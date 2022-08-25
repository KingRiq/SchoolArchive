#include "fsck-exfat.h"

int main(int argc, char **argv)
{

    // read tasks in line by line
    if (argc != 2)
    {
        printf("\nPlease enter only 2 arguments.\n");
        exit(0);
    }

    char *filename = argv[1];
    int file_fd = open(filename, O_RDONLY); // file descriptor

    printf("\nFile: %s\n\n", filename);
    main_boot_sector MBR;
    read_MBR(&MBR, file_fd);

    close(file_fd);
    printf("Process Complete\n");
    return EXIT_SUCCESS;
}

void read_MBR(main_boot_sector *MBR, int handle)
{
    directory_entry directory_entry;
    uint8_t entry_val = 0x81;

    assert(MBR != NULL);

    // Jumpboot
    read(handle, &MBR->jump_boot, 3);
    check_Jumpboot(MBR);

    // fs_name
    read(handle, &MBR->fs_name, 8);
    check_fs_name(MBR);

    // mustbezero
    read(handle, &MBR->must_be_zero, 53);
    check_must_be_zero(MBR);

    // get metadata for necesary fields
    read(handle, &MBR->partition_offset, 8);
    read(handle, &MBR->volume_length, 8);
    read(handle, &MBR->fat_offset, 4);
    read(handle, &MBR->fat_length, 4);
    read(handle, &MBR->cluster_heap_offset, 4);
    read(handle, &MBR->cluster_count, 4);
    read(handle, &MBR->first_cluster_of_root_directory, 4);
    read(handle, &MBR->volume_serial_number, 4);
    read(handle, &MBR->fs_revision, 2);
    read(handle, &MBR->fs_flags, 2);
    read(handle, &MBR->bytes_per_sector_shift, 1);

    check_volume_length(MBR);
    read(handle, &MBR->sectors_per_cluster_shift, 1);
    read(handle, &MBR->number_of_fats, 1);

    check_fatoffset(MBR);
    check_fat_length(MBR);

    read(handle, &MBR->drive_select, 1);
    read(handle, &MBR->percent_in_use, 1);
    read(handle, &MBR->reserved, 7);
    read(handle, &MBR->bootcode, 390);
    read(handle, &MBR->boot_signature, 2);

    check_root_dir(MBR);
    check_boot_sig(MBR);

    // MBR Check Complete
    printf("MBR appears to be consistent.\n");

    int bytes_per_sector = 1 << MBR->bytes_per_sector_shift;
    int sectors_per_cluster = 1 << MBR->sectors_per_cluster_shift;
    int cluster_heap_offset = MBR->cluster_heap_offset * bytes_per_sector;
    int first_cluster_root_index = MBR->first_cluster_of_root_directory - 2;
    int root_cluster_offset = first_cluster_root_index * (sectors_per_cluster * bytes_per_sector);

    // jump to first cluster of root directory
    lseek(handle, (root_cluster_offset + cluster_heap_offset), SEEK_SET);
    read(handle, &directory_entry.EntryType, 1);

    // search for DataEntry 0x81
    while (directory_entry.EntryType != entry_val)
    {
        lseek(handle, 31, SEEK_CUR);
        read(handle, &directory_entry.EntryType, 1);
    }

    // get the meta data for the other fields
    read(handle, &directory_entry.CustomDefined, 19);
    read(handle, &directory_entry.FirstCluster, 4);
    read(handle, &directory_entry.DataLength, 8);

    // offset of first cluster
    int newoffset = (directory_entry.FirstCluster - 2) * (sectors_per_cluster * bytes_per_sector);

    // we must be DataLength bytes long
    uint8_t array[directory_entry.DataLength];

    // jump to firstcluster index
    lseek(handle, (cluster_heap_offset + newoffset), SEEK_SET);
    int bitCount = 0;

    // read datalength bytes
    read(handle, &array, directory_entry.DataLength);
    for (int i = 0; i < (int)directory_entry.DataLength; i++)
    {
        // printf("%x", array[i]);
        bitCount += __builtin_popcount(array[i]);
    }

    // convert to float for decimal values
    float percent_value = (double)bitCount / (double)(MBR->cluster_count);

    // convert to percentage
    percent_value = percent_value * 100;

    // reduces float to int (implicitly the floor of the integer value)
    int percent_in_use = percent_value;

    check_percent_in_use(MBR, percent_in_use, bitCount);
    printf("File system appears to be consistent.\n");
}

void check_Jumpboot(main_boot_sector *MBR)
{
    unsigned char index0 = 0xeb;
    unsigned char index1 = 0x76;
    unsigned char index2 = 0x90;
    if (MBR->jump_boot[0] != index0 || MBR->jump_boot[1] != index1 || MBR->jump_boot[2] != index2)
    {
        printf("Inconsistent file system: Jumpboot must be '%x%x%x', value is '%x%x%x'.", index0, index1, index2, MBR->jump_boot[0], MBR->jump_boot[1], MBR->jump_boot[2]);
        exit(EXIT_FAILURE);
    }
}

void check_fs_name(main_boot_sector *MBR)
{
    char *exfat = "EXFAT   ";
    if (strncmp(MBR->fs_name, exfat, 8) != 0)
    {
        printf("Inconsistent file system: FileSystemName must be %s, value is %s.", exfat, MBR->fs_name);
        exit(EXIT_FAILURE);
    }
}

void check_must_be_zero(main_boot_sector *MBR)
{
    for (int i = 0; i < 53; i++)
    {
        if (MBR->must_be_zero[i] != 0)
        {
            printf("Inconsistent file system: MustBeZero value is incorrect\n");
            exit(EXIT_FAILURE);
        }
    }
}

void check_boot_sig(main_boot_sector *MBR)
{
    int boot_signature = 0xaa55;
    if (MBR->boot_signature != boot_signature)
    {
        printf("Inconsistent file system: BootSignature should be 0x%X, value is 0x%X.\n", boot_signature, MBR->boot_signature);
        exit(EXIT_FAILURE);
    }
}

void check_volume_length(main_boot_sector *MBR)
{

    uint64_t max_val = (1ULL << 63); // ULL = unsigned long long (uint_64)
    uint64_t temp = max_val - 1;
    uint64_t min_val = 1 << MBR->bytes_per_sector_shift;

    // max val = 1<<64 - 1
    max_val = max_val + temp;

    // hold value 2^20
    temp = 1 << 20;

    if (MBR->volume_length > max_val)
    {
        printf("Inconsistent file system: VolumeLength must be <= %lu, value is %lu.\n", max_val, MBR->volume_length);
        exit(EXIT_FAILURE);
    }
    else if (MBR->volume_length < temp / min_val)
    {
        printf("Inconsistent file system: VolumeLength must be >= %lu, value is %lu.\n", temp / min_val, MBR->volume_length);
        exit(EXIT_FAILURE);
    }
}

void check_root_dir(main_boot_sector *MBR)
{
    uint32_t min_val = 2;
    uint32_t max_val = MBR->cluster_count + 1;
    uint32_t first_root_cluster_index = MBR->first_cluster_of_root_directory - 2;
    if (first_root_cluster_index < min_val)
    {
        printf("Inconsistent file system: FirstClusterOfRootIndex should be >= %d, value is %d.\n", min_val, first_root_cluster_index);

        exit(EXIT_FAILURE);
    }
    else if (first_root_cluster_index > max_val)
    {
        printf("Inconsistent file system: FirstClusterOfRootIndex should be <= %d, value is %d.\n", max_val, first_root_cluster_index);
        exit(EXIT_FAILURE);
    }
}

void check_fatoffset(main_boot_sector *MBR)
{
    uint32_t min_val = 24;
    uint32_t max_val = MBR->cluster_heap_offset - (MBR->fat_length * MBR->number_of_fats);

    if (MBR->fat_offset < min_val)
    {
        printf("Inconsistent file system: FatOffset should be >=%d, value is %d.\n", min_val, MBR->fat_offset);
        exit(EXIT_FAILURE);
    }
    else if (MBR->fat_offset > max_val)
    {
        printf("Inconsistent file system: FatOffset should be <=%d, value is %d.\n", max_val, MBR->fat_offset);
        exit(EXIT_FAILURE);
    }
}

void check_fat_length(main_boot_sector *MBR)
{

    uint32_t two_squared = 1 << 2;
    uint32_t bytes_per_sector_squared = 1 << MBR->bytes_per_sector_shift;
    uint32_t min_val = ((MBR->cluster_count + 2) * (two_squared / bytes_per_sector_squared) + 1);
    uint32_t max_val = MBR->cluster_heap_offset - MBR->fat_offset / MBR->number_of_fats;

    if (MBR->fat_length < min_val)
    {
        printf("Inconsistent file system: FatLength should be >= %d, value is %d.\n", min_val, MBR->fat_length);

        exit(EXIT_FAILURE);
    }
    else if (MBR->fat_length > max_val)
    {
        printf("Inconsistent file system: FatLength should be <= %d, value is %d.\n", max_val, MBR->fat_length);
        exit(EXIT_FAILURE);
    }
}

void check_percent_in_use(main_boot_sector *MBR, int percent_in_use, int bitCount)
{
    if (MBR->percent_in_use != percent_in_use)
    {
        printf("Inconsistent file system: PercentInUse is %d%%, allocation bitmap is %d/%d => %d%%.\n", MBR->percent_in_use, bitCount, MBR->cluster_count, (bitCount * 100 / MBR->cluster_count));
        exit(EXIT_FAILURE);
    }
}
