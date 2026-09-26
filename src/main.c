#include <stdio.h>
#include "system_info.h"
#include "cpu_monitor.h"
#include "memory_monitor.h"
#include "process_monitor.h"
#include "disk_monitor.h"
#include "ipc_monitor.h"
#include "thread_monitor.h"
#include "signal_control.h"
void display_menu()
{
    printf("\n");
    printf("========================================\n");
    printf("     LINUX SYSTEM RESOURCE MONITOR\n");
    printf("========================================\n");
    printf("1. System Information\n");
    printf("2. CPU Monitoring\n");
    printf("3. Memory Monitoring\n");
    printf("4. Process Monitoring\n");
    printf("5. File and Disk Monitoring\n");
    printf("6. IPC Monitoring\n");
    printf("7. Thread and Synchronization\n");
    printf("8. Signal Control\n");
    printf("9. Exit\n");
    printf("========================================\n");
}

int main()
{
    int choice;

    while (1)
    {
        display_menu();

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
    		show_system_info();
    		break;

            case 2:
    		show_cpu_usage();
    		break;

            case 3:
    		show_memory_usage();
    		break;

            case 4:
                show_processes();
    		break;

            case 5:
                 show_disk_usage();
    		break;

            case 6:
                show_ipc_monitor();
    		break;

            case 7:
                show_thread_monitor();
    		break;

            case 8:
                 show_signal_control();
    		 break;

            case 9:
                printf("\nExiting program...\n");
                return 0;

            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    }

    return 0;
}
