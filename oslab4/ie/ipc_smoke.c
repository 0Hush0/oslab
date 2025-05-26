#include "ipc_smoke.h"
#include <sys/sem.h>

// 定义全局信号量变量
int sem_tobacco;
int sem_paper;
int sem_glue;
int sem_agent;

// 设置信号灯初值
int set_sem(key_t key, int init_val) {
    int semid = semget(key, 1, IPC_CREAT | 0666);
    if (semid == -1) {
        perror("semget error");
        exit(1);
    }

    union semun {
        int val;
    } sem_val;
    sem_val.val = init_val;

    if (semctl(semid, 0, SETVAL, sem_val) == -1) {
        perror("semctl SETVAL error");
        exit(1);
    }

    return semid;
}

// P 操作
void down(int semid) {
    struct sembuf sop;
    sop.sem_num = 0;
    sop.sem_op = -1;
    sop.sem_flg = 0;
    if (semop(semid, &sop, 1) == -1) {
        perror("semop down error");
        exit(1);
    }
}

// V 操作
void up(int semid) {
    struct sembuf sop;
    sop.sem_num = 0;
    sop.sem_op = 1;
    sop.sem_flg = 0;
    if (semop(semid, &sop, 1) == -1) {
        perror("semop up error");
        exit(1);
    }
}

