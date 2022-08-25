#ifndef _FSCK_EXFAT_H
#define _FSCK_EXFAT_H
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <stdint.h>
#include <string.h>
#pragma pack(push)
#pragma pack(1)

typedef struct MAIN_BOOT_SECTOR
{
    uint8_t jump_boot[3];
    char fs_name[8];
    uint8_t must_be_zero[53];
    uint64_t partition_offset;
    uint64_t volume_length;
    uint32_t fat_offset;
    uint32_t fat_length;
    uint32_t cluster_heap_offset;
    uint32_t cluster_count;
    uint32_t first_cluster_of_root_directory;
    uint32_t volume_serial_number;
    uint16_t fs_revision;
    uint16_t fs_flags;
    uint8_t bytes_per_sector_shift;
    uint8_t sectors_per_cluster_shift;
    uint8_t number_of_fats;
    uint8_t drive_select;
    uint8_t percent_in_use;
    uint8_t reserved[7];
    uint8_t bootcode[390];
    uint16_t boot_signature;
} main_boot_sector;

typedef struct DIRECTORY_ENTRY
{
    uint8_t EntryType;
    uint8_t CustomDefined[19];
    uint32_t FirstCluster;
    uint64_t DataLength;
} directory_entry;
#pragma pack(pop)

void read_MBR(main_boot_sector *MBR, int handle);
void check_Jumpboot(main_boot_sector *MBR);
void check_fs_name(main_boot_sector *MBR);
void check_must_be_zero(main_boot_sector *MBR);
void check_boot_sig(main_boot_sector *MBR);
void check_volume_length(main_boot_sector *MBR);
void check_boot_sig(main_boot_sector *MBR);
void check_root_dir(main_boot_sector *MBR);
void check_fatoffset(main_boot_sector *MBR);
void check_fat_length(main_boot_sector *MBR);
void check_percent_in_use(main_boot_sector *MBR, int percent_in_use, int bitCount);
#endif
