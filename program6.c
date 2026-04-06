/*
 * Program: Display File Properties using stat()
 *
 * Description:
 * Write a C program to display file properties such as:
 * - Inode number
 * - Number of hard links
 * - File permissions
 * - File size
 * - Last access time
 * - Last modification time
 *
 * Usage:
 *   ./a.out <filename>
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char *argv[])
{
    struct stat info;

    // Check arguments
    if (argc != 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Get file information
    if (stat(argv[1], &info) == -1)
    {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    printf("File: %s\n", argv[1]);

    // Inode number
    printf("Inode Number       : %ld\n", (long)info.st_ino);

    // File size
    printf("File Size          : %lld bytes\n", (long long)info.st_size);

    // Number of hard links
    printf("Hard Links         : %ld\n", (long)info.st_nlink);

    // Last access time
    printf("Last Access Time   : %s", ctime(&info.st_atime));

    // Last modification time
    printf("Last Modify Time   : %s", ctime(&info.st_mtime));

    // Permissions
    printf("File Permissions   : ");

    printf((info.st_mode & S_IRUSR) ? "r" : "-");
    printf((info.st_mode & S_IWUSR) ? "w" : "-");
    printf((info.st_mode & S_IXUSR) ? "x" : "-");

    printf((info.st_mode & S_IRGRP) ? "r" : "-");
    printf((info.st_mode & S_IWGRP) ? "w" : "-");
    printf((info.st_mode & S_IXGRP) ? "x" : "-");

    printf((info.st_mode & S_IROTH) ? "r" : "-");
    printf((info.st_mode & S_IWOTH) ? "w" : "-");
    printf((info.st_mode & S_IXOTH) ? "x" : "-");

    printf("\n");

    return 0;
}

/*
------------------------------------------------------------
Concept: stat() system call
------------------------------------------------------------

Syntax:
    int stat(const char *path, struct stat *buf);

Description:
    Retrieves information about a file and stores it in 'buf'.

Important Fields:
    st_ino   → Inode number
    st_size  → File size (bytes)
    st_nlink → Number of hard links
    st_mode  → File permissions
    st_atime → Last access time
    st_mtime → Last modification time

------------------------------------------------------------
Permission Bits:
------------------------------------------------------------
    S_IRUSR → Read by owner
    S_IWUSR → Write by owner
    S_IXUSR → Execute by owner

    S_IRGRP → Read by group
    S_IWGRP → Write by group
    S_IXGRP → Execute by group

    S_IROTH → Read by others
    S_IWOTH → Write by others
    S_IXOTH → Execute by others

------------------------------------------------------------
*/