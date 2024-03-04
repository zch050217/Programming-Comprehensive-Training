#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// �û�����˫ɫ�����
void inputInterface(int *redBalls, int *blueBall) {
    printf("������������ɫ����룺");
    for (int i = 0; i < 6; i++) {
        scanf("%d", &redBalls[i]);
        // ȷ�����뷶Χ�Ϸ���
        if (redBalls[i] < 1 || redBalls[i] > 33) {
            printf("�������,��ɫ��Χ������1��33\n");
            exit(1);
        }
        //����
        for (int j = 0; j < i; j++) {
            if (redBalls[j] == redBalls[i]) {
                printf("�������,��ɫ����벻���ظ�\n");
                exit(1);
            }
        }
    }

    printf("������һ����ɫ����룺");
    scanf("%d", blueBall);
    // ȷ�����뷶Χ�Ϸ���
    if (*blueBall < 1 || *blueBall > 16) {
        printf("�������,��ɫ��Χ������1��16\n");
        exit(1);
    }
}

// ��������н�����
void lotterySimulation(int *winningRedBalls, int *winningBlueBall) {
    srand(time(NULL));  //�޸�����
    // ������ɺ�ɫ�����
    bool chosen[34] = {false}; // ��ʼ���������飬O(1)
    for (int i = 0; i < 6; i++) {
        int ball;
        do {
            ball = rand() % 33 + 1;
        } while (chosen[ball]); // �����������Ѿ���ѡ�У�����������
        winningRedBalls[i] = ball;
        chosen[ball] = true; // �����������Ѿ���ѡ��
    }

    // ���������ɫ�����
    *winningBlueBall = rand() % 16 + 1;
}

// ����н����
int checkWinning(int *redBalls, int blueBall, int *winningRedBalls, int winningBlueBall) {
    int RedFlag = 0, BlueFlag = 1;
    // �ȽϺ�ɫ�����
    int redBallsCount[34] = {0}; // Ͱ�������飬����ͳ�ƺ�ɫ��ĸ���

    // ͳ���û�ѡ��ĺ�ɫ�����
    for (int i = 0; i < 6; i++) {
        redBallsCount[redBalls[i]]++;
    }
    //ͳ���н���ɫ��
    for (int i = 0; i < 6; i++) {
        redBallsCount[winningRedBalls[i]]++;
    }
    // �Ƚ��û�ѡ��ĺ�ɫ����н���ɫ��
    for (int i = 0; i < 6; i++) {
        if (redBallsCount[winningRedBalls[i]] == 2) {
            RedFlag++;
        } 
    }

    // �Ƚ���ɫ�����
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
// ��ʾ�н���Ϣ
void displayWinningInfo(int *redBalls, int blueBall, int *winningRedBalls, int winningBlueBall, int result) {
    printf("��ѡ��ĺ�ɫ����룺");
    for (int i = 0; i < 6; i++) {
        printf("%d ", redBalls[i]);
    }
    printf("\n");

    printf("��ѡ�����ɫ����룺 %d\n", blueBall);

    printf("��ɫ���н�����: ");
    for (int i = 0; i < 6; i++) {
        printf("%d ", winningRedBalls[i]);
    }
    printf("\n");

    printf("��ɫ���н����룺 %d\n", winningBlueBall);
    
    if (result != 0) {
        printf("����%d�Ƚ�\n", result);
    } else {
        printf("û���н�\n");
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