
/*
 * Program: Display File Properties using fstat()
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
 * This program uses fstat(), which works on an open file descriptor.
 *
 * Usage:
 *   ./a.out <filename>
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int fd;
    struct stat info;

    // Check argument
    if (argc != 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Open file
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    // Get file information using fstat()
    if (fstat(fd, &info) == -1)
    {
        perror("fstat");
        close(fd);
        return 1;
    }

    printf("File: %s\n", argv[1]);

    // Inode
    printf("Inode Number       : %ld\n", (long)info.st_ino);

    // Size
    printf("File Size          : %lld bytes\n", (long long)info.st_size);

    // Hard links
    printf("Hard Links         : %ld\n", (long)info.st_nlink);

    // Time details
    printf("Last Access Time   : %s", ctime(&info.st_atime));
    printf("Last Modify Time   : %s", ctime(&info.st_mtime));

    // File type + permissions
    printf("File Permissions   : ");

    // File type
    if (S_ISDIR(info.st_mode)) printf("d");
    else if (S_ISREG(info.st_mode)) printf("-");
    else printf("?");

    // Owner
    printf((info.st_mode & S_IRUSR) ? "r" : "-");
    printf((info.st_mode & S_IWUSR) ? "w" : "-");
    printf((info.st_mode & S_IXUSR) ? "x" : "-");

    // Group
    printf((info.st_mode & S_IRGRP) ? "r" : "-");
    printf((info.st_mode & S_IWGRP) ? "w" : "-");
    printf((info.st_mode & S_IXGRP) ? "x" : "-");

    // Others
    printf((info.st_mode & S_IROTH) ? "r" : "-");
    printf((info.st_mode & S_IWOTH) ? "w" : "-");
    printf((info.st_mode & S_IXOTH) ? "x" : "-");

    printf("\n");

    close(fd);
    return 0;
}

/*
------------------------------------------------------------
Concept: fstat()
------------------------------------------------------------

Syntax:
    int fstat(int fd, struct stat *buf);

Description:
    fstat() retrieves file information using a file descriptor
    instead of a file path.

Difference:
    stat()  → uses filename (path)
    fstat() → uses file descriptor

------------------------------------------------------------
Key Fields:
------------------------------------------------------------
    st_ino   → Inode number
    st_size  → File size
    st_nlink → Hard links count
    st_mode  → Permissions + file type
    st_atime → Last access time
    st_mtime → Last modification time

------------------------------------------------------------
*/