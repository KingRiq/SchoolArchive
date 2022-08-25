#ifndef _A1_THREAD_HERDER_H
#define _A1_THREAD_HERDER_H

// signal handlers
void sigint_handler();
void sighup_handler();
void sigusr2_handler();
void killAll();
int read_file();

// Thread creation and deletion
void create(int);
void increase(int);
void decrease(int);


// Thread handling
void* work(void *);
void print();
void wait_prompt();
void updateCount();
#endif
