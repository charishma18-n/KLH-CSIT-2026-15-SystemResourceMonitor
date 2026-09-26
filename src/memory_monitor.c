#include <stdio.h>
#include <string.h>
#include "memory_monitor.h"

void show_memory_usage()
{
    FILE *file;
    char line[256];

    unsigned long total_memory = 0;
    unsigned long free_memory = 0;
    unsigned long available_memory = 0;

    file = fopen("/proc/meminfo", "r");

    if (file == NULL)
    {
        perror("Unable to open /proc/meminfo");
        return;
    }

    while (fgets(line, sizeof(line), file))
    {
        if (strncmp(line, "MemTotal:", 9) == 0)
        {
            sscanf(line, "MemTotal: %lu kB", &total_memory);
        }
        else if (strncmp(line, "MemFree:", 8) == 0)
        {
            sscanf(line, "MemFree: %lu kB", &free_memory);
        }
        else if (strncmp(line, "MemAvailable:", 13) == 0)
        {
            sscanf(line, "MemAvailable: %lu kB", &available_memory);
        }
    }

    fclose(file);

    unsigned long used_memory =
        total_memory - free_memory;

    printf("\n========================================\n");
    printf("          MEMORY MONITORING\n");
    printf("========================================\n");

    printf("Total Memory     : %lu MB\n", total_memory / 1024);
    printf("Used Memory      : %lu MB\n", used_memory / 1024);
    printf("Free Memory      : %lu MB\n", free_memory / 1024);
    printf("Available Memory : %lu MB\n", available_memory / 1024);

    printf("========================================\n");
}
