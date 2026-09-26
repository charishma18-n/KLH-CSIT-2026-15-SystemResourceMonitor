#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include "process_monitor.h"

void show_processes()
{
    DIR *directory;
    struct dirent *entry;
    int count = 0;

    directory = opendir("/proc");

    if (directory == NULL)
    {
        perror("Unable to open /proc");
        return;
    }

    printf("\n========================================\n");
    printf("          PROCESS MONITORING\n");
    printf("========================================\n");
    printf("%-10s %-25s\n", "PID", "PROCESS");
    printf("----------------------------------------\n");

    while ((entry = readdir(directory)) != NULL && count < 15)
    {
        if (isdigit(entry->d_name[0]))
        {
            char path[512];
            char process_name[256];
            FILE *file;

            snprintf(path, sizeof(path),
                     "/proc/%s/comm", entry->d_name);

            file = fopen(path, "r");

            if (file != NULL)
            {
                if (fgets(process_name,
                          sizeof(process_name), file) != NULL)
                {
                    process_name[strcspn(process_name, "\n")] = '\0';

                    printf("%-10s %-25s\n",
                           entry->d_name,
                           process_name);

                    count++;
                }

                fclose(file);
            }
        }
    }

    closedir(directory);

    printf("----------------------------------------\n");
    printf("Processes displayed: %d\n", count);
    printf("========================================\n");
}
