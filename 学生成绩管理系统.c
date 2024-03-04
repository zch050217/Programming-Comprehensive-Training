#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100

// ����ѧ����Ϣ�Ľṹ��
typedef struct {
    long studentID;
    char name[50];
    int mathScore;
    int programmingScore;
} Student;

// ��ʾ���˵�
void displayMainMenu() {
    printf("���˵�\n");
    printf("1. �½�����\n");
    printf("2. �������\n");
    printf("3. ɾ������\n");
    printf("4. ����\n");
    printf("5. ��ѯ\n");
    printf("6. �˳�\n");
    printf("���������ѡ����Ӧ����:");
}

// ���������ļ�
void createDataFile() {
    FILE *file = fopen("data.txt", "w");
    if (file == NULL) {
        printf("���������ļ�ʱ���ִ���\n");
        return;
    }
    fclose(file);
    printf("�����ļ�data.txt�ѳɹ�����\n");
}

// �������
void addData() {
    FILE *file = fopen("data.txt", "a");
    if (file == NULL) {
        printf("�������ļ�ʱ���ִ���\n");
        return;
    }

    Student student;
    printf("����ѧ��:");
    scanf("%ld", &student.studentID);
    printf("����ѧ������:");
    scanf("%s", student.name);
    printf("������ѧ�ɼ�:");
    scanf("%d", &student.mathScore);
    printf("���������Ƴɼ�:");
    scanf("%d", &student.programmingScore);

    fprintf(file, "%ld %s %d %d\n", student.studentID, student.name, student.mathScore, student.programmingScore);
    fclose(file);
    printf("�ѳɹ��������\n");
}

// ɾ������
void deleteData() {
    long studentID;
    printf("����Ҫɾ����ѧ��ѧ��:");
    scanf("%ld", &studentID);

    FILE *file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("�������ļ�ʱ��������\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("������ʱ�ļ�ʱ��������\n");
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
        printf("�ѳɹ�ɾ������\n");
    } else {
        remove("temp.txt");
        printf("δ�ҵ�ƥ���ѧ��ѧ��\n");
    }
}

// ������ѧ�ɼ����бȽ�
int compareByMathScore(const void *a, const void *b) {
    const Student *studentA = (const Student *)a;
    const Student *studentB = (const Student *)b;
    return studentB->mathScore - studentA->mathScore;
}

// ���ճ�����Ƴɼ����бȽ�
int compareByProgrammingScore(const void *a, const void *b) {
    const Student *studentA = (const Student *)a;
    const Student *studentB = (const Student *)b;
    return studentB->programmingScore - studentA->programmingScore;
}

// �����ֽܷ��бȽ�
int compareByTotalScore(const void *a, const void *b) {
    const Student *studentA = (const Student *)a;
    const Student *studentB = (const Student *)b;
    int totalScoreA = studentA->mathScore + studentA->programmingScore;
    int totalScoreB = studentB->mathScore + studentB->programmingScore;
    return totalScoreB - totalScoreA;
}

// ����ѡ���ķ�ʽ��������
void sortData() {
    FILE *file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("�������ļ�ʱ��������\n");
        return;
    }

    Student students[MAX_STUDENTS];
    int count = 0;
    while (fscanf(file, "%ld %s %d %d", &students[count].studentID, students[count].name, &students[count].mathScore, &students[count].programmingScore) != EOF) {
        count++;
    }

    fclose(file);

    int option;
    printf("����ʽ\n");
    printf("1. ��ѧ�ɼ�����\n");
    printf("2. ������Ƴɼ�����\n");
    printf("3. �ܷ�����\n");
    printf("4. �������˵�\n");
    printf("����������ѡ��:");
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

    printf("��������������:\n");
    for (int i = 0; i < count; i++) {
        printf("ѧ��: %ld, ����: %s, ��ѧ�ɼ�: %d, ������Ƴɼ�: %d\n", students[i].studentID, students[i].name, students[i].mathScore, students[i].programmingScore);
    }
}

// ����ѡ����ʽ���в�ѯ
void queryData() {
    FILE *file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("�������ļ�ʱ���ִ���\n");
        return;
    }

    int option;
    printf("��ѯ��ʽ\n");
    printf("1. ѧ�Ų�ѯ\n");
    printf("2. ������ѯ\n");
    printf("3. ��ѧ�ɼ���ѯ\n");
    printf("4. ������Ƴɼ���ѯ\n");
    printf("5. �ֲܷ�ѯ\n");
    printf("6. �������˵�\n");
    printf("�������ѯѡ��:");
    scanf("%d", &option);

    switch (option) {
        case 1: {
            long studentID;
            printf("������Ҫ��ѯ��ѧ��: ");
            scanf("%ld", &studentID);

            Student student;
            int found = 0;
            while (fscanf(file, "%ld %s %d %d", &student.studentID, student.name, &student.mathScore, &student.programmingScore) != EOF) {
                if (student.studentID == studentID) {
                    printf("ѧ��: %ld, ����: %s, ��ѧ�ɼ�: %d, ������Ƴɼ�: %d\n", student.studentID, student.name, student.mathScore, student.programmingScore);
                    found = 1;
                    break;
                }
            }

            if (!found) {
                printf("ѧ��δ�ҵ�\n");
            }
            break;
        }
        case 2: {
            char name[50];
            printf("������Ҫ��ѯ������: ");
            scanf("%s", name);

            Student student;
            int found = 0;
            while (fscanf(file, "%ld %s %d %d", &student.studentID, student.name, &student.mathScore, &student.programmingScore) != EOF) {
                if (strcmp(student.name, name) == 0) {
                    printf("ѧ��: %ld, ����: %s, ��ѧ�ɼ�: %d, ������Ƴɼ�: %d\n", student.studentID, student.name, student.mathScore, student.programmingScore);
                    found = 1;
                    break;
                }
            }

            if (!found) {
                printf("����δ�ҵ�\n");
            }
            break;
        }
        case 3: {
            int mathScore;
            printf("������Ҫ��ѯ����ѧ�ɼ�: ");
            scanf("%d", &mathScore);

            Student student;
            int count = 0;
            while (fscanf(file, "%ld %s %d %d", &student.studentID, student.name, &student.mathScore, &student.programmingScore) != EOF) {
                if (student.mathScore >= mathScore) {
                    printf("ѧ��: %ld, ����: %s, ��ѧ�ɼ�: %d, ������Ƴɼ�: %d\n", student.studentID, student.name, student.mathScore, student.programmingScore);
                    count++;
                }
            }

            printf("��ѧ�ɼ� >= %d ������: %d\n", mathScore, count);
            break;
        }
        case 4: {
            int programmingScore;
            printf("������Ҫ��ѯ�ĳ�����Ƴɼ�: ");
            scanf("%d", &programmingScore);

            Student student;
            int count = 0;
            while (fscanf(file, "%ld %s %d %d", &student.studentID, student.name, &student.mathScore, &student.programmingScore) != EOF) {
                if (student.programmingScore >= programmingScore) {
                    printf("ѧ��: %ld, ����: %s, ��ѧ�ɼ�: %d, ������Ƴɼ�: %d\n", student.studentID, student.name, student.mathScore, student.programmingScore);
                    count++;
                }
            }

            printf("������Ƴɼ� >= %d ������: %d\n", programmingScore, count);
            break;
        }
        case 5: {
            int totalScore;
            printf("������Ҫ��ѯ���ܳɼ�: ");
            scanf("%d", &totalScore);

            Student student;
            int count = 0;
            while (fscanf(file, "%ld %s %d %d", &student.studentID, student.name, &student.mathScore, &student.programmingScore) != EOF) {
                int total = student.mathScore + student.programmingScore;
                if (total >= totalScore) {
                    printf("ѧ��: %ld, ����: %s, ��ѧ�ɼ�: %d, ������Ƴɼ�: %d\n", student.studentID, student.name, student.mathScore, student.programmingScore);
                    count++;
                }
            }

            printf("�ܳɼ� >= %d ������: %d\n", totalScore, count);
            break;
        }
        default:
            return;
    }

    fclose(file);
}

// ������
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
                printf("�������˳�\n");
                break;

            default:
                printf("�����ڵ�ѡ�����������\n");
                break;
        }
    } while (option != 6);

    return 0;
}
