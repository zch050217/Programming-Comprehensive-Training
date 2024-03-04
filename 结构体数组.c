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

// ���ѧ��
void addStudent(int id, const char* name, int age) {
    if (numStudents == maxStudents) {
        printf("�Ѵﵽ���ѧ��������\n");
        return;
    }

    students[numStudents].id = id;
    strcpy(students[numStudents].name, name);
    students[numStudents].age = age;

    numStudents++;
}

// ɾ��ѧ��
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
        printf("��ɾ��ѧ����%d\n", id);
    } else {
        printf("δ�ҵ�ѧ����%d\n", id);
    }
}

// ����ѧ��
void searchStudent(int id) {
    int found = 0;

    for (int i = 0; i < numStudents; i++) {
        if (students[i].id == id) {
            found = 1;
            printf("ѧ����Ϣ��\n");
            printf("ѧ�ţ�%d\n", students[i].id);
            printf("������%s\n", students[i].name);
            printf("���䣺%d\n", students[i].age);
            break;
        }
    }

    if (!found) {
        printf("δ�ҵ�ѧ����%d\n", id);
    }
}

// �޸�ѧ����Ϣ
void modifyStudent(int id, const char* newName, int newAge) {
    int found = 0;

    for (int i = 0; i < numStudents; i++) {
        if (students[i].id == id) {
            found = 1;
            strcpy(students[i].name, newName);
            students[i].age = newAge;
            printf("���޸�ѧ����%d\n", id);
            break;
        }
    }

    if (!found) {
        printf("δ�ҵ�ѧ����%d\n", id);
    }
}

// ��ӡѧ���б�
void printStudentList() {
    printf("ѧ���б�\n");

    for (int i = 0; i < numStudents; i++) {
        printf("ѧ�ţ�%d��������%s�����䣺%d\n",
               students[i].id, students[i].name, students[i].age);
    }
}

int main() {
    // �����ڴ��ѧ������
    students = (struct Student*)malloc(maxStudents * sizeof(struct Student));

    // ���ѧ��
    addStudent(1, "����", 20);
    addStudent(2, "����", 21);
    addStudent(3, "����", 22);

    // ��ӡѧ���б�
    printStudentList();

    // ɾ��ѧ��
    deleteStudent(2);

    // ��ӡѧ���б�
    printStudentList();

    // ����ѧ��
    searchStudent(3);

    // �޸�ѧ����Ϣ
    modifyStudent(1, "����", 25);

    // ��ӡѧ���б�
    printStudentList();

    // �ͷ��ڴ�
    free(students);

    return 0;
}
