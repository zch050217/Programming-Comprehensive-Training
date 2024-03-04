//��Դ�ڿ�����WE-ubytt
#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<string.h>
typedef struct Node
{
	int ID;// ����
	char Name[50];// ����
	char Sex[10];// �Ա�
	int Age;// ����
	char Education[20];// ѧ��
	char Post[20];// ְ��
	int Wage;// ����
	char Room[50];// סַ
	char Telephone[20];// �绰

	struct Node* next;// ָ����
}node;

node list;// ����

// ��ȡ�ļ�
int Read_FILE(node* L);

// �����ļ�
int  Save_FILE(node* L);

// ���˵�����
void welcome();

// ����ְ����Ϣ
void Add(node* L, node e);// ����
void Add_Printf();// ����

// ɾ��ְ����Ϣ
void Delete_Printf(node* L);// ����
void Delete(node* s);// ����

// �޸�ְ����Ϣ
void Fix(node* L);

// ��ѯְ����Ϣ
void Search_Printf(node* L);// ����
node* Search_id(int id, node* L);// �����Ž��в���
node* Search_name(char name[], node* L);// ���������в���

// ���ְ����Ϣ
void Print(node* L);// ����
void Print_Printf();// ����

// ����ְ����Ϣ
void Sort(node* L);
bool cmp_big_Wage(node e1, node e2);// ���ʴӴ�С
bool cmp_small_Wage(node e1, node e2);// ���ʴ�С����

// �˳�����ϵͳ
void goodbye();

int main()
{
	int choice = 0;
	Read_FILE(&list);
	while (true)
	{
		welcome();
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:// ����ְ����Ϣ
			Add_Printf();
			break;
		case 2:// ɾ��ְ����Ϣ
			Delete_Printf(&list);
			break;
		case 3:// �޸�ְ����Ϣ
			Fix(&list);
			break;
		case 4:// ��ѯְ����Ϣ
			Search_Printf(&list);
			break;
		case 5:// ���ְ����Ϣ
			Print(&list);
			break;
		case 6:// ����ְ����Ϣ
			Sort(&list);
			break;
		case 0:// �˳�ְ��ϵͳ
			goodbye();
			break;
		}
		printf("�Ƿ���Ҫ������������Yes��1 / No��0)��");
		scanf("%d", &choice);
		if (choice == 0)
		{
			break;
		}
	}
	return 0;
}

void welcome()
{
	system("cls");
	printf("****************************************************************\n");
	printf("***********             ְ����Ϣ����ϵͳ             ***********\n");
	printf("***********          1 ---- ����ְ����Ϣ             ***********\n");
	printf("***********          2 ---- ɾ��ְ����Ϣ             ***********\n");
	printf("***********          3 ---- �޸�ְ����Ϣ             ***********\n");
	printf("***********          4 ---- ��ѯְ����Ϣ             ***********\n");
	printf("***********          5 ---- ���ְ����Ϣ             ***********\n");
	printf("***********          6 ---- ����ְ����Ϣ             ***********\n");
	printf("***********          0 ---- �˳�����ϵͳ             ***********\n");
	printf("****************************************************************\n");

	printf("��ѡ����Ҫʵ�ֵĹ��ܣ����֣���");
}

// ��ȡ�ļ�
int Read_FILE(node* L)
{
	FILE* pfRead = fopen("worker_information.txt", "r");
	node st;
	node* s;
	node* t = L;

	if (pfRead == NULL)
	{
		return 0;
	}

	while (fscanf(pfRead, "%d %s %s %d %s %s %d %s %s", &st.ID, st.Name, st.Sex, &st.Age, st.Education, st.Post, &st.Wage, st.Room, st.Telephone) != EOF)
	{
		s = (node*)malloc(sizeof(node));

		*s = st;

		// β�巨
		t->next = s;
		t = s;
		t->next = NULL;
	}

	return 1;
}

// �����ļ�
int  Save_FILE(node* L)
{
	FILE* pfWrite = fopen("worker_information.txt", "w");
	if (pfWrite == NULL)
	{
		return 0;
	}

	node* p = L->next;

	while (p != NULL)
	{
		fprintf(pfWrite, "%d %s %s %d %s %s %d %s %s\n", p->ID, p->Name, p->Sex, p->Age, p->Education, p->Post, p->Wage, p->Room, p->Telephone);
		p = p->next;
	}

	return 1;
}

// ����ְ����Ϣ
void Add_Printf()
{
	system("cls");
	node st;
	printf("����������ְ���������Ϣ��\n");
	printf("���ţ�");
	scanf("%d", &st.ID);
	printf("������");
	scanf("%s", st.Name);
	printf("�Ա�");
	scanf("%s", st.Sex);
	printf("���䣺");
	scanf("%d", &st.Age);
	printf("ѧ����");
	scanf("%s", st.Education);
	printf("ְ��");
	scanf("%s", st.Post);
	printf("���ʣ�");
	scanf("%d", &st.Wage);
	printf("סַ��");
	scanf("%s", st.Room);
	printf("�绰��");
	scanf("%s", &st.Telephone);

	Add(&list, st);
}

void Add(node* L, node e)
{
	// ͷ�巨
	node* p = L;
	node* s = (node*)malloc(sizeof(node));
	*s = e;

	s->next = p->next;
	p->next = s;

	Save_FILE(L);
}

// ɾ��ְ����Ϣ
void Delete_Printf(node* L)
{
	system("cls");
	int id;

	node* p;

	printf("������Ҫɾ����ְ���Ĺ��ţ�");
	scanf("%d", &id);
	node* st = Search_id(id, L);
	p = st;

	if (st == NULL)
	{
		printf("���޴��ˣ�\n");
		return;
	}

	st = st->next;
	printf("________________________________________________________________________________________________\n");
	printf("|ѧ��\t|����\t|�Ա�\t|����\t|ѧ��\t|ְλ\t|����\t|סַ\t\t\t|�绰\t\t|\n");
	printf("________________________________________________________________________________________________\n");
	printf("|%d\t|%s\t|%s\t|%d\t|%s\t|%s\t|%d\t|%s\t\t|%s\t|\n", st->ID, st->Name, st->Sex, st->Age, st->Education, st->Post, st->Wage, st->Room, st->Telephone);
	printf("________________________________________________________________________________________________\n");

	Delete(p);
	// ������Ϣ
	Save_FILE(L);
}

void Delete(node* s)
{
	node* t = s->next;

	s->next = t->next;
	t->next = NULL;

	free(t);
}

// �޸�ְ����Ϣ
void Fix(node* L)
{
	system("cls");
	int id;
	printf("������Ҫ�޸ĵ�ְ���Ĺ��ţ�");
	scanf("%d", &id);
	node* st = Search_id(id, L);

	if (st == NULL)
	{
		printf("���޴��ˣ�\n");
		return;
	}

	st = st->next;

	int choice = 0;
	while (1)
	{
		system("cls");

		// ���һ����Ҫ�޸ĵ�ְ����Ϣ
		printf("________________________________________________________________________________________________\n");
		printf("|ѧ��\t|����\t|�Ա�\t|����\t|ѧ��\t|ְλ\t|����\t|סַ\t\t\t|�绰\t\t|\n");
		printf("________________________________________________________________________________________________\n");
		printf("|%d\t|%s\t|%s\t|%d\t|%s\t|%s\t|%d\t|%s\t\t|%s\t|\n", st->ID, st->Name, st->Sex, st->Age, st->Education, st->Post, st->Wage, st->Room, st->Telephone);
		printf("________________________________________________________________________________________________\n");

		printf("�޸����� ---- 1\n");
		printf("�޸��Ա� ---- 2\n");
		printf("�޸İ༶ ---- 3\n");
		printf("�޸�ѧ�� ---- 4\n");
		printf("�޸�ְλ ---- 5\n");
		printf("�޸Ĺ��� ---- 6\n");
		printf("�޸�סַ ---- 7\n");
		printf("�޸ĵ绰 ---- 8\n");

		printf("������Ҫ�޸ĵ���Ϣ��");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			printf("������������");
			scanf("%s", st->Name);
			break;
		case 2:
			printf("�������Ա�");
			scanf("%s", st->Sex);
			break;
		case 3:
			printf("���������䣺");
			scanf("%d", st->Age);
			break;
		case 4:
			printf("������ѧ����");
			scanf("%s", st->Education);
			break;
		case 5:
			printf("������ְ��");
			scanf("%s", st->Post);
			break;
		case 6:
			printf("�����빤�ʣ�");
			scanf("%d", st->Wage);
			break;
		case 7:
			printf("������סַ��");
			scanf("%s", st->Room);
			break;
		case 8:
			printf("������绰��");
			scanf("%s", st->Telephone);
			break;
		}
		printf("�Ƿ�����޸ĸ�ѧ����Ϣ����Yes��1 / No��0����");
		scanf("%d", &choice);
		if (choice == 0)
		{
			break;
		}
	}

	// �޸���ɺ��ѧ������Ϣ
	printf("________________________________________________________________________________________________\n");
	printf("|ѧ��\t|����\t|�Ա�\t|����\t|ѧ��\t|ְλ\t|����\t|סַ\t\t\t|�绰\t\t|\n");
	printf("________________________________________________________________________________________________\n");
	printf("|%d\t|%s\t|%s\t|%d\t|%s\t|%s\t|%d\t|%s\t\t|%s\t|\n", st->ID, st->Name, st->Sex, st->Age, st->Education, st->Post, st->Wage, st->Room, st->Telephone);
	printf("________________________________________________________________________________________________\n");

	// ������Ϣ
	Save_FILE(L);
}

// ��ѯְ����Ϣ
void Search_Printf(node* L)
{
	system("cls");
	int choice = 0;
	printf("���չ��Ų�ѯ ---- 1\n");
	printf("����������ѯ ---- 2\n");
	printf("�������ѯ��ʽ��");
	scanf("%d", &choice);

	int id;
	char name[50];
	node* st;
	if (choice == 1)
	{
		printf("������Ҫ��ѯ�Ĺ��ţ�");
		scanf("%d", &id);
		st = Search_id(id, L);

		if (st == NULL)
		{
			printf("���޴��ˣ�\n");
		}
		else
		{
			st = st->next;
			printf("________________________________________________________________________________________________\n");
			printf("|ѧ��\t|����\t|�Ա�\t|����\t|ѧ��\t|ְλ\t|����\t|סַ\t\t\t|�绰\t\t|\n");
			printf("________________________________________________________________________________________________\n");
			printf("|%d\t|%s\t|%s\t|%d\t|%s\t|%s\t|%d\t|%s\t\t|%s\t|\n", st->ID, st->Name, st->Sex, st->Age, st->Education, st->Post, st->Wage, st->Room, st->Telephone);
			printf("________________________________________________________________________________________________\n");
		}
	}
	else if (choice == 2)
	{
		printf("������Ҫ��ѯ��������");
		scanf("%s", name);
		st = Search_name(name, L);

		if (st == NULL)
		{
			printf("���޴��ˣ�\n");
		}
		else
		{
			st = st->next;
			printf("________________________________________________________________________________________________\n");
			printf("|ѧ��\t|����\t|�Ա�\t|����\t|ѧ��\t|ְλ\t|����\t|סַ\t\t\t|�绰\t\t|\n");
			printf("________________________________________________________________________________________________\n");
			printf("|%d\t|%s\t|%s\t|%d\t|%s\t|%s\t|%d\t|%s\t\t|%s\t|\n", st->ID, st->Name, st->Sex, st->Age, st->Education, st->Post, st->Wage, st->Room, st->Telephone);
			printf("________________________________________________________________________________________________\n");
		}
	}
}

// ��ѧ�Ž��в���
node* Search_id(int id, node* L)
{
	node* p = L;

	while (p->next != NULL)
	{
		if (p->next->ID == id)
		{
			return p;
		}
		p = p->next;
	}
	return NULL;
}

// ���������в���
node* Search_name(char name[], node* L)
{
	node* p = L;

	while (p->next != NULL)
	{
		if (strcmp(name, p->next->Name) == 0)
		{
			return p;
		}
		p = p->next;
	}
	return NULL;
}

// ���ְ����Ϣ
void Print(node* L)
{
	system("cls");
	node* p = L->next;
	Print_Printf();
	if (p != NULL)
	{
		while (p != NULL)
		{
			printf("________________________________________________________________________________________________\n");
			printf("|%d\t|%s\t|%s\t|%d\t|%s\t|%s\t|%d\t|%s\t\t|%s\t|\n", p->ID, p->Name, p->Sex, p->Age, p->Education, p->Post, p->Wage, p->Room, p->Telephone);
			printf("________________________________________________________________________________________________\n");
			p = p->next;
		}
	}
}

void Print_Printf()
{
	printf("________________________________________________________________________________________________\n");
	printf("|ѧ��\t|����\t|�Ա�\t|����\t|ѧ��\t|ְλ\t|����\t|סַ\t\t\t|�绰\t\t|\n");
	printf("________________________________________________________________________________________________\n");
}

// ����ְ����Ϣ
void Sort(node* L)
{
	system("cls");
	int choice = 0;
	printf("���չ��ʴӴ�С���� ---- 1\n");
	printf("���չ��ʴ�С�������� ---- 2\n");
	printf("��ѡ������ʽ��");
	scanf("%d", &choice);

	int flag = 0;
	for (node* p = L->next; p != NULL; p = p->next)
	{
		for (node* q = p; q != NULL; q = q->next)
		{
			switch (choice)
			{
			case 1:
				if (!cmp_big_Wage(*p, *q))
				{
					flag = 1;
				}
				break;
			case 2:
				if (!cmp_small_Wage(*p, *q))
				{
					flag = 1;
				}
				break;
				if (flag == 1)
				{
					// ����������
					node t = *p;
					*p = *q;
					*q = t;
					// ����ָ����
					t.next = p->next;
					p->next = q->next;
					q->next = t.next;
					flag = 0;
				}
			}
		}
	}
}

// ���ʴӴ�С
bool cmp_big_Wage(node e1, node e2)
{
	return e1.Wage > e2.Wage;
}
// ���ʴ�С����
bool cmp_small_Wage(node e1, node e2)
{
	return e1.Wage < e2.Wage;
}

// �˳�����ϵͳ
void goodbye()
{
	system("cls");
	printf("��ӭ�´�ʹ��ְ����Ϣ����ϵͳ��");
	exit(0);// ��������
}