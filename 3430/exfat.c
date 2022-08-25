//-----------------------------------------
// NAME: Eriq Hampton
// STUDENT NUMBER: 7852830
// COURSE: COMP 3430, SECTION: A01
// INSTRUCTOR: Robert Guderian
// ASSIGNMENT: Assignment 4, QUESTION: 1-3
//
// REMARKS: prints the exfat volume info and a tree
//
//-----------------------------------------
#include "exfat.h"
#include <stdbool.h>

#define BITS_TO_BYTES 8
#define BYTES_TO_KB 1024
void searchClusters(main_boot_sector *MBR, Queue *queue, int handle, char *path, bool isDirectory, int length);
char *pathtofile;
void getFile(main_boot_sector *MBR, uint32_t clusterIndex, char *path, int handle, int length);
int main(int argc, char **argv)
{
    // read tasks in line by line
    if (argc < 3)
    {
        printf("\nPlease enter at least 3 arguments.\n");
        exit(0);
    }

    char *filename = argv[1];
    int file_fd = open(filename, O_RDONLY); // file descriptor

    printf("\nFile: %s\n\n", filename);

    // the stack lead to undefined behaviour
    main_boot_sector *MBR = (main_boot_sector *)malloc(sizeof(main_boot_sector));
    read_MBR(MBR, file_fd);

    if (argc > 2)
    {
        if (strcmp(argv[2], "info") == 0)
            printInfo(MBR, file_fd);

        else if (strcmp(argv[2], "list") == 0)
            getList(MBR, file_fd);

        else if (strcmp(argv[2], "get") == 0)
        {
            if (argc > 3)
            {

                pathtofile = strdup(argv[3]);
                open("file.txt", O_RDWR | O_CREAT | O_APPEND);
                printf("Now searching for %s\n\n", pathtofile);

                getFile(MBR, MBR->first_cluster_of_root_directory, pathtofile, file_fd, (int)strlen(argv[3]));
                free(pathtofile);
            }
            else
            {
                printf("The get command requires a 4th argument which is a path to the file. Please try again\n");
            }
        }
    }

    close(file_fd);
    free(MBR);

    printf("\nProcess Complete\n");
    return EXIT_SUCCESS;
}

//------------------------------------------------------
// read_MBR
//
// PURPOSE: check that the exfat file passed is valid. Prints error when one is found.
// INPUT PARAMETERS:
//     MBR Struct, file descriptor
// OUTPUT PARAMETERS:
//     None
//------------------------------------------------------
void read_MBR(main_boot_sector *MBR, int handle)
{
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
    // printf("MBR appears to be consistent.\n");
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
// this

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
        printf("Inconsistent file system: VolumeLength must be <= %llu, value is %llu.\n", max_val, MBR->volume_length);
        exit(EXIT_FAILURE);
    }
    else if (MBR->volume_length < temp / min_val)
    {
        printf("Inconsistent file system: VolumeLength must be >= %llu, value is %llu.\n", temp / min_val, MBR->volume_length);
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

//------------------------------------------------------
// printInfo
//
// PURPOSE: prints the volume info
// INPUT PARAMETERS:
//     MBR Struct, file descripter (handle)
// OUTPUT PARAMETERS:
//     None
//------------------------------------------------------
void printInfo(main_boot_sector *MBR, int handle)
{
    uint64_t volume_serial = MBR->volume_serial_number;
    directory_entry directory_entry;
    volume_label_entry volume_label_dir;
    uint8_t entry_val = 0x81;

    int bytes_per_sector = 1 << MBR->bytes_per_sector_shift;
    int sectors_per_cluster = 1 << MBR->sectors_per_cluster_shift;
    int cluster_heap_offset = MBR->cluster_heap_offset * bytes_per_sector;
    int first_cluster_root_index = MBR->first_cluster_of_root_directory - 2;
    int root_cluster_offset = first_cluster_root_index * (sectors_per_cluster * bytes_per_sector);

    // jump to first cluster of root directory
    int p = lseek(handle, (root_cluster_offset + cluster_heap_offset), SEEK_SET);

    read(handle, &volume_label_dir.EntryType, 1);
    while (volume_label_dir.EntryType != 0x83)
    {
        lseek(handle, 31, SEEK_CUR);
        read(handle, &directory_entry.EntryType, 1);
    }
    // get the meta data for the other fields
    read(handle, &volume_label_dir.CharCount, 1);
    read(handle, &volume_label_dir.VolumeLabel, 22);
    read(handle, &volume_label_dir.Reserved, 8);

    lseek(handle, p, SEEK_SET);
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

    char *volume_label = unicode2ascii((uint16_t *)volume_label_dir.VolumeLabel, volume_label_dir.CharCount);

    // offset of first cluster
    int newoffset = (directory_entry.FirstCluster - 2) * (sectors_per_cluster * bytes_per_sector);

    // we must be DataLength bytes long
    uint8_t array[directory_entry.DataLength];

    // jump to firstcluster index
    lseek(handle, (cluster_heap_offset + newoffset), SEEK_SET);
    int bitCount = 0;

    // read datalength bytes
    read(handle, &array, directory_entry.DataLength);

    // count the set bits and flip them.
    for (int i = 0; i < (int)directory_entry.DataLength; i++)
    {
        bitCount += __builtin_popcount(array[i]);
    }

    int unallocated_clusters = MBR->cluster_count - bitCount;

    // Log
    printf("Volume Label: %s\n", volume_label);
    printf("Volume Serial Number: %llu\n", volume_serial);
    printf("Free space on drive: %d KB(s)\n", (unallocated_clusters * sectors_per_cluster * bytes_per_sector) / BYTES_TO_KB);
    printf("Cluster Size in Sectors: %d\n", sectors_per_cluster);
    printf("Cluster Size in Bytes: %d\n", sectors_per_cluster * bytes_per_sector);
    printf("Storage capacity: %d KB(s)\n", (MBR->cluster_count * sectors_per_cluster * bytes_per_sector) / BYTES_TO_KB);
    free(volume_label);
}

//------------------------------------------------------
// getList
//
// PURPOSE: prints out a list of the file structure of the exfat volume passed
// INPUT PARAMETERS:
//     MBR Struct, and file descriptor to the volume passed
// OUTPUT PARAMETERS:
//     None
//------------------------------------------------------
void getList(main_boot_sector *MBR, int handle)
{
    uint32_t index = MBR->first_cluster_of_root_directory;
    Queue *queue = fatChain(MBR, index, handle);

    getClusters(MBR, queue, handle, 0);
    free(queue);
}

//------------------------------------------------------
// fatChain
//
// PURPOSE: returns a queue with the current cluster chain inside
// INPUT PARAMETERS:
//     MBR Struct, and file descriptor to the volume passed and index of the first cluster
//      in the chain
// OUTPUT PARAMETERS:
//     returns a queue struct
//------------------------------------------------------
Queue *fatChain(main_boot_sector *MBR, uint32_t index, int handle)
{
    uint32_t index1 = index;
    int bytes_per_sector = 1 << MBR->bytes_per_sector_shift;
    Queue *queue;

    // check if the first cluster is valid then loop
    if ((int)index1 == -1)
    {

        return NULL;
    }
    else
    {
        queue = createQueue();
        enQueue(queue, index);
    }
    while ((int)index1 != -1 && (int)index1 != 0)
    {
        // jump to fat
        lseek(handle, (MBR->fat_offset * bytes_per_sector), SEEK_SET);
        lseek(handle, (index1)*4, SEEK_CUR);

        read(handle, &index1, 4);

        // only put valid clusters in the queue
        if ((int)index1 != -1 && (int)index1 != 0)
        {
            enQueue(queue, index1);
        }
    }
    return queue;
}

//------------------------------------------------------
// getClusters
//
// PURPOSE: navigates to the clusters in the cluster chain passed inside a queue
// INPUT PARAMETERS:
//     MBR struct, Queue LL, handle which is file descripter of the volume, depth
// OUTPUT PARAMETERS:
//     None
//------------------------------------------------------
void getClusters(main_boot_sector *MBR, Queue *queue, int handle, int depth)
{
    int bytes_per_sector = 1 << MBR->bytes_per_sector_shift;
    int sectors_per_cluster = 1 << MBR->sectors_per_cluster_shift;
    int cluster_heap_offset = MBR->cluster_heap_offset * bytes_per_sector;
    bool is_Directory = false;
    uint8_t entry;
    uint32_t clusterNum;

    assert(queue != NULL);
    while (!isEmpty(queue))
    {
        int boundary = 0;
        int printed = 0;
        uint8_t nameLength;
        uint32_t nextchain;
        uint16_t fileatt;
        Queue *dir_queue;

        // jump to cluster heap
        lseek(handle, (cluster_heap_offset), SEEK_SET);

        // deQueue a cluster chain index
        nodes *temp = deQueue(queue);
        clusterNum = temp->clusterNum;
        assert((int)clusterNum > -1);

        // jump to *this* cluster
        lseek(handle, (clusterNum - 2) * (sectors_per_cluster * bytes_per_sector), SEEK_CUR);

        // we must check what this is
        read(handle, &entry, 1);

        // iterate over the full cluster if we hit 0x0 we are done with this cluster
        while (boundary < bytes_per_sector * sectors_per_cluster / 32 && entry != 0x0)
        {
            if (entry == 0x85)
            {

                lseek(handle, 3, SEEK_CUR);
                read(handle, &fileatt, 2);
                lseek(handle, 26, SEEK_CUR);

                // check file attribute
                if (fileatt & 1 << 4)
                {
                    is_Directory = true;
                }
            }
            else if (entry == 0xc0)
            {

                // stream extension
                lseek(handle, 2, SEEK_CUR);
                read(handle, &nameLength, 1);
                lseek(handle, 16, SEEK_CUR);
                read(handle, &nextchain, 4);

                // save our place
                int value = lseek(handle, 0, SEEK_CUR);
                dir_queue = fatChain(MBR, nextchain, handle);

                // finish where we left off
                lseek(handle, value, SEEK_SET);

                lseek(handle, 8, SEEK_CUR);
            }
            else if (entry == 0xc1)
            {

                // We have a file name
                if (is_Directory)
                {
                    printDepth(depth);
                    printf("Directory: ");
                }
                else if (printed == 0)
                {
                    printDepth(depth);
                    printf("File: ");
                }
                lseek(handle, 1, SEEK_CUR);
                uint16_t filename[30];
                read(handle, &filename, 30);

                char *name = unicode2ascii(filename, nameLength);

                printed += strlen(name);

                printf("%s", name);
                if (printed == nameLength)
                {
                    printf("\n");
                    printed = 0;
                }

                int value = lseek(handle, 0, SEEK_CUR);

                if (is_Directory)
                {
                    getClusters(MBR, dir_queue, handle, depth + 1);
                    is_Directory = false;
                }
                // finish where we left off
                lseek(handle, value, SEEK_SET);
                free(name);
            }
            else
            {
                lseek(handle, 31, SEEK_CUR);
            }
            // read the next entry and increment
            read(handle, &entry, 1);
            boundary++;
        }

        // free the node just deQueue'd
        free(temp);
        free(dir_queue);
    }
}

//------------------------------------------------------
// printDepth
//
// PURPOSE: pretty prints the depth of the current caller
// INPUT PARAMETERS:
//     int Depth which represents the depth within the filesystem directories
// OUTPUT PARAMETERS:
//     None
//------------------------------------------------------
void printDepth(int depth)
{
    if (depth > 0)
    {
        for (int i = 0; i < depth; i++)
        {
            printf("-");
        }
        printf(" ");
    }
}

//------------------------------------------------------
// getFile
//
// PURPOSE: Used to recursively strip the path until we are in the file
//  directory
// INPUT PARAMETERS:
//     MBR, first cluster of the cluster chain, current path, file descriptor, length of string left to search
// OUTPUT PARAMETERS:
//     None
//------------------------------------------------------
void getFile(main_boot_sector *MBR, uint32_t clusterIndex, char *path, int handle, int length)
{

    printf("Searching for %s\n", path);
    bool isDirectory = false;

    if (path[0] == '/')
    {
        isDirectory = true;
        path++;
    }

    // no need to check if it is already determined to be a directory
    int checkLength = 0;

    while (path[checkLength] != '/' && isDirectory != true && checkLength < length)
    {
        checkLength++;
    }
    if (checkLength == length)
    {
        isDirectory = false;
    }
    else
    {
        isDirectory = true;
    }

    // else the first file we are looking for is directory.

    Queue *queue = fatChain(MBR, clusterIndex, handle);
    searchClusters(MBR, queue, handle, path, isDirectory, checkLength);

    (void)queue;
}

//------------------------------------------------------
// searchClusters
//
// PURPOSE: Searches for the file/directory passed
// INPUT PARAMETERS:
//     MBR, first cluster of the cluster chain, current path, file descriptor, length of string left to search
//      A boolean specifying whether we are looking for a file or directory
// OUTPUT PARAMETERS:
//     None
//------------------------------------------------------
void searchClusters(main_boot_sector *MBR, Queue *queue, int handle, char *path, bool isDirectory, int length)
{

    int bytes_per_sector = 1 << MBR->bytes_per_sector_shift;
    int sectors_per_cluster = 1 << MBR->sectors_per_cluster_shift;
    int cluster_heap_offset = MBR->cluster_heap_offset * bytes_per_sector;
    bool is_Directory = false;
    uint8_t entry;
    uint32_t clusterNum;

    if (isDirectory)
    {
        printf("we are looking for a directory\n");
    }
    else
    {
        printf("we're looking for a file\n");
    }
    char *file = strndup(path, length);

    assert(queue != NULL);
    while (!isEmpty(queue))
    {
        int boundary = 0;
        uint8_t nameLength;
        uint32_t nextchain;
        uint16_t fileatt;
        Queue *dir_queue;

        // jump to cluster heap
        lseek(handle, (cluster_heap_offset), SEEK_SET);

        // deQueue a cluster chain index
        nodes *temp = deQueue(queue);
        clusterNum = temp->clusterNum;
        assert((int)clusterNum > -1);

        // jump to *this* cluster
        lseek(handle, (clusterNum - 2) * (sectors_per_cluster * bytes_per_sector), SEEK_CUR);

        // we must check what this is
        read(handle, &entry, 1);

        // iterate over the full cluster if we hit 0x0 we are done with this cluster
        while (boundary < bytes_per_sector * sectors_per_cluster / 32 && entry != 0x0)
        {
            if (entry == 0x85)
            {
                lseek(handle, 3, SEEK_CUR);
                read(handle, &fileatt, 2);
                lseek(handle, 26, SEEK_CUR);

                // check file attribute
                if (fileatt & 1 << 4)
                {
                    is_Directory = true;
                }
            }
            else if (entry == 0xc0)
            {
                // stream extension
                lseek(handle, 2, SEEK_CUR);
                read(handle, &nameLength, 1);
                lseek(handle, 16, SEEK_CUR);
                read(handle, &nextchain, 4);

                // save our place
                int value = lseek(handle, 0, SEEK_CUR);
                dir_queue = fatChain(MBR, nextchain, handle);

                // finish where we left off
                lseek(handle, value, SEEK_SET);
                lseek(handle, 8, SEEK_CUR);
            }
            else if (entry == 0xc1)
            {
                lseek(handle, 1, SEEK_CUR);
                uint16_t filename[30];
                read(handle, &filename, 30);

                char *name = unicode2ascii(filename, nameLength);
                if (strcmp(name, file) == 0)
                {
                    if (is_Directory && isDirectory)
                    {
                        // we need to go deeper into the directory
                        nodes *nextClusterIndex = deQueue(dir_queue);
                        int index2 = length + 1;

                        if (index2 < (int)strlen(path))
                        {
                            // get the distance from curr to end
                            int distance = (int)strlen(pathtofile) - index2;
                            char tempArray[distance];

                            memcpy(tempArray, &path[index2], distance);
                            char *newFile = strdup(tempArray);

                            newFile[distance] = '\0';

                            // recursively get the next file/directory
                            getFile(MBR, nextClusterIndex->clusterNum, newFile, handle, (int)strlen(newFile));
                            free(newFile);
                            free(nextClusterIndex);
                        }
                        // else we are out of bounds
                    }
                    // we have found the file next search the stream extension
                    else
                    {
                        printf("We have found the file \"%s\"\n", name);
                    }
                }
                free(name);
            }
            else
            {
                lseek(handle, 31, SEEK_CUR);
            }

            // read the next entry and increment
            read(handle, &entry, 1);
            boundary++;
        }

        // free the node just deQueue'd
        free(temp);
        free(dir_queue);
    }
    free(file);
}
