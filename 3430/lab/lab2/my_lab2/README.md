Eriq Hampton 7852830
Professor: Robert Guderian
Lab 2

*This README contains both compilation, and run instructions.*

#### Contents: octopipe.c, Makefile, README.md*

`Notes: Freeing allocated char* line in process_Args resulted in execvp failing on Aviary machines so I excluded it`  

## Compilation Instructions:
Type `make` to compile.
Type `make run` to run everything with my default arguments. (For ease)
Type 'make clean' to remove all the executeable files.


## How to run:
For *octopipe* 
Type ./octopipe + "command2" "command3" to run.
`./octopipe "tr A-Z a-z" "wc -c"` is an example of acceptable input.
`./octopipe` *only* is not enough arguments and the program will ask to enter more then exit failure.

