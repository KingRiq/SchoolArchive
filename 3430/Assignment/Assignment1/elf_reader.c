//-----------------------------------------
// NAME: Eriq Hampton
// STUDENT NUMBER: 7852830
// COURSE: COMP 3430, SECTION: A01
// INSTRUCTOR: Robert Guderian
// ASSIGNMENT: Assignment 1, QUESTION: 1
//
// REMARKS: Print the contents of the ELF header, 
//  program header, and section header.
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


int main(int argc, char *argv[]){
    //unused variable warning
    (void)argc;

    char *filename = argv[1];
    elf_header elfHeader;
    int elf_fd = open( filename, O_RDONLY );
    assert(elf_fd > 0);
    read_elf_header( &elfHeader, elf_fd );

    close(elf_fd);

    printf("Process Complete. Terminating..\n");

    exit(EXIT_SUCCESS);
}

//------------------------------------------------------
// read_elf_header
//
// PURPOSE: Reads the Elf header of an ELF file and prints it out.
// INPUT PARAMETERS:
//     Takes a predefined struct in a1q1.h and the elf file descriptor
// OUTPUT PARAMETERS:
//     None
//------------------------------------------------------
void read_elf_header( elf_header *header, int handle ) {
    char format_type[3];
    char endian_type[14];
    int num_of_bytes;
    program_header programHeader;
    section_header  sectionHeader;

    // Read the magic number
    read( handle, &header->elf_field, 4 );

    if(header->elf_field[1] != 'E'&& header->elf_field[2] != 'L' && header->elf_field[3] != 'F') {
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
    if(header->format == 2) {
        strcpy(format_type,"64");
        num_of_bytes = 8;
    }
    else {
        strcpy(format_type,"32");
        num_of_bytes = 4;
    }

    // get endianess
    if(header->endianess == 2) {
        strcpy(endian_type,"Big Endian");
    }
    else {
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
// PURPOSE: Reads the Program headers of an ELF file and prints it out.
// INPUT PARAMETERS:
//     Takes 2 predefined structs in a1q1.h and the elf file descriptor
// OUTPUT PARAMETERS:
//     None
//------------------------------------------------------
void read_program_header( elf_header *elfHeader, program_header *header, int handle ) {
    int num_of_bytes;
    int new_offset = 0;

    //handle 32/64 differences
    if(elfHeader->format == 2) {
        num_of_bytes = 8;
    }
    else {
        num_of_bytes = 4;
    }

    for(int i = 0; i < elfHeader->ph_entry_num; i++) {

        // jump to the beginning of this header index iteration
        new_offset = (i*elfHeader->ph_entry_sizes) + elfHeader->ph_table_start;
        lseek(handle, new_offset, SEEK_SET);
        read(handle, &header->segment_type, 4);

        // 64 bit needs to skip 4 bytes
        if(num_of_bytes == 8) {
            lseek(handle, 4, SEEK_CUR);
        }

        lseek(handle, num_of_bytes, SEEK_CUR);
        read(handle, &header->segment_address, num_of_bytes);
        lseek(handle, num_of_bytes, SEEK_CUR);
        read(handle, &header->size, num_of_bytes);
        lseek(handle, new_offset, SEEK_SET);
        
        // Print Report
        printf("Program header #%x:\n", i);
        printf("  * segment type 0x%08x\n", header->segment_type);
        printf("  * virtual address of segment 0x%016lx\n", header->segment_address);
        printf("  * size in file %lu bytes\n", header->size);
        printf("  * first up to 32 bytes starting at 0x%016x:\n", new_offset);
        parse_hex(handle);
        parse_hex(handle);
        printf("-----------------------------------------------------------\n");
    }
}

//------------------------------------------------------
// read_section_header
//
// PURPOSE: Reads the Section headers of an ELF file and prints it out.
// INPUT PARAMETERS:
//     Takes a predefined struct in a1q1.h and the elf file descriptor
// OUTPUT PARAMETERS:
//     None
//------------------------------------------------------
void read_section_header( elf_header *elfHeader, section_header *header, int handle ) {

    int num_of_bytes;
    int shstr_offset = (elfHeader->sh_string_index*elfHeader->sh_entry_sizes) + elfHeader->sh_table_start;
    uint64_t table_offset = 0;
    int new_offset = 0;

    // handle 32/64 differences
    if(elfHeader->format == 2) {
        num_of_bytes = 8;
    }
    else { 
        num_of_bytes = 4;
    }

    // jump to shstrtab section
    lseek(handle, shstr_offset, SEEK_SET);
    lseek(handle, 8, SEEK_CUR);
    lseek(handle, (num_of_bytes+num_of_bytes), SEEK_CUR);

    // get location of string table
    read(handle, &table_offset, num_of_bytes);
    
    for(int i =0; i< elfHeader->sh_entry_num; i++) {

        // jump to the beginning of this header index iteration
        new_offset = (i*elfHeader->sh_entry_sizes) + elfHeader->sh_table_start;

        lseek(handle, new_offset, SEEK_SET);
        read(handle, &header->name_offset, 4);

        // jump to string table and read the name
        lseek(handle, table_offset, SEEK_SET);
        lseek(handle, header->name_offset, SEEK_CUR);
        read(handle, header->str_name, 16);
        lseek(handle, new_offset, SEEK_SET);
        lseek(handle, 4, SEEK_CUR);
        read(handle, &header->type,4);
        lseek(handle, num_of_bytes, SEEK_CUR);
        read(handle, &header->section_address, num_of_bytes);
        lseek(handle, num_of_bytes, SEEK_CUR);
        read(handle, &header->size, num_of_bytes);
        lseek(handle, new_offset, SEEK_SET);

        // Print Report
        printf("Section header #%x:\n", i);
        printf("  * section name %s\n",  header->str_name);
        printf("  * segment type 0x%02x\n", header->type);
        printf("  * virtual address of section %017lx\n", header->section_address);
        printf("  * size in file %lu bytes\n", header->size);
        printf("  * first up to 32 bytes starting at 0x%016x:\n", new_offset);
        parse_hex(handle);
        parse_hex(handle);
        printf("-----------------------------------------------------------\n");
    }
}
//------------------------------------------------------
// parse_hex
//
// PURPOSE: Parses the next 16 bits and prints them one byte at a time 
// INPUT PARAMETERS:
//     The elf file descriptor
// OUTPUT PARAMETERS:
//     None
//------------------------------------------------------
void parse_hex(int handle) {
    u_int8_t byte_parse;
    
    printf("    ");
    for(int i = 0; i<16; i++) {
        read(handle, &byte_parse, 1);
        printf("%02x ", byte_parse);
    }
    printf("\n");   
}
