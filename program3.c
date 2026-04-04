/*
 * Program: Unnamed Pipe (Parent reads, Child writes)
 *
 * Description:
 * Create an unnamed pipe. The child process writes data into the pipe,
 * and the parent process reads from it.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main()
{
    int fd[2];
    pid_t pid;
    char buffer[100];

    // Create pipe
    if (pipe(fd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    // CHILD PROCESS
    if (pid == 0)
    {
        close(fd[0]); // ❗ close unused read end

        char msg[] = "Hello parent process";

        printf("CHILD: Writing to pipe...\n");

        if (write(fd[1], msg, strlen(msg)) == -1)
        {
            perror("write");
            exit(EXIT_FAILURE);
        }

        close(fd[1]); // done writing
        printf("CHILD: Exiting\n");
    }

    // PARENT PROCESS
    else
    {
        close(fd[1]); // ❗ close unused write end

        printf("PARENT: Reading from pipe...\n");

        int n = read(fd[0], buffer, sizeof(buffer) - 1);
        if (n == -1)
        {
            perror("read");
            exit(EXIT_FAILURE);
        }

        buffer[n] = '\0'; // null terminate

        printf("PARENT: Received -> \"%s\"\n", buffer);

        close(fd[0]);
        wait(NULL);

        printf("PARENT: Exiting\n");
    }

    return 0;
}

/*
------------------------------------------------------------
Concept: Unnamed Pipe
------------------------------------------------------------

- A pipe is used for communication between related processes
  (parent ↔ child).

- It is half-duplex (one direction only).

Syntax:
    int pipe(int fd[2]);

fd[0] → Read end
fd[1] → Write end

------------------------------------------------------------
IMPORTANT RULE (Very Common Viva Question)
------------------------------------------------------------

Child:
    close(fd[0]);  // don't read
Parent:
    close(fd[1]);  // don't write

If not closed:
    → Can cause deadlock or unexpected behavior

------------------------------------------------------------
fork() Return Values:
------------------------------------------------------------

< 0  → Error
= 0  → Child process
> 0  → Parent (returns child PID)

------------------------------------------------------------
*/