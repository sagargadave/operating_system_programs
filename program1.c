/*
 * Program: Check File Existence in Current Directory
 *
 * Description:
 * Write a C program to check whether a given file is present
 * in the current directory or not.
 *
 * Usage:
 *   ./a.out filename
 *
 * Example:
 *   ./a.out test.txt
 */

#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    // Check if filename is provided
    if (argc != 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // access() checks file existence
    if (access(argv[1], F_OK) == 0)
    {
        printf("File '%s' exists in the current directory.\n", argv[1]);
    }
    else
    {
        printf("File '%s' does NOT exist in the current directory.\n", argv[1]);
    }

    return 0;
}

/*
------------------------------------------------------------
Function Used: access()
------------------------------------------------------------

Syntax:
    int access(const char *path, int amode);

Parameters:
    path  - Path to the file or directory.
    amode - Access mode to check:

        F_OK  : Check if file exists
        R_OK  : Check read permission
        W_OK  : Check write permission
        X_OK  : Check execute permission

Description:
    The access() function checks whether the file specified
    by 'path' exists and whether it can be accessed according
    to the mode specified by 'amode'.

    It uses the REAL user ID and group ID (not effective IDs).

Return Value:
    0   : File exists / permission granted
   -1   : File does not exist or permission denied

------------------------------------------------------------
*/