#include "ipc_smoke.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./smoker [tobacco|paper|glue]\n");
        exit(1);
    }

    // 初始化信号量
    sem_agent = set_sem(SEM_AGENT, 1);
    sem_tobacco = set_sem(SEM_TOBACCO, 0);
    sem_paper = set_sem(SEM_PAPER, 0);
    sem_glue = set_sem(SEM_GLUE, 0);

    int role = -1;
    if (strcmp(argv[1], "tobacco") == 0) role = TOBACCO;
    else if (strcmp(argv[1], "paper") == 0) role = PAPER;
    else if (strcmp(argv[1], "glue") == 0) role = GLUE;
    else {
        printf("Invalid role. Use tobacco, paper or glue.\n");
        exit(1);
    }

    while (1) {
        switch (role) {
            case TOBACCO:
                down(sem_tobacco);
                printf("Smoker with Tobacco is smoking...\n");
                break;
            case PAPER:
                down(sem_paper);
                printf("Smoker with Paper is smoking...\n");
                break;
            case GLUE:
                down(sem_glue);
                printf("Smoker with Glue is smoking...\n");
                break;
        }

        sleep(2);  // 抽烟时间
        up(sem_agent);  // 抽完烟后通知供应者
    }

    return 0;
}

