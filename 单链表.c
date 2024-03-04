#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* head = NULL;

// 创建链表
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

// 插入节点
void insertNode(int position, int data) {
    if (position < 0) {
        printf("错误的位置。\n");
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
            printf("错误的位置。\n");
            return;
        }

        newNode->next = temp->next;
        temp->next = newNode;
    }
}

// 删除节点
void deleteNode(int position) {
    if (head == NULL) {
        printf("链表为空。\n");
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
            printf("错误的位置。\n");
            return;
        }

        prev->next = temp->next;
        free(temp);
    }
}

// 查找节点
int searchNode(int data) {
    if (head == NULL) {
        printf("链表为空。\n");
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

    printf("节点未找到。\n");
    return -1;
}

// 修改节点
void modifyNode(int position, int newData) {
    if (head == NULL) {
        printf("链表为空。\n");
        return;
    }

    struct Node* temp = head;
    int i = 0;

    while (temp != NULL && i < position) {
        temp = temp->next;
        i++;
    }

    if (temp == NULL) {
        printf("错误的位置。\n");
        return;
    }

    temp->data = newData;
}

// 打印链表
void displayList() {
    struct Node* temp = head;

    if (temp == NULL) {
        printf("链表为空。\n");
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

    printf("初始链表：");
    displayList();

    insertNode(2, 5);
    printf("在位置2插入节点5之后：");
    displayList();

    deleteNode(1);
    printf("删除位置1的节点之后：");
    displayList();

    int searchPosition = searchNode(3);
    if (searchPosition != -1) {
        printf("节点3在位置%d上找到。\n", searchPosition);
    }

    modifyNode(0, 10);
    printf("将位置0的节点修改为10之后：");
    displayList();

    return 0;
}