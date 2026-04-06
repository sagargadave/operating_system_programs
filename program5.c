/*
/*
 * Program: Redirect Standard Output to a File
 *
 * Description:
 * Write a C program that redirects standard output (stdout)
 * to a file named "output.txt" using open() and dup2().
 *
 * Any printf() output will be written to the file instead of the screen.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
    int n1, n2, sum;
    int fd;

    // Open (or create) output.txt
    fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Redirect stdout to file
    if (dup2(fd, STDOUT_FILENO) < 0)
    {
        perror("dup2");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Now printf writes to output.txt instead of terminal
    printf("Enter two numbers:\n");
    scanf("%d %d", &n1, &n2);

    sum = n1 + n2;

    printf("Sum = %d\n", sum);

    close(fd);
    return 0;
}

/*
------------------------------------------------------------
Concepts Used
------------------------------------------------------------

1) open()
   - Opens or creates a file
   - Flags:
        O_WRONLY : write only
        O_CREAT  : create file if not exists
        O_TRUNC  : truncate file if exists
   - Mode:
        0644 → rw-r--r--

2) dup2(oldfd, newfd)
   - Redirects newfd to oldfd
   - Here:
        dup2(fd, STDOUT_FILENO)
        → stdout now points to output.txt

3) STDOUT_FILENO
   - File descriptor for standard output (1)

------------------------------------------------------------
Key Idea:
------------------------------------------------------------
Before dup2:
    printf → terminal

After dup2:
    printf → output.txt

------------------------------------------------------------
*/