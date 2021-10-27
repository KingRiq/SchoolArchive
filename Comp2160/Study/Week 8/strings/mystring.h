#ifndef _MY_STRING_H
#define _MY_STRING_H

typedef struct STRING my_string;
my_string *make_string(char *);
void destroy_string(my_string *);
char char_at(my_string *,int);
void split(my_string *, char *,my_string *i[]);
char *get_content(my_string *);
#endif
