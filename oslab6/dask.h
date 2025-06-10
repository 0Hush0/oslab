#include<iostream>
#include<iomanip>
#include<malloc.h>

class DiskArm {
public:
    DiskArm();
    ~DiskArm();
    void InitSpace(char* MethodName); // 初始化寻道记录
    void Report();                    // 报告算法执行情况
    void FCFS();                      // 先来先服务算法
    void SSTF();                      // 最短寻道时间优先
    void SCAN();                      // 电梯扫描算法
    void CSCAN();                     // 循环扫描算法
    void LOOK();                      // 改进的电梯算法

private:
    int* Request;          // 磁盘请求道号
    int* Cylinder;          // 工作柱面道号
    int RequestNumber;      // 磁盘请求数
    int CurrentCylinder;    // 当前道号
    int SeekDirection;      // 磁头方向
    int SeekNumber;         // 移臂总数
    int SeekChange;         // 磁头调头数
};
