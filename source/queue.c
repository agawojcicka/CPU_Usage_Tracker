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
    pthread_mutex_lock(&RAmutex);
    ++q->size;
    if(q->size > 1) 
        sem_post(&RAsem);
    pthread_mutex_unlock(&RAmutex);
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
    pthread_mutex_lock(&APmutex);
    ++q->size;
    sem_post(&APsem);
    pthread_mutex_unlock(&APmutex);
}

cpuStat* DequeueRA(queueRA *q)
{
    nodeRA *tmp = q->head;
    cpuStat *result = tmp->value;
    q->head = q->head->next;
    if(q->head == NULL) 
        q->tail = NULL;
    
    free(tmp);
    pthread_mutex_lock(&RAmutex);
    --q->size;
    sem_wait(&RAsem);
    pthread_mutex_unlock(&RAmutex);
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
    pthread_mutex_lock(&APmutex);
    --q->size;
    sem_wait(&APsem);
    pthread_mutex_unlock(&APmutex);
    return result;
}