#ifndef CPU_STAT_H
#define CPU_STAT_H

typedef struct cpuStat{
    char name[5];
    int user;
    int nice;
    int system;
    int idle;
    int iowait;
    int irq;
    int softirq;
    int steal;
    int guest;
    int guestNice;

}cpuStat;

typedef struct cpuUsage{
    char name[5];
    double value;
}cpuUsage;


#endif //CPU_STAT_H