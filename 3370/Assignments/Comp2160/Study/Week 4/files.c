#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
#define SIZE 100
    FILE *f = fopen("beowulf.txt", "r");
    char line[SIZE];
    int last_char_idx = -1;

    if (f == NULL)
    {
        printf("File does not exist.\n");
        exit(1);
    }

    while (fgets(line, SIZE, f) != NULL) 
    {
        // last char
        last_char_idx = strlen(line) - 2;
        if (line[last_char_idx] == '\n')
            line[last_char_idx] = '\0'; // strip trailing newlines
        printf("The line is %s\n", line);
        sleep(2);
    }

    return 0;
}
