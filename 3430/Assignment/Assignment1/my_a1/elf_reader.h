#ifndef _ELF_READER_H
#define _ELF_READER_H

#pragma pack(push)
#pragma pack(1)

typedef struct ELF_HEADER
{
    unsigned char elf_field[4];
    uint8_t format;
    uint8_t endianess;
    uint8_t Op_Sys;
    uint16_t object_type;
    uint16_t architecture;
    uint64_t entry_point;
    uint64_t ph_table_start; // program offset
    uint64_t sh_table_start; // section offset
    uint16_t ph_entry_num;
    uint16_t ph_entry_sizes;
    uint16_t sh_entry_num;
    uint16_t sh_entry_sizes;
    uint16_t sh_string_index;
} elf_header;

typedef struct PROGRAM_HEADER
{
    uint32_t p_num;
    uint32_t segment_type;
    uint64_t segment_address;
    uint64_t size;
    uint8_t byte_parse;

} program_header;

typedef struct SECTION_HEADER
{
    uint32_t name_offset;
    uint32_t type;
    uint64_t section_address;
    unsigned char str_name[32];
    uint64_t size;
    uint8_t byte_parse;
} section_header;

#pragma pack(pop)

void read_elf_header( elf_header *header, int handle );
void read_program_header( elf_header *elfHeader, program_header *header, int handle );
void read_section_header( elf_header *elfHeader, section_header *header, int handle );
void parse_hex(int handle);
#endif
