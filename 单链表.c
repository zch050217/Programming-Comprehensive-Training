#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* head = NULL;

// ��������
void createList(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
    } else {
        struct Node* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// ����ڵ�
void insertNode(int position, int data) {
    if (position < 0) {
        printf("�����λ�á�\n");
        return;
    }

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;

    if (position == 0) {
        newNode->next = head;
        head = newNode;
    } else {
        struct Node* temp = head;
        for (int i = 0; i < position - 1 && temp != NULL; i++) {
            temp = temp->next;
        }

        if (temp == NULL) {
            printf("�����λ�á�\n");
            return;
        }

        newNode->next = temp->next;
        temp->next = newNode;
    }
}

// ɾ���ڵ�
void deleteNode(int position) {
    if (head == NULL) {
        printf("����Ϊ�ա�\n");
        return;
    }

    if (position == 0) {
        struct Node* temp = head;
        head = head->next;
        free(temp);
    } else {
        struct Node* temp = head;
        struct Node* prev = NULL;

        for (int i = 0; i < position && temp != NULL; i++) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == NULL) {
            printf("�����λ�á�\n");
            return;
        }

        prev->next = temp->next;
        free(temp);
    }
}

// ���ҽڵ�
int searchNode(int data) {
    if (head == NULL) {
        printf("����Ϊ�ա�\n");
        return -1;
    }

    struct Node* temp = head;
    int position = 0;

    while (temp != NULL) {
        if (temp->data == data) {
            return position;
        }
        temp = temp->next;
        position++;
    }

    printf("�ڵ�δ�ҵ���\n");
    return -1;
}

// �޸Ľڵ�
void modifyNode(int position, int newData) {
    if (head == NULL) {
        printf("����Ϊ�ա�\n");
        return;
    }

    struct Node* temp = head;
    int i = 0;

    while (temp != NULL && i < position) {
        temp = temp->next;
        i++;
    }

    if (temp == NULL) {
        printf("�����λ�á�\n");
        return;
    }

    temp->data = newData;
}

// ��ӡ����
void displayList() {
    struct Node* temp = head;

    if (temp == NULL) {
        printf("����Ϊ�ա�\n");
        return;
    }

    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }

    printf("\n");
}

int main() {
    createList(1);
    createList(2);
    createList(3);
    createList(4);

    printf("��ʼ����");
    displayList();

    insertNode(2, 5);
    printf("��λ��2����ڵ�5֮��");
    displayList();

    deleteNode(1);
    printf("ɾ��λ��1�Ľڵ�֮��");
    displayList();

    int searchPosition = searchNode(3);
    if (searchPosition != -1) {
        printf("�ڵ�3��λ��%d���ҵ���\n", searchPosition);
    }

    modifyNode(0, 10);
    printf("��λ��0�Ľڵ��޸�Ϊ10֮��");
    displayList();

    return 0;
}