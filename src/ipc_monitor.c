#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "ipc_monitor.h"

void show_ipc_monitor()
{
    int pipe_fd[2];
    pid_t pid;
    char message[] = "System monitoring data sent through IPC";
    char buffer[100];

    if (pipe(pipe_fd) == -1)
    {
        perror("pipe");
        return;
    }

    pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return;
    }

    if (pid > 0)
    {
        close(pipe_fd[0]);

        write(pipe_fd[1], message, strlen(message) + 1);

        close(pipe_fd[1]);

        wait(NULL);

        printf("\nParent process completed IPC communication.\n");
    }
    else
    {
        close(pipe_fd[1]);

        read(pipe_fd[0], buffer, sizeof(buffer));

        close(pipe_fd[0]);

        printf("\n========================================\n");
        printf("             IPC MONITORING\n");
        printf("========================================\n");
        printf("Parent -> Child Message:\n");
        printf("%s\n", buffer);
        printf("========================================\n");
	_exit(0);
    }
}
