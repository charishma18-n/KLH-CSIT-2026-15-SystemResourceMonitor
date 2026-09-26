#include <stdio.h>
#include <sys/utsname.h>
#include "system_info.h"

void show_system_info()
{
    struct utsname info;

    if (uname(&info) == -1)
    {
        perror("uname");
        return;
    }

    printf("\n========================================\n");
    printf("          SYSTEM INFORMATION\n");
    printf("========================================\n");

    printf("System Name     : %s\n", info.sysname);
    printf("Node Name       : %s\n", info.nodename);
    printf("Kernel Release  : %s\n", info.release);
    printf("Kernel Version  : %s\n", info.version);
    printf("Architecture    : %s\n", info.machine);

    printf("========================================\n");
}
