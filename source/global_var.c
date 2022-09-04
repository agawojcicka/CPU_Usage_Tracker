#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#include "cpu_stat.h"
#include "global_var.h"

pthread_mutex_t RAmutex, APmutex;
sem_t RAsem, APsem;

queueRA readAnalyseQueue;
queueAP analysePrintQueue;
int cpuCount;


