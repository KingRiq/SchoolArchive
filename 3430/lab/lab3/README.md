Eriq Hampton 7852830
Professor: Robert Guderian
Lab 3

*This README contains both compilation, and run instructions.*

#### Contents: pthread-lock.c, condition-vars.c, spin-lock.c, atomic-lock.c, lock-really.c, Makefile, README.md*

### Hypothesis for Atomic Variables:
I believe that making the lock variable atomic will make the concurrent threads more accurate but *not* correct. There is nothing enforcing concurrency during a context switch. The lock can be assigned to a thread and unlocked at any time but nothing is *explicitly* giving ownership of the lock to a particular thread. 

### After testing atomic-lock: 
It seems my hypothesis may be correct. I added an assert on line 48 in the unlock function (in atomic-lock). If the lock is set to 1 no other thread should be able to exit the while loop in the *lock* function. However the *(assert *lock ==1)* fails in the unlock function meaning the lock value was set to 0 at some point which couldn't happen unless it happened while the flags were being changed at the same time. Printf prints 1 every time if you replace the assert. There must be some sort of race condition between the reading of the atomic variable in lock function's *while* condition and the changing of the variable anywhere else. I made the counter variable atomic and it works. Probably because the only thing happening is that it is incrementing atomically each iteration.


### Q1 *Very generally, how do the system calls change when you switch from flag-based spin locks to atomic variables to atomic instructions?*
The system calls do not change at all between flag-based spin locks to atomic variables to atomic instructions. I guess the program is running the exact same system calls. What the hardware enforces *during* context switches must be driving the change perhaps. 

### Q2 *Does pthread_mutex_lock use any system calls? Create one more C program that replaces the spin locks with pthread_mutex_lock.*
No, it does not appear to be doing that, all of the system calls are the same.

### Q3 *Before you start, make a prediction: will your spin lock be faster, or pthread_mutex_lock?*
I personally think pthread_mutex_lock has a lot under the hood that is abstracted from us. That alone leads me to believe that pthread_mutex_lock will have *lower* performance than the spin locks.

#### Results:

*Note* I have removed all asserts for this test. I used them to convince myself things were happening the way I expect. So I have not omitted them within my solution, but I wanted to remove them for performance purposes.

**use `make time` to print similar results**
Times for each program:
spin-lock = 0:02.42
atomic-lock = 0:08.18
lock-really = 0:15.39
pthread = 0:09.7

It appears my prediction was wrong and pthread-lock performs better than lock-really.

## *Notes about Part 2*
So the instructions tells us that main signals *lowercase* but I was having an issue where main would send a signal before lowercase would even start so it would hang until the next word was entered and the same thing for *uppercase*. Another problem was it is never stated whether it *matters* that the threads heard the signal or not. I am not sure if signals are **allowed** to be missed. This is why I have excessive use of locks and condition variables to enforce that the signal was heard. My program is able to run concurrently but I am afraid that enforcing *meaningful* communication may mean my program is not fully concurrent. I interpretted it as (main signals lowercase -> lowercase receives signal and can proceed to do work). I would argue it is concurrent after the signals are heard though. I just wanted to communicate my intentions (although it may be wrong).

### Q4. *What may happen if lots of data is given quickly?*
There is a number of undefined behaviour, when large amounts of data is entered. Signals have to be set up prior otherwise a signal is never heard. A large read could throw off this timing; maybe even causing a deadlock. Each thread is subject to a circular wait if we're not careful. Threads could be doing anything at any time. We have a lock to ensure that our global buffer is never overwritten the same time but they could easily be read at different times because they were overwritten at any point. How do we know that this buffer is the correct one we are talking about? (This is why I have thread p1 pass a safe copy to p2) If we read directly from the buffer when trying to process the string before we have copied it over we will get an undefined string or a string that has already been processed from a previous iteration. This is why I ensure main waits for lower-case to *wait* before sending its signal and so on. This is also why I print the actual global buffer and not the copy it was passed.

## Compilation Instructions:
Type `make` to compile.
Type `make run` to run everything with my default arguments and write the output of strace into a respective .txt file (except condition-vars which will not use strace)
Type `make time` to run each "lock program" with the time command
Type `make clean` to remove all the executeable files and .txt files.


## How to run:
For *condition-vars* 
Type `./condition-vars`

For *spin-lock* 
Type `./spin-lock`

For *atomic-lock* 
Type `./atomic-lock`

For *lock-really* 
Type `./lockreally`

For *pthread-lock* 
Type `./pthread-lock`
