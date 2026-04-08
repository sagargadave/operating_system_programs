/*
 * Program: Create a File with a Hole (Sparse File)
 *
 * Description:
 * Write a C program to create a file with a hole using lseek().
 * The hole is created by skipping bytes without writing data.
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
    int fd;

    char b1[] = "Welcome";
    char b2[] = "Computer Science";

    // Create file
    fd = creat("file_with_hole.txt", 0644);
    if (fd < 0)
    {
        perror("creat");
        exit(EXIT_FAILURE);
    }

    // Write first string
    if (write(fd, b1, strlen(b1)) != strlen(b1))
    {
        perror("write b1");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Create hole of 100 bytes
    if (lseek(fd, 100, SEEK_CUR) == -1)
    {
        perror("lseek");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Write second string
    if (write(fd, b2, strlen(b2)) != strlen(b2))
    {
        perror("write b2");
        close(fd);
        exit(EXIT_FAILURE);
    }

    close(fd);

    printf("File with hole created successfully.\n");

    return 0;
}

/*
------------------------------------------------------------
Concept: File Hole (Sparse File)
------------------------------------------------------------

- A "hole" is a gap in a file where no data is written.
- Created using lseek().

Example:
    write → lseek → write

- The skipped region is NOT stored physically on disk.

------------------------------------------------------------
Important Points:
------------------------------------------------------------

1) File size increases
2) Disk usage remains small
3) Holes read as '\0' (null bytes)

------------------------------------------------------------
*/