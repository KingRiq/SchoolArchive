Eriq Hampton 7852830
Professor: Robert Guderian
Lab1

*This README contains both compilations, run instructions, and the answers to question  2 at the bottom of this document*

#### Contents: processes.c, threads.c, pe.c, Makefile, README.md

`Notes: I did not use locking for the counter variable in processes.c. So sometimes the parent process gets flooded. You will see my many attempts to slow down processes so that the Parent can count efficiently. This was what gave me consistent success. If it does not run at N processes the first time. I believe it will work a second time. My computer sometimes could not handle the number of processes being created at once. I hope this does not cause trouble. I was also told not to include putty.exe so I have not.`

  

## Compilation Instructions:
Type `make` to compile.
Type `make run` to run everything it with my default arguments. (For ease)
Type 'make clean' to remove all the executeable files and the picture *threads* downloads.

  

## How to run:
For *pe.c*  + the name of the file being read is expected.
`./pe putty.exe` is an example of acceptable input.

For processes.c a positive integer argument is expected and will exit otherwise.

`./processes 8` without quotations is acceptable input

For threads.c simply type 
  `./threads` and it will run.


## Syscalls I used for processes.c
In processes.c I have called the getpid, getppid to get the current process and parent proccess IDs. The kill system call, which signals a process. The wait() syscall, which makes the calling process wait until a child process has finished. I have implicitly used the sigaction syscall to signal both the parent and child processes respectively using signal and raise. The sleep system calls using usleep and sleep. Fork which creates a process and exit() to exit the program.

  
#### Syscalls:
Kill
Wait
signal, raise (which I assume calls sigaction)
sleep
fork
exit
getpid
getppid

  
## Using Strace
This is pretty cool. You can see execvp used to start the program. Is this done by the parent of the parent we are creating? (Our shell?) Other syscalls I see are things like mmap, clone, open, and write. Which the OS uses to write a copy of a parent process into the child process into the hardware's memory so it can run the child processes properly. Stat is used also which I am not sure what it does completely but I think it just tells us about the file we need. mprotect probably works like malloc but I assume it protects the memory allocated. munmap() unmaps the memory the OS specified for those processes. Close which closes a file.

  
#### Syscalls
execvp
mmap
clone
open
write
mprotect
stat
close
