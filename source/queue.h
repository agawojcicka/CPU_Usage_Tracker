#ifndef QUEUE_H
#define QUEUE_H

#include "cpu_stat.h"

typedef struct nodeRA{
    cpuStat *value;
    struct nodeRA *next;
}nodeRA;

typedef struct queueRA{
    nodeRA *head;
    nodeRA *tail;
    int size;
}queueRA;

typedef struct nodeAP{
    cpuUsage *value;
    struct nodeAP *next;
}nodeAP;

typedef struct queueAP{
    nodeAP *head;
    nodeAP *tail;
    int size;
}queueAP;

void QueueRAInit(queueRA *q);
void QueueAPInit(queueAP *q);
void EnqueueRA(cpuStat* value, queueRA *q);
void EnqueueAP(cpuUsage* value, queueAP *q);
cpuStat* DequeueRA(queueRA *q);
cpuUsage* DequeueAP(queueAP *q);
cpuStat* PeekRA(queueRA *q);

#endif //QUEUE_H