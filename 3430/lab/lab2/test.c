#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int
main(int argc, char *argv[])
{
    pid_t child;
    int p[2], to_parent, from_child;
    int child_status;
    char buffer[1024];
    ssize_t nread;

    /* create a unidirectional pipe
     * - child process will write to p[0]
     * - parent process will read from p[1]
     */
    pipe(p);
    from_child = p[0];
    to_parent = p[1];

    child = fork();
    if (child == 0) {
        /* child */
        /* close parent end of pipe */
        close(from_child);
        /* close unnecessary file descriptors */
        close(STDIN_FILENO);
        /* redirect standard output & error to pipe */
        dup2(STDOUT_FILENO, to_parent);
        dup2(STDERR_FILENO, to_parent);
        /* exec or die */
        execlp("ls", "ls", "-l", NULL);
        exit(EXIT_FAILURE);
    }

    /* parent */
    /* close child end of pipe */
    close(to_parent);

    //printf("reading");
    /* read output from child until EOF */
    while ((nread=read(from_child, &buffer[0], sizeof(buffer))) > 0) {
        //write(STDOUT_FILENO, &buffer[0], nread);
        printf("ENTER\n");
    }
    buffer[0] = '\n';
    write(STDOUT_FILENO, &buffer[0], 1);
    close(from_child);

    /* wait for child */
    wait(&child_status);                                                                            /*mindlessly copied from stack overflow*/
    if (WIFEXITED(child_status)) {
        printf("child %lu exited with code %d\n",
            (unsigned long)child, WEXITSTATUS(child_status));
    } else if (WIFSIGNALED(child_status)) {
        printf("child %lu terminated due to signal #%d%s\n",
            (unsigned long)child, WTERMSIG(child_status),
            WCOREDUMP(child_status) ? ", core dumped" : "");
    } else if (WIFSTOPPED(child_status)) {
        printf("child %lu stopped due to signal #%d\n",
            (unsigned long)child, WSTOPSIG(child_status));
    }

    return 0;
}
