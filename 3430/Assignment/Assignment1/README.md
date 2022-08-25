Eriq Hampton 7852830
Professor: Robert Guderian
Assignment 1

*This README contains both compilations, run instructions.*

#### Contents: elf_reader.c, a1_process_herder.c, a1_thread_herder.c, elf_reader.h, a1_process_herder.h, a1_thread_herder.h, Makefile, README.md, config.txt*

`Notes: I have included in my programs a print function that is called after every change, which will show you the list of child processes/threads. I also have a function that prints the parent ID at the bottom after every change to make it easier to test. This list can get messy with many processes/threads but I hope it is clear.`  

## Compilation Instructions:
Type `make` to compile.
`make run` is excluded due to the nature of the assignments during runtime
Type 'make clean' to remove all the executeable files.

  

## How to run:
For *elf_reader* 
Type ./elf_reader + the name of the file to be read.
`./elf_reader hello.out64` is an example of acceptable input.

### There must be a config.txt file inside this directory with a positive integer in it for the program to run properly for both a1_process_herder and a1_thread_herder respectively.
For *a1_process_herder* 
Type `./a1_process_herder`


For *a1_thread_herder*
Type `./a1_thread_herder`


