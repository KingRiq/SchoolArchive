Eriq Hampton 7852830
Professor: Robert Guderian
Assignment 4

*This README contains both compilation, and run instructions.*

#### Contents: Makefile, README.md, exfat.c, exfat.h, queue.h*

## Compilation Instructions:
1. Type `make` to compile.
2. Type `make run` to run everything with my default arguments (for ease)
3. Type `make clean` to remove all the executeable files and .img files and .txt files. (and .exfat files)

*Note* this program will not execute if the correct arguments are not entered, a bad volume is used, or the wrong volume type.

### Notes about the Assignment
I was able to get *info* and *list* working but *get* is incomplete it will search for the file but it will not print its contents. This is where I unfortunately had to stop. 

if you put a `/` before the path it will not search properly this was the last thing I was working on before proceeding to search in the stream extension of the file's contents that we are looking for but was unsuccessful. I must warn you that because it is incomplete there is a bit of undefined behavior that I wanted to make you aware of before hand but it should run smoothly.

if you run `./exfat a4image.exfat get text/numbers/300.txt` *after* `make` you will see what I mean.

Lastly, I have hit disk quota so I did not include the volumes because of their size, I hope this is ok.


## How to run:
## Make sure there is a proper .img/.exfat file in the directory
For *exfat* 
Type `./exfat a4image.exfat get path/to/file` is an example of acceptable input for the get command. the additional argument must be an img/exfat file *and* an absolute path
Type `./exfat a4image.exfat info ` is an example of acceptable input for the info command. the additional argument must be an img/exfat file
Type `./exfat a4image.exfat list ` is an example of acceptable input for the list command. the additional argument must be an img/exfat file


