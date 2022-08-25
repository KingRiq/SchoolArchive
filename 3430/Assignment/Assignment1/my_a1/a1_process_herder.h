#ifndef _A1_PROCESS_HERDER_H
#define _A1_PROCESS_HERDER_H

// read config
int read_file();

// signal handlers
void sighup_handler();
void sigint_handler();
void sigusr2_handler();

// process creation and deletion
void create(int);
void increase(int);
void decrease(int);
void killAll();

// process handling
void print();
void work();
void wait_prompt();
void updateCount();
#endif
