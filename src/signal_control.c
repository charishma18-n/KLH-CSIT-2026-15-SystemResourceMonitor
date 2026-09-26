#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "signal_control.h"

volatile sig_atomic_t signal_received = 0;

void signal_handler(int signal_number)
{
    if (signal_number == SIGINT)
    {
        signal_received = 1;
    }
}

void show_signal_control()
{
    printf("\n========================================\n");
    printf("           SIGNAL CONTROL\n");
    printf("========================================\n");

    signal(SIGINT, signal_handler);

    printf("SIGINT handler registered successfully.\n");
    printf("Process ID: %d\n", getpid());
    printf("Press Ctrl+C to test signal handling.\n");

    signal_received = 0;

    while (!signal_received)
    {
        pause();
    }

    printf("\nSIGINT received!\n");
    printf("Signal handled successfully by the monitoring tool.\n");
    printf("Returning to main menu...\n");

    signal(SIGINT, SIG_DFL);
}
