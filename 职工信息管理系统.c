//来源于开发者WE-ubytt
#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<string.h>
typedef struct Node
{
	int ID;// 工号
	char Name[50];// 姓名
	char Sex[10];// 性别
	int Age;// 年龄
	char Education[20];// 学历
	char Post[20];// 职务
	int Wage;// 工资
	char Room[50];// 住址
	char Telephone[20];// 电话

	struct Node* next;// 指针域
}node;

node list;// 链表

// 读取文件
int Read_FILE(node* L);

// 保存文件
int  Save_FILE(node* L);

// 主菜单界面
void welcome();

// 增加职工信息
void Add(node* L, node e);// 功能
void Add_Printf();// 界面

// 删除职工信息
void Delete_Printf(node* L);// 界面
void Delete(node* s);// 功能

// 修改职工信息
void Fix(node* L);

// 查询职工信息
void Search_Printf(node* L);// 界面
node* Search_id(int id, node* L);// 按工号进行查找
node* Search_name(char name[], node* L);// 按姓名进行查找

// 输出职工信息
void Print(node* L);// 功能
void Print_Printf();// 界面

// 排序职工信息
void Sort(node* L);
bool cmp_big_Wage(node e1, node e2);// 工资从大到小
bool cmp_small_Wage(node e1, node e2);// 工资从小到大

// 退出管理系统
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
		case 1:// 增加职工信息
			Add_Printf();
			break;
		case 2:// 删除职工信息
			Delete_Printf(&list);
			break;
		case 3:// 修改职工信息
			Fix(&list);
			break;
		case 4:// 查询职工信息
			Search_Printf(&list);
			break;
		case 5:// 输出职工信息
			Print(&list);
			break;
		case 6:// 排序职工信息
			Sort(&list);
			break;
		case 0:// 退出职工系统
			goodbye();
			break;
		}
		printf("是否需要继续操作？（Yes：1 / No：0)：");
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
	printf("***********             职工信息管理系统             ***********\n");
	printf("***********          1 ---- 增加职工信息             ***********\n");
	printf("***********          2 ---- 删除职工信息             ***********\n");
	printf("***********          3 ---- 修改职工信息             ***********\n");
	printf("***********          4 ---- 查询职工信息             ***********\n");
	printf("***********          5 ---- 输出职工信息             ***********\n");
	printf("***********          6 ---- 排序职工信息             ***********\n");
	printf("***********          0 ---- 退出管理系统             ***********\n");
	printf("****************************************************************\n");

	printf("请选择想要实现的功能（数字）：");
}

// 读取文件
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

		// 尾插法
		t->next = s;
		t = s;
		t->next = NULL;
	}

	return 1;
}

// 保存文件
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

// 增加职工信息
void Add_Printf()
{
	system("cls");
	node st;
	printf("请输入新增职工的相关信息：\n");
	printf("工号：");
	scanf("%d", &st.ID);
	printf("姓名：");
	scanf("%s", st.Name);
	printf("性别：");
	scanf("%s", st.Sex);
	printf("年龄：");
	scanf("%d", &st.Age);
	printf("学历：");
	scanf("%s", st.Education);
	printf("职务：");
	scanf("%s", st.Post);
	printf("工资：");
	scanf("%d", &st.Wage);
	printf("住址：");
	scanf("%s", st.Room);
	printf("电话：");
	scanf("%s", &st.Telephone);

	Add(&list, st);
}

void Add(node* L, node e)
{
	// 头插法
	node* p = L;
	node* s = (node*)malloc(sizeof(node));
	*s = e;

	s->next = p->next;
	p->next = s;

	Save_FILE(L);
}

// 删除职工信息
void Delete_Printf(node* L)
{
	system("cls");
	int id;

	node* p;

	printf("请输入要删除的职工的工号：");
	scanf("%d", &id);
	node* st = Search_id(id, L);
	p = st;

	if (st == NULL)
	{
		printf("查无此人！\n");
		return;
	}

	st = st->next;
	printf("________________________________________________________________________________________________\n");
	printf("|学号\t|姓名\t|性别\t|年龄\t|学历\t|职位\t|工资\t|住址\t\t\t|电话\t\t|\n");
	printf("________________________________________________________________________________________________\n");
	printf("|%d\t|%s\t|%s\t|%d\t|%s\t|%s\t|%d\t|%s\t\t|%s\t|\n", st->ID, st->Name, st->Sex, st->Age, st->Education, st->Post, st->Wage, st->Room, st->Telephone);
	printf("________________________________________________________________________________________________\n");

	Delete(p);
	// 保存信息
	Save_FILE(L);
}

void Delete(node* s)
{
	node* t = s->next;

	s->next = t->next;
	t->next = NULL;

	free(t);
}

// 修改职工信息
void Fix(node* L)
{
	system("cls");
	int id;
	printf("请输入要修改的职工的工号：");
	scanf("%d", &id);
	node* st = Search_id(id, L);

	if (st == NULL)
	{
		printf("查无此人！\n");
		return;
	}

	st = st->next;

	int choice = 0;
	while (1)
	{
		system("cls");

		// 输出一次所要修改的职工信息
		printf("________________________________________________________________________________________________\n");
		printf("|学号\t|姓名\t|性别\t|年龄\t|学历\t|职位\t|工资\t|住址\t\t\t|电话\t\t|\n");
		printf("________________________________________________________________________________________________\n");
		printf("|%d\t|%s\t|%s\t|%d\t|%s\t|%s\t|%d\t|%s\t\t|%s\t|\n", st->ID, st->Name, st->Sex, st->Age, st->Education, st->Post, st->Wage, st->Room, st->Telephone);
		printf("________________________________________________________________________________________________\n");

		printf("修改姓名 ---- 1\n");
		printf("修改性别 ---- 2\n");
		printf("修改班级 ---- 3\n");
		printf("修改学历 ---- 4\n");
		printf("修改职位 ---- 5\n");
		printf("修改工资 ---- 6\n");
		printf("修改住址 ---- 7\n");
		printf("修改电话 ---- 8\n");

		printf("请输入要修改的信息：");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			printf("请输入姓名：");
			scanf("%s", st->Name);
			break;
		case 2:
			printf("请输入性别：");
			scanf("%s", st->Sex);
			break;
		case 3:
			printf("请输入年龄：");
			scanf("%d", st->Age);
			break;
		case 4:
			printf("请输入学历：");
			scanf("%s", st->Education);
			break;
		case 5:
			printf("请输入职务：");
			scanf("%s", st->Post);
			break;
		case 6:
			printf("请输入工资：");
			scanf("%d", st->Wage);
			break;
		case 7:
			printf("请输入住址：");
			scanf("%s", st->Room);
			break;
		case 8:
			printf("请输入电话：");
			scanf("%s", st->Telephone);
			break;
		}
		printf("是否继续修改该学生信息？（Yes：1 / No：0）：");
		scanf("%d", &choice);
		if (choice == 0)
		{
			break;
		}
	}

	// 修改完成后该学生的信息
	printf("________________________________________________________________________________________________\n");
	printf("|学号\t|姓名\t|性别\t|年龄\t|学历\t|职位\t|工资\t|住址\t\t\t|电话\t\t|\n");
	printf("________________________________________________________________________________________________\n");
	printf("|%d\t|%s\t|%s\t|%d\t|%s\t|%s\t|%d\t|%s\t\t|%s\t|\n", st->ID, st->Name, st->Sex, st->Age, st->Education, st->Post, st->Wage, st->Room, st->Telephone);
	printf("________________________________________________________________________________________________\n");

	// 保存信息
	Save_FILE(L);
}

// 查询职工信息
void Search_Printf(node* L)
{
	system("cls");
	int choice = 0;
	printf("按照工号查询 ---- 1\n");
	printf("按照姓名查询 ---- 2\n");
	printf("请输入查询方式：");
	scanf("%d", &choice);

	int id;
	char name[50];
	node* st;
	if (choice == 1)
	{
		printf("请输入要查询的工号：");
		scanf("%d", &id);
		st = Search_id(id, L);

		if (st == NULL)
		{
			printf("查无此人！\n");
		}
		else
		{
			st = st->next;
			printf("________________________________________________________________________________________________\n");
			printf("|学号\t|姓名\t|性别\t|年龄\t|学历\t|职位\t|工资\t|住址\t\t\t|电话\t\t|\n");
			printf("________________________________________________________________________________________________\n");
			printf("|%d\t|%s\t|%s\t|%d\t|%s\t|%s\t|%d\t|%s\t\t|%s\t|\n", st->ID, st->Name, st->Sex, st->Age, st->Education, st->Post, st->Wage, st->Room, st->Telephone);
			printf("________________________________________________________________________________________________\n");
		}
	}
	else if (choice == 2)
	{
		printf("请输入要查询的姓名：");
		scanf("%s", name);
		st = Search_name(name, L);

		if (st == NULL)
		{
			printf("查无此人！\n");
		}
		else
		{
			st = st->next;
			printf("________________________________________________________________________________________________\n");
			printf("|学号\t|姓名\t|性别\t|年龄\t|学历\t|职位\t|工资\t|住址\t\t\t|电话\t\t|\n");
			printf("________________________________________________________________________________________________\n");
			printf("|%d\t|%s\t|%s\t|%d\t|%s\t|%s\t|%d\t|%s\t\t|%s\t|\n", st->ID, st->Name, st->Sex, st->Age, st->Education, st->Post, st->Wage, st->Room, st->Telephone);
			printf("________________________________________________________________________________________________\n");
		}
	}
}

// 按学号进行查找
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

// 按姓名进行查找
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

// 输出职工信息
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
	printf("|学号\t|姓名\t|性别\t|年龄\t|学历\t|职位\t|工资\t|住址\t\t\t|电话\t\t|\n");
	printf("________________________________________________________________________________________________\n");
}

// 排序职工信息
void Sort(node* L)
{
	system("cls");
	int choice = 0;
	printf("按照工资从大到小排序 ---- 1\n");
	printf("按照工资从小到大排序 ---- 2\n");
	printf("请选择排序方式：");
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
					// 交换数据域
					node t = *p;
					*p = *q;
					*q = t;
					// 处理指针域
					t.next = p->next;
					p->next = q->next;
					q->next = t.next;
					flag = 0;
				}
			}
		}
	}
}

// 工资从大到小
bool cmp_big_Wage(node e1, node e2)
{
	return e1.Wage > e2.Wage;
}
// 工资从小到大
bool cmp_small_Wage(node e1, node e2)
{
	return e1.Wage < e2.Wage;
}

// 退出管理系统
void goodbye()
{
	system("cls");
	printf("欢迎下次使用职工信息管理系统！");
	exit(0);// 结束程序
}