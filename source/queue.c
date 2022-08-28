#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>


#include "queue.h"
#include "cpu_stat.h"
#include "global_var.h"

void QueueRAInit(queueRA *q)
{
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
}

void QueueAPInit(queueAP *q)
{
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
}
void EnqueueRA(cpuStat *value, queueRA *q)
{
    nodeRA *newNode = malloc(sizeof(nodeRA));
    newNode->value = value;
    newNode->next = NULL;

    if(q->tail != NULL)
    {
        q->tail->next = newNode;
    }
    q->tail = newNode;
    if(q->head == NULL)
    {
        q->head = newNode;
    }
    ++q->size;
}
void EnqueueAP(cpuUsage *value, queueAP *q)
{
    nodeAP *newNode = malloc(sizeof(nodeAP));
    newNode->value = value;
    newNode->next = NULL;

    if(q->tail != NULL)
    {
        q->tail->next = newNode;
    }
    q->tail = newNode;
    if(q->head == NULL)
    {
        q->head = newNode;
    }
    ++q->size;
}

cpuStat* DequeueRA(queueRA *q)
{
    nodeRA *tmp = q->head;
    cpuStat *result = tmp->value;
    q->head = q->head->next;
    if(q->head == NULL) 
        q->tail = NULL;
    
    free(tmp);
    --q->size;
    return result;
}

cpuStat* PeekRA(queueRA *q)
{
    cpuStat *result = q->head->value;
    return result;
}
cpuUsage* DequeueAP(queueAP *q)
{
    nodeAP *tmp = q->head;
    cpuUsage *result = tmp->value;
    q->head = q->head->next;
    if(q->head == NULL) 
        q->tail = NULL;
    
    free(tmp);
    --q->size;
    return result;
}