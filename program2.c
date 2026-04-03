/*
 * Program: List Files Created in a Specific Month
 *
 * Description:
 * Write a C program to display all files from the current directory
 * that were created (inode change time) in a given month.
 *
 * Usage:
 *   ./a.out <Month>
 *
 * Example:
 *   ./a.out Jan
 *   ./a.out Mar
 *
 * Note:
 * Month should be in 3-letter format (Jan, Feb, Mar, etc.)
 */

#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char *argv[])
{
    DIR *dp;
    struct dirent *ep;
    struct stat sb;
    char *time_str;
    char day[10], month[10];
    int found = 0;

    // Check arguments
    if (argc != 2)
    {
        printf("Usage: %s <Month>\n", argv[0]);
        return 1;
    }

    dp = opendir(".");
    if (dp == NULL)
    {
        perror("opendir");
        return 1;
    }

    while ((ep = readdir(dp)) != NULL)
    {
        // Get file information
        if (stat(ep->d_name, &sb) == -1)
        {
            perror("stat");
            continue; // skip this file instead of exiting
        }

        // Convert time to string
        time_str = ctime(&sb.st_ctime);

        // Extract day and month
        sscanf(time_str, "%s %s", day, month);

        // Compare month
        if (strcmp(month, argv[1]) == 0)
        {
            found = 1;
            printf("%-20s %s", ep->d_name, time_str);
        }
    }

    if (!found)
    {
        printf("No files found for month: %s\n", argv[1]);
    }

    closedir(dp);
    return 0;
}

/*
------------------------------------------------------------
Concepts Used
------------------------------------------------------------

1) opendir() / readdir()
   - Used to read directory contents.

2) stat()
   - Retrieves file metadata (size, time, permissions, etc.)

3) st_ctime
   - Represents inode change time (NOT actual creation time in Linux)

4) ctime()
   - Converts time to readable format:
     Example: "Wed Apr  3 10:20:30 2026"

5) sscanf()
   - Extracts month from time string

------------------------------------------------------------
Important Note:
------------------------------------------------------------
Linux does NOT store actual file creation time.
st_ctime = last metadata change time.

So this program checks:
→ when file status last changed (NOT strictly creation)

------------------------------------------------------------
*/