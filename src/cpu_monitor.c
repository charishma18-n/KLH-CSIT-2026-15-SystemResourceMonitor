#include <stdio.h>
#include <unistd.h>
#include "cpu_monitor.h"

void get_cpu_times(unsigned long long *idle,
                   unsigned long long *total)
{
    FILE *file;
    char line[256];

    unsigned long long user;
    unsigned long long nice;
    unsigned long long system;
    unsigned long long idle_time;
    unsigned long long iowait;
    unsigned long long irq;
    unsigned long long softirq;
    unsigned long long steal;

    *idle = 0;
    *total = 0;

    file = fopen("/proc/stat", "r");

    if (file == NULL)
    {
        perror("Unable to open /proc/stat");
        return;
    }

    if (fgets(line, sizeof(line), file) != NULL)
    {
        sscanf(line, "cpu %llu %llu %llu %llu %llu %llu %llu %llu",
               &user, &nice, &system, &idle_time,
               &iowait, &irq, &softirq, &steal);

        *idle = idle_time + iowait;

        *total = user + nice + system + idle_time +
                 iowait + irq + softirq + steal;
    }

    fclose(file);
}

void show_cpu_usage()
{
    unsigned long long idle1;
    unsigned long long total1;
    unsigned long long idle2;
    unsigned long long total2;

    get_cpu_times(&idle1, &total1);

    sleep(1);

    get_cpu_times(&idle2, &total2);

    unsigned long long idle_difference = idle2 - idle1;
    unsigned long long total_difference = total2 - total1;

    double cpu_usage = 0.0;

    if (total_difference > 0)
    {
        cpu_usage =
            100.0 *
            (1.0 - ((double)idle_difference /
                    (double)total_difference));
    }

    printf("\n========================================\n");
    printf("             CPU MONITORING\n");
    printf("========================================\n");
    printf("CPU Usage       : %.2f%%\n", cpu_usage);
    printf("========================================\n");
}
