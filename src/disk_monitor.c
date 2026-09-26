#include <stdio.h>
#include <sys/statvfs.h>
#include "disk_monitor.h"

void show_disk_usage()
{
    struct statvfs disk;

    if (statvfs("/", &disk) != 0)
    {
        perror("statvfs");
        return;
    }

    unsigned long long total_space =
        (unsigned long long)disk.f_blocks * disk.f_frsize;

    unsigned long long free_space =
        (unsigned long long)disk.f_bfree * disk.f_frsize;

    unsigned long long available_space =
        (unsigned long long)disk.f_bavail * disk.f_frsize;

    unsigned long long used_space =
        total_space - free_space;

    printf("\n========================================\n");
    printf("        FILE AND DISK MONITORING\n");
    printf("========================================\n");

    printf("File System      : /\n");
    printf("Total Space      : %llu MB\n",
           total_space / (1024 * 1024));

    printf("Used Space       : %llu MB\n",
           used_space / (1024 * 1024));

    printf("Free Space       : %llu MB\n",
           free_space / (1024 * 1024));

    printf("Available Space  : %llu MB\n",
           available_space / (1024 * 1024));

    printf("========================================\n");
}
