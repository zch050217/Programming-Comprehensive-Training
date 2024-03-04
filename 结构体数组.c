#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int id;
    char name[20];
    int age;
};

struct Student* students;
int numStudents = 0;
int maxStudents = 10;

// 添加学生
void addStudent(int id, const char* name, int age) {
    if (numStudents == maxStudents) {
        printf("已达到最大学生数量。\n");
        return;
    }

    students[numStudents].id = id;
    strcpy(students[numStudents].name, name);
    students[numStudents].age = age;

    numStudents++;
}

// 删除学生
void deleteStudent(int id) {
    int found = 0;
    int deleteIndex;

    for (int i = 0; i < numStudents; i++) {
        if (students[i].id == id) {
            found = 1;
            deleteIndex = i;
            break;
        }
    }

    if (found) {
        for (int i = deleteIndex; i < numStudents - 1; i++) {
            students[i] = students[i + 1];
        }

        numStudents--;
        printf("已删除学生：%d\n", id);
    } else {
        printf("未找到学生：%d\n", id);
    }
}

// 查找学生
void searchStudent(int id) {
    int found = 0;

    for (int i = 0; i < numStudents; i++) {
        if (students[i].id == id) {
            found = 1;
            printf("学生信息：\n");
            printf("学号：%d\n", students[i].id);
            printf("姓名：%s\n", students[i].name);
            printf("年龄：%d\n", students[i].age);
            break;
        }
    }

    if (!found) {
        printf("未找到学生：%d\n", id);
    }
}

// 修改学生信息
void modifyStudent(int id, const char* newName, int newAge) {
    int found = 0;

    for (int i = 0; i < numStudents; i++) {
        if (students[i].id == id) {
            found = 1;
            strcpy(students[i].name, newName);
            students[i].age = newAge;
            printf("已修改学生：%d\n", id);
            break;
        }
    }

    if (!found) {
        printf("未找到学生：%d\n", id);
    }
}

// 打印学生列表
void printStudentList() {
    printf("学生列表：\n");

    for (int i = 0; i < numStudents; i++) {
        printf("学号：%d，姓名：%s，年龄：%d\n",
               students[i].id, students[i].name, students[i].age);
    }
}

int main() {
    // 分配内存给学生数组
    students = (struct Student*)malloc(maxStudents * sizeof(struct Student));

    // 添加学生
    addStudent(1, "张三", 20);
    addStudent(2, "李四", 21);
    addStudent(3, "王五", 22);

    // 打印学生列表
    printStudentList();

    // 删除学生
    deleteStudent(2);

    // 打印学生列表
    printStudentList();

    // 查找学生
    searchStudent(3);

    // 修改学生信息
    modifyStudent(1, "赵六", 25);

    // 打印学生列表
    printStudentList();

    // 释放内存
    free(students);

    return 0;
}
