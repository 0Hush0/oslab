#include "ipc_smoke.h"
#include <time.h>

int main() {
    srand(time(NULL));

    // 初始化信号量，agent 初始为 1，三个 smoker 信号量初始为 0
    sem_agent = set_sem(SEM_AGENT, 1);
    sem_tobacco = set_sem(SEM_TOBACCO, 0);
    sem_paper = set_sem(SEM_PAPER, 0);
    sem_glue = set_sem(SEM_GLUE, 0);

    while (1) {
        down(sem_agent);  // 等待抽烟者通知

        int choice = rand() % 3;
        switch (choice) {
            case 0:
                // 放纸 + 胶水，唤醒有烟草的人
                printf("Agent puts: Paper + Glue -> wake up Smoker with Tobacco\n");
                up(sem_tobacco);
                break;
            case 1:
                // 放烟草 + 胶水，唤醒有纸的人
                printf("Agent puts: Tobacco + Glue -> wake up Smoker with Paper\n");
                up(sem_paper);
                break;
            case 2:
                // 放烟草 + 纸，唤醒有胶水的人
                printf("Agent puts: Tobacco + Paper -> wake up Smoker with Glue\n");
                up(sem_glue);
                break;
        }

        sleep(1);  // 模拟供料时间
    }

    return 0;
}


