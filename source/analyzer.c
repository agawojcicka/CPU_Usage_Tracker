#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#include "queue.h"
#include "global_var.h"
#include "cpu_stat.h"
#include "analyzer.h"

void* Analyse(void *arg)
{
    printf("analyser start\n");

    cpuStat *state0, *state1;  
    cpuUsage *usg = malloc(cpuCount*sizeof(cpuUsage));
    int total = 0, prevTotal = 0, idle = 0, prevIdle = 0;
    double totalDiff = 0.0, totalIdleDiff = 0.0;
    double result = 0.0;

    state0 = DequeueRA(&readAnalyseQueue);
    state1 = PeekRA(&readAnalyseQueue);

    for (int i = 0; i < cpuCount; i++)
    {
        cpuUsage tmp;
        total = state1[i].user + state1[i].nice + state1[i].system + state1[i].idle + state1[i].iowait 
            + state1[i].irq + state1[i].softirq + state1[i].steal + state1[i].guest + state1[i].guestNice;
        prevTotal = state0[i].user + state0[i].nice + state0[i].system + state0[i].idle + state0[i].iowait 
            + state0[i].irq + state0[i].softirq + state0[i].steal + state0[i].guest + state0[i].guestNice;
        idle = state1[i].idle + state1[i].iowait;
        prevIdle = state0[i].idle + state0[i].iowait;
        totalDiff = (double)total - (double)prevTotal;
        totalIdleDiff = (double)idle - (double)prevIdle;

        result = (totalDiff - totalIdleDiff)*100/totalDiff;
            
        strcpy(tmp.name, state0[i].name);
        tmp.value = result;
        *(usg + i) = tmp;
            
    }
    EnqueueAP(usg, &analysePrintQueue);

    printf("analyser stop\n");
}