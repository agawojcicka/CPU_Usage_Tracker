#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>


#include "cpu_stat.h"
#include "queue.h"
#include "global_var.h"
#include "reader.h"
#include "analyzer.h"
#include "printer.h"

void main()
{
    QueueRAInit(&readAnalyseQueue);
    QueueAPInit(&analysePrintQueue);
    
    pthread_t reader, analyser, printer;

    pthread_create(&reader, NULL, &Read, NULL);
    pthread_create(&analyser, NULL, &Analyse, NULL);
    pthread_create(&printer, NULL, &Analyse, NULL);

    pthread_join(reader, NULL);
    pthread_join(analyser, NULL);
    pthread_join(printer, NULL); 
    
}