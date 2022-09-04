#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#include "cpu_stat.h"
#include "queue.h"
#include "global_var.h"
#include "printer.h"

void* Print(void *arg)
{
    printf("printer start\n");

    cpuUsage *tmp = DequeueAP(&analysePrintQueue);
    for (int i = 0; i < cpuCount; i++)
    {
        printf("%s\t%lf\n", tmp[i].name, tmp[i].value);
    }
    printf("\n");
    
    printf("printer stop\n");
}