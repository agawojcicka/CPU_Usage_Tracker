#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#include "global_var.h"
#include "reader.h"

void* Read(void *arg)
{
    printf("reader start\n");

    FILE *fp, *cpuData;
    cpuStat tmp;
    int count;

    system("grep -c cpu /proc/stat > howmany.txt");    
    fp = fopen("howmany.txt", "r");
    if(!fp) exit(EXIT_FAILURE);
    fscanf(fp, "%d", &cpuCount);
    fclose(fp);
    system("rm howmany.txt");

    cpuStat *cpus = malloc(cpuCount*sizeof(cpuStat));

    system("grep cpu /proc/stat > cpustat.txt");
    cpuData = fopen("cpustat.txt", "r");
    if(!cpuData) exit(EXIT_FAILURE);
    for (int i = 0; i < cpuCount; i++) 
    {
        fscanf(cpuData, "%s %d %d %d %d %d %d %d %d %d %d", &tmp.name[0], &tmp.user, &tmp.nice, &tmp.system,
                                                            &tmp.idle, &tmp.iowait, &tmp.irq, &tmp.softirq,
                                                            &tmp.steal, &tmp.guest, &tmp.guestNice);
        
        *(cpus + i) = tmp;
             
    }
    EnqueueRA(cpus, &readAnalyseQueue);
    sleep(1);

    printf("reader stop\n");
}