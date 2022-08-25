//-----------------------------------------
// NAME: Eriq Hampton
// STUDENT NUMBER: 7852830
// COURSE: COMP 3430, SECTION: A01
// INSTRUCTOR: Franklin Bristow
// ASSIGNMENT: assignment 1, QUESTION: 1
//
// REMARKS: Print the contents of the ELF header, program header, and section header.
//
//-----------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include "elf_reader.h"


int main(int argc, char *argv[])
{
    //unused variable warning
    (void)argc;

    char *filename = argv[1];
    elf_header elfHeader;
    int elf_fd = open( filename, O_RDONLY ); //elf file descriptor
    assert(elf_fd > 0);
    read_elf_header( &elfHeader, elf_fd );

    close(elf_fd);

    printf("Process Complete. Terminating..\n");

    return EXIT_SUCCESS;
}

//------------------------------------------------------
// read_elf_header
//
// PURPOSE: reads the Elf header of an ELF file.
// INPUT PARAMETERS:
//     takes a predefined struct in a1q1.h and the elf file descriptor
// OUTPUT PARAMETERS:
//     None
//------------------------------------------------------
void read_elf_header( elf_header *header, int handle )
{
    
    
    char format_type[3];
    char endian_type[14];
    int num_of_bytes;

    
    program_header programHeader;
    section_header  sectionHeader;

    // Read the magic number
    read( handle, &header->elf_field, 4 );

    if(header->elf_field[1] != 'E'&& header->elf_field[2] != 'L' && header->elf_field[3] != 'F')
    {
        printf("The program passed it not an ELF file please try again\n");
        return;
    }
    

    // read the rest since its an Elf file
    read( handle, &header->format, 1 );
    read( handle, &header->endianess, 1 );
    lseek(handle, 1, SEEK_CUR);
    read( handle, &header->Op_Sys, 1 );
    lseek(handle, 8, SEEK_CUR);
    read( handle, &header->object_type, 2 );
    read( handle, &header->architecture, 2 );
    lseek(handle, 4, SEEK_CUR);


    // the header goes off course and we need to specify bytes separately
    if(header->format == 2)
    {
        strcpy(format_type,"64");
        num_of_bytes = 8;
    }
    else
    {
        strcpy(format_type,"32");
        num_of_bytes = 4;
    }

    // get endianess
    if(header->endianess == 2)
    {
        strcpy(endian_type,"Big Endian");
    }
    else
    {
        strcpy(endian_type,"Little Endian");
    }

    read( handle, &header->entry_point, num_of_bytes);
    read( handle, &header->ph_table_start, num_of_bytes);
    read( handle, &header->sh_table_start, num_of_bytes);
    lseek(handle, 6, SEEK_CUR);
    read( handle, &header->ph_entry_sizes, 2);
    read( handle, &header->ph_entry_num, 2);
    read( handle, &header->sh_entry_sizes, 2);
    read( handle, &header->sh_entry_num, 2);
    read( handle, &header->sh_string_index, 2);

    //Print Report
    printf("ELF header:\n");
    printf("  * %s-bit\n", format_type);
    printf("  * %s\n", endian_type);
    printf("  * compiled for 0x0%x (operating system)\n", header->Op_Sys);
    printf("  * has type 0x0%x\n", header->object_type);
    printf("  * compiled for 0x%x (isa)\n", header->architecture);
    printf("  * entry point address 0x%016lx\n", header->entry_point);
    printf("  * program header table starts at 0x%016lx\n", header->ph_table_start);
    printf("  * section header table starts at 0x%016lx\n", header->sh_table_start);
    printf("  * there are %d program headers, each is %d bytes\n" , header->ph_entry_num,header->ph_entry_sizes );
    printf("  * there are %d section headers, each is %d bytes\n", header->sh_entry_num, header->sh_entry_sizes);
    printf("  * the section header string table is %d\n", header->sh_string_index);
    printf("-----------------------------------------------------------\n");

    read_program_header( header, &programHeader, handle );
    read_section_header( header, &sectionHeader, handle );
}

//------------------------------------------------------
// read_program_header
//
// PURPOSE: reads the Program header of an ELF file.
// INPUT PARAMETERS:
//     takes 2 predefined structs in a1q1.h and the elf file descriptor
// OUTPUT PARAMETERS:
//     None
//------------------------------------------------------
void read_program_header( elf_header *elfHeader, program_header *header, int handle )
{
    int num_of_bytes;

    //handle 32/64 differences
    if(elfHeader->format == 2)
    {
        num_of_bytes = 8;
    }
    else
    {
        num_of_bytes = 4;
    }

    for(int i = 0; i < elfHeader->ph_entry_num; i++)
    {

        //jump to the beginning of this header index iteration
        int new_offset = (i*elfHeader->ph_entry_sizes) + elfHeader->ph_table_start;
        lseek(handle, new_offset, SEEK_SET); //at offset
        read(handle, &header->segment_type, 4);

        //64 bit needs to skip 4 bytes
        if(num_of_bytes == 8)
        {
            lseek(handle, 4, SEEK_CUR);
        }
        lseek(handle, num_of_bytes, SEEK_CUR);
        read(handle, &header->segment_address, num_of_bytes);
        lseek(handle, num_of_bytes, SEEK_CUR);
        read(handle, &header->size, num_of_bytes);

        //Print Report
        printf("Program header #%d:\n", i);
        printf("  * segment type 0x%08x\n", header->segment_type);
        printf("  * virtual address of segment 0x%016lx\n", header->segment_address);
        printf("  * size in file %lu bytes\n", header->size);
        lseek(handle, new_offset, SEEK_SET);
        printf("  * first up to 32 bytes starting at 0x%016x:\n", new_offset);
        parse_hex(handle);
        parse_hex(handle);
        printf("\n-----------------------------------------------------------\n");
    }
}

void read_section_header( elf_header *elfHeader, section_header *header, int handle ) {
    int num_of_bytes;

    //jump to section with string
    int offset = (elfHeader->sh_entry_sizes*elfHeader->sh_string_index) + elfHeader->sh_table_start;
    //handle 32/64 differences
    if(elfHeader->format == 2) {num_of_bytes = 8;}
        else{ num_of_bytes = 4;}

    for(int i =0; i< elfHeader->sh_entry_num; i++)
    {
        //get back to curret section
        int new_offset = (i*elfHeader->sh_entry_sizes) + elfHeader->sh_table_start;
        /*
        printf("SECTION STARTS HERE %x\n", new_offset);
        printf("start of sections is %lx\n", elfHeader->sh_table_start);
        printf("string table section %d\n", elfHeader->sh_string_index);
        printf("each size is %d\n", elfHeader->sh_entry_sizes);
        printf("multiply %d\n", (elfHeader->sh_string_index*elfHeader->sh_entry_sizes));
        printf("add in sh_table_offset %lu\n", (elfHeader->sh_table_start+(elfHeader->sh_string_index*elfHeader->sh_entry_sizes)));
        printf("which is %x in hex\n", (elfHeader->sh_table_start+(elfHeader->sh_string_index*elfHeader->sh_entry_sizes)));*/

        lseek(handle, new_offset, SEEK_SET); //at offset
        read(handle, &header->name, 4);     //sh_name of this section
        read(handle, &header->type,4);
        lseek(handle, num_of_bytes, SEEK_CUR);
        read(handle, &header->section_address, num_of_bytes);
        read(handle, &header->offset, num_of_bytes);    //sh_off of this section
        read(handle, &header->size, num_of_bytes);
    
        printf("sh name of THIS SECTION = %x\n", header->name);
        printf("offset I EXPECT = %x\n", offset);

        
        // jump to shstrtab
        lseek(handle, offset, SEEK_SET);
        lseek(handle, header->name, SEEK_CUR);
        
        read(handle, header->names, 4);
        printf("%s\n", header->names);

        // Print Report
        printf("Section header #%d:\n", i);
        printf("  * section name %d\n",  header->name);
        printf("  * segment type 0x%x\n", header->type);
        printf("  * virtual address of section %#017lx\n", header->section_address);
        printf("  * size in file %lu bytes\n", header->size);
        printf("  * first up to 32 bytes starting at 0x%016x:\n", new_offset);
        parse_hex(handle);
        parse_hex(handle);
        printf("\n-----------------------------------------------------------\n");

    }
}

/*//------------------------------------------------------
// read_section_header
//
// PURPOSE: reads the Section header of an ELF file.
// INPUT PARAMETERS:
//     takes a predefined struct in a1q1.h and the elf file descriptor
// OUTPUT PARAMETERS:
//     None
//------------------------------------------------------
void read_section_header( elf_header *elfHeader, section_header *header, int handle )
{
    int num_of_bytes;

    //handle 32/64 differences
    if(elfHeader->format == 2) {num_of_bytes = 8;}
        else{ num_of_bytes = 4;}

    for(int i =0; i< elfHeader->sh_entry_num; i++)
    {
        int new_offset = (i*elfHeader->sh_entry_sizes) + elfHeader->sh_table_start;

        lseek(handle, new_offset, SEEK_SET); //at offset
        read(handle, &header->name, 4);
        read(handle, &header->type,4);
        lseek(handle, num_of_bytes, SEEK_CUR);
        read(handle, &header->section_address, num_of_bytes);
        lseek(handle, num_of_bytes, SEEK_CUR);
        read(handle, &header->size, num_of_bytes);

        lseek(handle, new_offset, SEEK_SET); //at offset
        read(handle, &header->name, 4);     //sh_name of this section
        read(handle, &header->type,4);
        lseek(handle, num_of_bytes, SEEK_CUR);
        read(handle, &header->section_address, num_of_bytes);
        read(handle, &header->offset, num_of_bytes);    //sh_off of this section
        read(handle, &header->size, num_of_bytes);

        // Print Report
        printf("Section header #%d:\n", i);
        printf("  * section name %d\n",  header->name);
        printf("  * segment type %#03x\n", header->type);
        printf("  * virtual address of section %#017lx\n", header->section_address);
        printf("  * size in file %lu bytes\n", header->size);
        printf("  * first up to 32 bytes starting at 0x%016x:\n", new_offset);
        parse_hex(new_offset, handle);
        parse_hex(new_offset, handle);
        printf("\n-----------------------------------------------------------\n");

    }
}*/
//------------------------------------------------------
// parse_hex
//
// PURPOSE: parses the first 32 bits of the current program header
// INPUT PARAMETERS:
//     an offset to the location of the current program header
//     takes a predefined struct in a1q1.h and the elf file descriptor
// OUTPUT PARAMETERS:
//     None
//------------------------------------------------------
void parse_hex(int handle)
{
    u_int8_t byte_parse;
    // the hex pairs by hand
    printf("    ");
    for(int i = 0; i<16; i++) {
        read(handle, &byte_parse, 1);

        printf("%02x ", byte_parse);
    }
    printf("\n");
    
}
