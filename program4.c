/*
 * Program: List Files Starting with Given Prefix
 *
 * Description:
 * Write a C program that takes a string as an argument
 * and prints all file names in the current directory
 * that begin with that string.
 *
 * Usage:
 *   ./a.out <prefix>
 *
 * Example:
 *   ./a.out foo
 */

#include <stdio.h>
#include <string.h>
#include <dirent.h>

int main(int argc, char *argv[])
{
    DIR *d;
    struct dirent *dir;

    // Check argument
    if (argc != 2)
    {
        printf("Usage: %s <prefix>\n", argv[0]);
        return 1;
    }

    d = opendir(".");
    if (d == NULL)
    {
        perror("opendir");
        return 1;
    }

    while ((dir = readdir(d)) != NULL)
    {
        // Compare prefix
        if (strncmp(dir->d_name, argv[1], strlen(argv[1])) == 0)
        {
            printf("%s\n", dir->d_name);
        }
    }

    closedir(d);
    return 0;
}