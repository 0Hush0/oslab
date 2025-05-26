#ifndef IPC_SMOKE_H
#define IPC_SMOKE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define TOBACCO 0
#define PAPER 1
#define GLUE 2

// 信号量键值
#define SEM_TOBACCO 1111
#define SEM_PAPER 2222
#define SEM_GLUE 3333
#define SEM_AGENT 4444

// 声明全局信号量 ID
extern int sem_tobacco;
extern int sem_paper;
extern int sem_glue;
extern int sem_agent;

// 信号量函数
int set_sem(key_t key, int init_val);
void down(int semid);
void up(int semid);

#endif

