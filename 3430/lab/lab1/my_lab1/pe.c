//-----------------------------------------
// NAME: Eriq Hampton 
// STUDENT NUMBER: 7852830
// COURSE: COMP 3430, SECTION: A01
// INSTRUCTOR: Robert Guderian
// LAB 1: Lab #1, QUESTION: question 1
// 
// REMARKS: read the COFF File Header from a PE-formatted binary file (an .exe file on Windows)
//
//-----------------------------------------
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
typedef struct COFF_HEADER
{
    u_int32_t offset;
    char sig[8];
    uint16_t arch;
    uint16_t section;
    time_t time;
    uint32_t symbolStart;
    uint32_t symbolCount;
    uint16_t optHeaders;
    uint16_t characteristics;
} coff_header;
#pragma pack(pop)


void read_coff_header(coff_header*, int handle);
int const OFFSET = 0x3c;

int main(int argv, char* argc[]) {

    if(argv != 2) {
        printf("\nPlease enter only 2 arguments.\n");
        exit(0);
    }
    char *filename = argc[1]; //argv[1];
    coff_header coffHeader;
    int coff_fd = open( filename, O_RDONLY ); //coff file descriptor
    printf("\nFile: %s\n\n", filename);
    read_coff_header( &coffHeader, coff_fd );

    close(coff_fd);

    printf("Process Complete.\nTerminating..\n");

    return EXIT_SUCCESS;
}

void read_coff_header(coff_header* header, int handle) {


    assert(header != NULL);
    lseek(handle, OFFSET, SEEK_CUR);
    read(handle, &header->offset, 4);
    lseek(handle, header->offset, SEEK_SET);
    read(handle, &header->sig, 4);

    assert(strcmp("PE\0\0", header->sig) == 0); //verify signature
    
    read( handle, &header->arch, 2 );
    read( handle, &header->section, 2 );
    read(handle, &header->time, 4);
    read(handle, &header->symbolStart, 4);
    read(handle, &header->symbolCount, 4);
    read(handle, &header->optHeaders, 2);
    read(handle, &header->characteristics, 2);


    // printlog
    printf("------------------------------------------\n");
    printf("Machine type: 0x%x\n", header->arch);
    printf("Number of sections: %d\n",header->section);
    printf("Created: %s", asctime(gmtime(&header->time)));
    printf("Symbol table start: 0x%08x\n" ,header->symbolStart); //0x00000000 (should be 0)
    printf("Number of symbols: %d\n", header->symbolCount);// (should be 0)
    printf("Size of optional header: %d\n" , header->optHeaders);
    printf("Characteristics: 0x%04x\n", header->characteristics);
    printf("------------------------------------------\n");
}
