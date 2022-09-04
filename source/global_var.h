#ifndef GLOBAL_VAR_H
#define GLOBAL_VAR_H

#include <semaphore.h>
#include "queue.h"

extern pthread_mutex_t RAmutex, APmutex;
extern sem_t RAsem, APsem;
extern queueRA readAnalyseQueue;
extern queueAP analysePrintQueue;
extern int cpuCount;

#endif //GLOBAL_VAR_H