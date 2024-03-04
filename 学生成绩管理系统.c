#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100

// 储存学生信息的结构体
typedef struct {
    long studentID;
    char name[50];
    int mathScore;
    int programmingScore;
} Student;

// 显示主菜单
void displayMainMenu() {
    printf("主菜单\n");
    printf("1. 新建数据\n");
    printf("2. 添加数据\n");
    printf("3. 删除数据\n");
    printf("4. 排序\n");
    printf("5. 查询\n");
    printf("6. 退出\n");
    printf("请输入序号选择相应操作:");
}

// 创建数据文件
void createDataFile() {
    FILE *file = fopen("data.txt", "w");
    if (file == NULL) {
        printf("创建数据文件时出现错误\n");
        return;
    }
    fclose(file);
    printf("数据文件data.txt已成功创建\n");
}

// 添加数据
void addData() {
    FILE *file = fopen("data.txt", "a");
    if (file == NULL) {
        printf("打开数据文件时出现错误\n");
        return;
    }

    Student student;
    printf("输入学号:");
    scanf("%ld", &student.studentID);
    printf("输入学生姓名:");
    scanf("%s", student.name);
    printf("输入数学成绩:");
    scanf("%d", &student.mathScore);
    printf("输入程序设计成绩:");
    scanf("%d", &student.programmingScore);

    fprintf(file, "%ld %s %d %d\n", student.studentID, student.name, student.mathScore, student.programmingScore);
    fclose(file);
    printf("已成功添加数据\n");
}

// 删除数据
void deleteData() {
    long studentID;
    printf("输入要删除的学生学号:");
    scanf("%ld", &studentID);

    FILE *file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("打开数据文件时发生错误\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("创建临时文件时发生错误\n");
        fclose(file);
        return;
    }

    Student student;
    int deleted = 0;
    while (fscanf(file, "%ld %s %d %d", &student.studentID, student.name, &student.mathScore, &student.programmingScore) != EOF) {
        if (student.studentID != studentID) {
            fprintf(tempFile, "%ld %s %d %d\n", student.studentID, student.name, student.mathScore, student.programmingScore);
        } else {
            deleted = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    if (deleted) {
        remove("data.txt");
        rename("temp.txt", "data.txt");
        printf("已成功删除数据\n");
    } else {
        remove("temp.txt");
        printf("未找到匹配的学生学号\n");
    }
}

// 按照数学成绩进行比较
int compareByMathScore(const void *a, const void *b) {
    const Student *studentA = (const Student *)a;
    const Student *studentB = (const Student *)b;
    return studentB->mathScore - studentA->mathScore;
}

// 按照程序设计成绩进行比较
int compareByProgrammingScore(const void *a, const void *b) {
    const Student *studentA = (const Student *)a;
    const Student *studentB = (const Student *)b;
    return studentB->programmingScore - studentA->programmingScore;
}

// 按照总分进行比较
int compareByTotalScore(const void *a, const void *b) {
    const Student *studentA = (const Student *)a;
    const Student *studentB = (const Student *)b;
    int totalScoreA = studentA->mathScore + studentA->programmingScore;
    int totalScoreB = studentB->mathScore + studentB->programmingScore;
    return totalScoreB - totalScoreA;
}

// 按照选定的方式进行排序
void sortData() {
    FILE *file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("打开数据文件时发生错误\n");
        return;
    }

    Student students[MAX_STUDENTS];
    int count = 0;
    while (fscanf(file, "%ld %s %d %d", &students[count].studentID, students[count].name, &students[count].mathScore, &students[count].programmingScore) != EOF) {
        count++;
    }

    fclose(file);

    int option;
    printf("排序方式\n");
    printf("1. 数学成绩排序\n");
    printf("2. 程序设计成绩排序\n");
    printf("3. 总分排序\n");
    printf("4. 返回主菜单\n");
    printf("请输入排序选项:");
    scanf("%d", &option);

    switch (option) {
        case 1:
            qsort(students, count, sizeof(Student), compareByMathScore);
            break;
        case 2:
            qsort(students, count, sizeof(Student), compareByProgrammingScore);
            break;
        case 3:
            qsort(students, count, sizeof(Student), compareByTotalScore);
            break;
        default:
            return;
    }

    printf("已完成排序的数据:\n");
    for (int i = 0; i < count; i++) {
        printf("学号: %ld, 姓名: %s, 数学成绩: %d, 程序设计成绩: %d\n", students[i].studentID, students[i].name, students[i].mathScore, students[i].programmingScore);
    }
}

// 根据选定方式进行查询
void queryData() {
    FILE *file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("打开数据文件时出现错误\n");
        return;
    }

    int option;
    printf("查询方式\n");
    printf("1. 学号查询\n");
    printf("2. 姓名查询\n");
    printf("3. 数学成绩查询\n");
    printf("4. 程序设计成绩查询\n");
    printf("5. 总分查询\n");
    printf("6. 返回主菜单\n");
    printf("请输入查询选项:");
    scanf("%d", &option);

    switch (option) {
        case 1: {
            long studentID;
            printf("请输入要查询的学号: ");
            scanf("%ld", &studentID);

            Student student;
            int found = 0;
            while (fscanf(file, "%ld %s %d %d", &student.studentID, student.name, &student.mathScore, &student.programmingScore) != EOF) {
                if (student.studentID == studentID) {
                    printf("学号: %ld, 姓名: %s, 数学成绩: %d, 程序设计成绩: %d\n", student.studentID, student.name, student.mathScore, student.programmingScore);
                    found = 1;
                    break;
                }
            }

            if (!found) {
                printf("学号未找到\n");
            }
            break;
        }
        case 2: {
            char name[50];
            printf("请输入要查询的姓名: ");
            scanf("%s", name);

            Student student;
            int found = 0;
            while (fscanf(file, "%ld %s %d %d", &student.studentID, student.name, &student.mathScore, &student.programmingScore) != EOF) {
                if (strcmp(student.name, name) == 0) {
                    printf("学号: %ld, 姓名: %s, 数学成绩: %d, 程序设计成绩: %d\n", student.studentID, student.name, student.mathScore, student.programmingScore);
                    found = 1;
                    break;
                }
            }

            if (!found) {
                printf("姓名未找到\n");
            }
            break;
        }
        case 3: {
            int mathScore;
            printf("请输入要查询的数学成绩: ");
            scanf("%d", &mathScore);

            Student student;
            int count = 0;
            while (fscanf(file, "%ld %s %d %d", &student.studentID, student.name, &student.mathScore, &student.programmingScore) != EOF) {
                if (student.mathScore >= mathScore) {
                    printf("学号: %ld, 姓名: %s, 数学成绩: %d, 程序设计成绩: %d\n", student.studentID, student.name, student.mathScore, student.programmingScore);
                    count++;
                }
            }

            printf("数学成绩 >= %d 的人数: %d\n", mathScore, count);
            break;
        }
        case 4: {
            int programmingScore;
            printf("请输入要查询的程序设计成绩: ");
            scanf("%d", &programmingScore);

            Student student;
            int count = 0;
            while (fscanf(file, "%ld %s %d %d", &student.studentID, student.name, &student.mathScore, &student.programmingScore) != EOF) {
                if (student.programmingScore >= programmingScore) {
                    printf("学号: %ld, 姓名: %s, 数学成绩: %d, 程序设计成绩: %d\n", student.studentID, student.name, student.mathScore, student.programmingScore);
                    count++;
                }
            }

            printf("程序设计成绩 >= %d 的人数: %d\n", programmingScore, count);
            break;
        }
        case 5: {
            int totalScore;
            printf("请输入要查询的总成绩: ");
            scanf("%d", &totalScore);

            Student student;
            int count = 0;
            while (fscanf(file, "%ld %s %d %d", &student.studentID, student.name, &student.mathScore, &student.programmingScore) != EOF) {
                int total = student.mathScore + student.programmingScore;
                if (total >= totalScore) {
                    printf("学号: %ld, 姓名: %s, 数学成绩: %d, 程序设计成绩: %d\n", student.studentID, student.name, student.mathScore, student.programmingScore);
                    count++;
                }
            }

            printf("总成绩 >= %d 的人数: %d\n", totalScore, count);
            break;
        }
        default:
            return;
    }

    fclose(file);
}

// 主函数
int main() {
    int option;

    do {
        displayMainMenu();
        scanf("%d", &option);

        switch (option) {
            case 1:
                createDataFile();
                break;
            case 2:
                addData();
                break;
            case 3:
                deleteData();
                break;
            case 4:
                sortData();
                break;
            case 5:
                queryData();
                break;
            case 6:
                printf("程序已退出\n");
                break;

            default:
                printf("不存在的选项，请重新输入\n");
                break;
        }
    } while (option != 6);

    return 0;
}
