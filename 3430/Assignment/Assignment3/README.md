Eriq Hampton 7852830
Professor: Robert Guderian
Assignment 3

*This README contains both compilation, and run instructions.*

#### Contents: Makefile, README.md, a3q1.c, queue.h, taskmaker.py, tasks.txt, a3q0.c, processLine.h, schedule.c, timefunct.h*

## Thing you should know
I was not able to complete the assignment reliably. I found that my code segmentation faulted randomly and I did want to risk a 0. At least I could spare some marks by submitting a non-conurrent version. So a3q1 is the noncurrent version and I hope that runs smoothly. a3q0 is my concurrent version which I cannot get to work reliably. You may run it and it may work, but that is not always the case.
## Report

When I had it working concurrently I noticed that the more CPU's I added, the more my averages increased in both fields. This may be because there are so many cpu's caught in lock acquisition that it somehow takes longer. When multithreading 2-4 CPU's that seemed to have the best performance. 1 CPU is just sequential and 4+ resulted in a larger turnaround and response time respectively. Whe I changed the value of S the IO tasks turnaround time would get higher depending on the value of S. When S was tasks had an even distribution but the turnaround time would be much higher. when S was high the IO tasks and short tasks would finish much quicker and the longer tasks remained at the end of the queue when I dequeue'd them. 

## Compilation Instructions:
Type `make` to compile.
Type `make run` to run everything with my default arguments
Type `make clean` to remove all the executeable files and .txt files.


## How to run:
## Make sure there is a .txt file in the directory
For *a3q1*  the sequential version [which is my true submission]
Type `./a3q1 4 5000 tasks.txt`

For *a3q0*  the concurrent version (which doesnt work)
Type `./a3q0 4 5000 tasks.txt`

