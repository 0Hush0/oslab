/*
 * Filename : ipc.h
 * copyright : (C) 2006 by zhonghonglie
 * Function : 声明 IPC 机制的函数原型和全局变量
 */
#ifndef IPC_H  // 添加头文件保护
#define IPC_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#define BUFSZ 256

// 函数原型声明
int get_ipc_id(char* proc_file, key_t key);
char* set_shm(key_t shm_key, int shm_num, int shm_flag);
int set_msq(key_t msq_key, int msq_flag);
int set_sem(key_t sem_key, int sem_val, int sem_flag);
int down(int sem_id);
int up(int sem_id);

// 共用体和结构体声明
typedef union semuns {
    int val;
} Sem_uns;

typedef struct msgbuf {
    long mtype;
    char mtext[1];
} Msg_buf;

// 全局变量声明（使用 extern）
extern key_t buff_key;
extern int buff_num;
extern char* buff_ptr;

extern key_t pput_key;
extern int pput_num;
extern int* pput_ptr;

extern key_t cget_key;
extern int cget_num;
extern int* cget_ptr;

extern key_t prod_key;
extern key_t pmtx_key;
extern int prod_sem;
extern int pmtx_sem;

extern key_t cons_key;
extern key_t cmtx_key;
extern int cons_sem;
extern int cmtx_sem;

extern int sem_val;
extern int sem_flg;
extern int shm_flg;

#endif // IPC_H
