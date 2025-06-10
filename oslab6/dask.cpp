#include "dask.h"
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <climits>

DiskArm::DiskArm() {
    Request = nullptr;
    Cylinder = nullptr;
    RequestNumber = 0;
    CurrentCylinder = 50;   // 默认当前磁道在50
    SeekDirection = 1;       // 初始方向为1（向外）
    SeekNumber = 0;
    SeekChange = 0;
}

DiskArm::~DiskArm() {
    if (Request) free(Request);
    if (Cylinder) free(Cylinder);
}

void DiskArm::InitSpace(char* MethodName) {
    // 释放之前的请求序列
    if (Request) free(Request);
    if (Cylinder) free(Cylinder);
    
    // 设置请求数量
    RequestNumber = 10;
    Request = (int*)malloc(RequestNumber * sizeof(int));
    
    // 生成随机请求序列
    srand(time(NULL));
    for (int i = 0; i < RequestNumber; i++) {
        Request[i] = rand() % 100;  // 0-99随机磁道
    }
    
    Cylinder = (int*)malloc(RequestNumber * sizeof(int));
    memcpy(Cylinder, Request, RequestNumber * sizeof(int));
    
    // 根据算法进行排序
    if (strcmp(MethodName, "SCAN") == 0 || 
        strcmp(MethodName, "CSCAN") == 0 || 
        strcmp(MethodName, "LOOK") == 0) {
        std::sort(Cylinder, Cylinder + RequestNumber);
    }
    
    // 重置统计信息
    CurrentCylinder = 50;
    SeekDirection = 1;
    SeekNumber = 0;
    SeekChange = 0;
    
    // 输出调试信息
    std::cout << "\n使用算法: " << MethodName << std::endl;
    std::cout << "初始磁道: " << CurrentCylinder << std::endl;
    std::cout << "请求序列: ";
    for (int i = 0; i < RequestNumber; i++) {
        std::cout << Request[i] << " ";
    }
    std::cout << std::endl;
}

void DiskArm::Report() {
    std::cout << "\n总寻道距离: " << SeekNumber 
              << "\n调头次数: " << SeekChange << std::endl;
}

void DiskArm::FCFS() {
    SeekNumber = 0;
    SeekChange = 0;
    int current = CurrentCylinder;
    std::cout << "FCFS顺序: " << current;
    
    for (int i = 0; i < RequestNumber; i++) {
        std::cout << "->" << Request[i];
        SeekNumber += abs(current - Request[i]);
        current = Request[i];
    }
    std::cout << std::endl;
    Report();
}

void DiskArm::SSTF() {
    SeekNumber = 0;
    SeekChange = 0;
    int current = CurrentCylinder;
    std::cout << "SSTF顺序: " << current;
    
    // 复制请求序列用于处理
    int* temp = (int*)malloc(RequestNumber * sizeof(int));
    memcpy(temp, Request, RequestNumber * sizeof(int));
    
    // 已处理标记
    bool* processed = (bool*)malloc(RequestNumber * sizeof(bool));
    memset(processed, false, RequestNumber * sizeof(bool));
    
    // 处理所有请求
    for (int count = 0; count < RequestNumber; count++) {
        int minDist = INT_MAX;
        int minIndex = -1;
        
        // 查找最近的请求
        for (int i = 0; i < RequestNumber; i++) {
            if (!processed[i]) {
                int dist = abs(current - temp[i]);
                if (dist < minDist) {
                    minDist = dist;
                    minIndex = i;
                }
            }
        }
        
        // 处理最近的请求
        if (minIndex != -1) {
            processed[minIndex] = true;
            std::cout << "->" << temp[minIndex];
            SeekNumber += minDist;
            current = temp[minIndex];
        }
    }
    std::cout << std::endl;
    Report();
    
    free(temp);
    free(processed);
}

void DiskArm::SCAN() {
    SeekNumber = 0;
    SeekChange = 0;
    int current = CurrentCylinder;
    std::cout << "SCAN顺序: " << current;
    
    // 对请求排序（从小到大）
    std::sort(Cylinder, Cylinder + RequestNumber);
    
    // 找到起始位置（第一个>=当前磁道的位置）
    int idx = 0;
    while (idx < RequestNumber && Cylinder[idx] < current) {
        idx++;
    }
    
    // 向右扫描（向外移动）到最外侧（99号磁道）
    // 1. 先处理右侧所有请求
    for (int i = idx; i < RequestNumber; i++) {
        std::cout << "->" << Cylinder[i];
        SeekNumber += abs(current - Cylinder[i]);
        current = Cylinder[i];
    }
    
    // 2. 继续移动到最外侧（99号磁道），即使那里没有请求
    if (current < 99) {
        std::cout << "->99";
        SeekNumber += abs(current - 99);
        current = 99;
    }
    
    // 调头处理左侧请求
    SeekChange++;  // 调头次数+1
    
    // 向左扫描（向内移动）到最内侧（0号磁道）
    // 1. 处理左侧所有请求
    for (int i = idx - 1; i >= 0; i--) {
        std::cout << "->" << Cylinder[i];
        SeekNumber += abs(current - Cylinder[i]);
        current = Cylinder[i];
    }
    
    // 2. 继续移动到最内侧（0号磁道），即使那里没有请求
    if (current > 0) {
        std::cout << "->0";
        SeekNumber += abs(current - 0);
        current = 0;
    }
    
    std::cout << std::endl;
    Report();
}
void DiskArm::CSCAN() {
    SeekNumber = 0;
    SeekChange = 0;
    int current = CurrentCylinder;
    std::cout << "CSCAN顺序: " << current;
    
    // 排序请求
    std::sort(Cylinder, Cylinder + RequestNumber);
    
    // 找到起始位置
    int idx = 0;
    while (idx < RequestNumber && Cylinder[idx] < current) {
        idx++;
    }
    
    // 向右扫描到最外侧（99号磁道）
    // 1. 处理右侧所有请求
    for (int i = idx; i < RequestNumber; i++) {
        std::cout << "->" << Cylinder[i];
        SeekNumber += abs(current - Cylinder[i]);
        current = Cylinder[i];
    }
    
    // 2. 继续移动到最外侧（99号磁道）
    if (current < 99) {
        std::cout << "->99";
        SeekNumber += abs(current - 99);
        current = 99;
    }
    
    // 循环回到最内侧（0号磁道）
    SeekChange++;  // 调头计数
    
    // 1. 跳回最内侧（0号磁道）
    std::cout << "->0";
    SeekNumber += abs(current - 0);
    current = 0;
    
    // 2. 继续向右扫描处理剩余请求
    for (int i = 0; i < idx; i++) {
        std::cout << "->" << Cylinder[i];
        SeekNumber += abs(current - Cylinder[i]);
        current = Cylinder[i];
    }
    
    std::cout << std::endl;
    Report();
}
void DiskArm::LOOK() {
    SeekNumber = 0;
    SeekChange = 0;
    int current = CurrentCylinder;
    int direction = SeekDirection;
    std::cout << "LOOK顺序: " << current;
    
    // 排序请求序列
    std::sort(Cylinder, Cylinder + RequestNumber);
    
    // 找到起始位置
    int idx = 0;
    while (idx < RequestNumber && Cylinder[idx] < current) {
        idx++;
    }
    
    // 向右扫描
    if (direction == 1) {
        for (int i = idx; i < RequestNumber; i++) {
            std::cout << "->" << Cylinder[i];
            SeekNumber += abs(current - Cylinder[i]);
            current = Cylinder[i];
        }
        
        // 调头处理左侧请求
        if (idx > 0) {
            SeekChange++;
            for (int i = idx - 1; i >= 0; i--) {
                std::cout << "->" << Cylinder[i];
                SeekNumber += abs(current - Cylinder[i]);
                current = Cylinder[i];
            }
        }
    } 
    // 向左扫描
    else {
        for (int i = idx - 1; i >= 0; i--) {
            std::cout << "->" << Cylinder[i];
            SeekNumber += abs(current - Cylinder[i]);
            current = Cylinder[i];
        }
        
        // 调头处理右侧请求
        if (idx < RequestNumber) {
            SeekChange++;
            for (int i = idx; i < RequestNumber; i++) {
                std::cout << "->" << Cylinder[i];
                SeekNumber += abs(current - Cylinder[i]);
                current = Cylinder[i];
            }
        }
    }
    std::cout << std::endl;
    Report();
}

// 主函数入口
int main() {
    DiskArm arm;
    
    std::cout << "==============================" << std::endl;
    arm.InitSpace((char*)"FCFS");
    arm.FCFS();
    
    std::cout << "\n==============================" << std::endl;
    arm.InitSpace((char*)"SSTF");
    arm.SSTF();
    
    std::cout << "\n==============================" << std::endl;
    arm.InitSpace((char*)"SCAN");
    arm.SCAN();
    
    std::cout << "\n==============================" << std::endl;
    arm.InitSpace((char*)"CSCAN");
    arm.CSCAN();
    
    std::cout << "\n==============================" << std::endl;
    arm.InitSpace((char*)"LOOK");
    arm.LOOK();
    
    return 0;
}
