#include <stdio.h>
#include <string.h>

/**
 * WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARN
 *
 *                  DO NOT EVER USE THIS CODE
 *
 *
 *                  ANYWHERE
 *
 *
 *                  EVER
 *
 * WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARN
 *
 * This is adapted from "Buffer Overflow Attack Explained with a C Program
 * Example" by Nguyen Tien Su.
 *
 * https://blogchiasekienthuc.wordpress.com/2015/11/25/buffer-overflow-attack-explained-with-a-c-program-example/
 */
int main(void)
{
    int success = 0;
    char password[15];

    printf("\nEnter your password: ");
    scanf("%s", password);

    if (strcmp(password, "hunter2"))
    {
        printf("Wrong password\n");
    }
    else
    {
        printf("Correct password!\n");
        success = 1;
    }

    if (success)
    {
        printf("Access granted to super secret hideout.\n");
    }

    return 0;
}
