#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// 用户输入双色球号码
void inputInterface(int *redBalls, int *blueBall) {
    printf("请输入六个红色球号码：");
    for (int i = 0; i < 6; i++) {
        scanf("%d", &redBalls[i]);
        // 确认输入范围合法性
        if (redBalls[i] < 1 || redBalls[i] > 33) {
            printf("输入出错,红色球范围必须在1到33\n");
            exit(1);
        }
        //查重
        for (int j = 0; j < i; j++) {
            if (redBalls[j] == redBalls[i]) {
                printf("输入出错,红色球号码不能重复\n");
                exit(1);
            }
        }
    }

    printf("请输入一个蓝色球号码：");
    scanf("%d", blueBall);
    // 确认输入范围合法性
    if (*blueBall < 1 || *blueBall > 16) {
        printf("输入出错,蓝色球范围必须在1到16\n");
        exit(1);
    }
}

// 随机生成中奖号码
void lotterySimulation(int *winningRedBalls, int *winningBlueBall) {
    srand(time(NULL));  //修改种子
    // 随机生成红色球号码
    bool chosen[34] = {false}; // 初始化布尔数组，O(1)
    for (int i = 0; i < 6; i++) {
        int ball;
        do {
            ball = rand() % 33 + 1;
        } while (chosen[ball]); // 如果这个号码已经被选中，就重新生成
        winningRedBalls[i] = ball;
        chosen[ball] = true; // 标记这个号码已经被选中
    }

    // 随机生成蓝色球号码
    *winningBlueBall = rand() % 16 + 1;
}

// 检查中奖情况
int checkWinning(int *redBalls, int blueBall, int *winningRedBalls, int winningBlueBall) {
    int RedFlag = 0, BlueFlag = 1;
    // 比较红色球号码
    int redBallsCount[34] = {0}; // 桶排序数组，用于统计红色球的个数

    // 统计用户选择的红色球个数
    for (int i = 0; i < 6; i++) {
        redBallsCount[redBalls[i]]++;
    }
    //统计中奖红色球
    for (int i = 0; i < 6; i++) {
        redBallsCount[winningRedBalls[i]]++;
    }
    // 比较用户选择的红色球和中奖红色球
    for (int i = 0; i < 6; i++) {
        if (redBallsCount[winningRedBalls[i]] == 2) {
            RedFlag++;
        } 
    }

    // 比较蓝色球号码
    if (blueBall != winningBlueBall) {
        BlueFlag = 0;
    }

    if (RedFlag == 6 && BlueFlag == 1) {
        return 1;
    }
    else if (RedFlag == 6 && BlueFlag == 0) {
        return 2;
    }
    else if (RedFlag == 5 && BlueFlag == 1) {
        return 3;
    }
    else if (RedFlag == 5 && BlueFlag == 0 || RedFlag == 4 && BlueFlag == 1) {
        return 4;
    }
    else if (RedFlag == 4 && BlueFlag == 0 || RedFlag == 3 && BlueFlag == 1) {
        return 5;
    }
    else if (RedFlag == 2 && BlueFlag == 1 || RedFlag == 1 && BlueFlag == 1 || RedFlag == 0 && BlueFlag == 1) {
        return 6;
    }
    else {
        return 0;
    }
}
// 显示中奖信息
void displayWinningInfo(int *redBalls, int blueBall, int *winningRedBalls, int winningBlueBall, int result) {
    printf("你选择的红色球号码：");
    for (int i = 0; i < 6; i++) {
        printf("%d ", redBalls[i]);
    }
    printf("\n");

    printf("你选择的蓝色球号码： %d\n", blueBall);

    printf("红色球中奖号码: ");
    for (int i = 0; i < 6; i++) {
        printf("%d ", winningRedBalls[i]);
    }
    printf("\n");

    printf("蓝色球中奖号码： %d\n", winningBlueBall);
    
    if (result != 0) {
        printf("中了%d等奖\n", result);
    } else {
        printf("没有中奖\n");
    }
}

int main() {
    int redBalls[6];
    int blueBall;
    int winningRedBalls[6];
    int winningBlueBall;
    int result;

    inputInterface(redBalls, &blueBall);
    lotterySimulation(winningRedBalls, &winningBlueBall);
    result = checkWinning(redBalls, blueBall, winningRedBalls, winningBlueBall);
    displayWinningInfo(redBalls, blueBall, winningRedBalls, winningBlueBall, result);

    return 0;
}