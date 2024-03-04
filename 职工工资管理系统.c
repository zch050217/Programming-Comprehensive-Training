#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#define SIZE sizeof(struct person_info)
struct person_info{
	int id;					//职工号
	char name[100];			//姓名
	int sex;				//性别 0-male,1-female
	char position[100];		//职称
	float salary_position;	//职务工资
	float extra_money;		//奖金
	float water_elec_fee;	//水电费
	float insur_fee;		//保险费
	float salary_total;		//实发工资	
	struct person_info *next;
	struct person_info *last;
};
struct person_info* create(int total_num);
void print_data(struct person_info* p);

void show_data(struct person_info* p);
void sort_data(struct person_info* p);

void func6(struct person_info* p);

struct person_info* sortID(struct person_info* p);
struct person_info* sortTOTALSalary(struct person_info* p);
struct person_info* sortsalary_position(struct person_info* p);
struct person_info* sortextra_money(struct person_info* p);

struct person_info* add(struct person_info* p,int n);

struct person_info* delete_main(struct person_info* p);
struct person_info* delete_id(struct person_info* p,int id);
struct person_info* delete_name(struct person_info* p,char name[100]);

struct person_info* find_main(struct person_info* p);
struct person_info* find_id(struct person_info* p,int id);
struct person_info* find_name(struct person_info* p,char name[100]);
struct person_info* find_posi(struct person_info* p,char posi[100]);
void show_main_menu(void)
{
	printf("----------公司职工工资管理系统----------\n");
	printf("|              1.新建                  |\n");
	printf("|              2.显示                  |\n");
	printf("|              3.插入                  |\n");
	printf("|              4.删除                  |\n");
	printf("|              5.查询                  |\n");
	printf("|           6.计算实发工资             |\n");
	printf("|            0.退出本系统              |\n");
	printf("----------------------------------------\n");
}
int main(void)
{
	struct person_info *p;
	bool choose_correct;//choose_correct 以防用户输入不合法指令 
	A:show_main_menu();	//显示开始界面 
	int user_choose; 	// user_choose 记录用户的选择
	
	printf("请选择功能对应的序号\n");
	scanf("%d",&user_choose);
	
	if(user_choose==1)
	{
		printf("您的选择是 %d 新建数据\n",user_choose);
		int total_num;
		printf("请输入公司员工总数："); 
		scanf("%d",&total_num);
		printf("请依次输入%d名员工的信息：职工号、姓名、性别、职称、职务工资、奖金、水电费、保险费\n\n",total_num);
		p=create(total_num);
		print_data(p);
		goto A;
	}
	if(user_choose==2)
	{
		printf("您的选择是 %d 显示数据\n",user_choose);
		print_data(p);
		//当选择显示功能时，用户可以选择按某种排序形式显示，
		//如按职工号或姓名的顺序、工资总额的顺序、职务工资或奖金的顺序
		show_data(p);
		goto A;
	}
	if(user_choose==6)
	{
		printf("您的选择是 %d 计算实发工资\n",user_choose);
		func6(p);
		goto A;
	}
	if(user_choose==3)
	{
		printf("您的选择是 %d 插入数据\n",user_choose);
		int func3_add; 		////记录要添加的人数 
		printf("请输入添加人数：");
		scanf("%d",&func3_add);
		p=add(p,func3_add);
		printf("操作成功\n\n");
		goto A;
	}
	if(user_choose==4)
	{
		printf("您的选择是 %d 删除数据\n",user_choose);
		p=delete_main(p);
		goto A;
	}
	if(user_choose==5)
	{
		printf("您的选择是 %d 查询数据\n",user_choose);
		p=find_main(p);
		goto A;
	}
	if(user_choose == 0)
	{
		printf("您的选择是 %d 退出本系统\n",user_choose);
		printf("感谢使用本系统,再见\n");
	}
	return 0;
}


struct person_info* create(int total_num)
{
	struct person_info *head,*p,*q;
	q=p=head=(struct person_info*)malloc(SIZE);
	head->last=NULL;
	int i;
	for(i=0;i<total_num;i++)
	{
		p=(struct person_info*)malloc(SIZE);
		q->next=p;
		p->last=q;
		q=p;
		printf("请输入第%d名员工的 职工号：",i+1);
		scanf("%d",&q->id);
		printf("请输入第%d名员工的 姓名：",i+1);
		scanf("%s",q->name);
		printf("请输入第%d名员工的 性别[0-男性，1-女性]：",i+1);
		scanf("%d",&q->sex);
		printf("请输入第%d名员工的 职称：",i+1);
		scanf("%s",q->position);
		printf("请输入第%d名员工的 职务工资：",i+1);
		scanf("%f",&q->salary_position);
		printf("请输入第%d名员工的 奖金：",i+1);
		scanf("%f",&q->extra_money);
		printf("请输入第%d名员工的 水电费：",i+1);
		scanf("%f",&q->water_elec_fee);
		printf("请输入第%d名员工的 保险费：",i+1);
		scanf("%f",&q->insur_fee);
		q->salary_total = q->salary_position + q->extra_money - q->water_elec_fee - q->insur_fee;
		printf("第%d名员工信息录入成功！\n\n",i+1);
	}
	q->next=NULL;
	printf("操作成功,成功读入%d名员工信息！！\n\n",i);
	return(head);
	
}
void print_data(struct person_info* p)
{
	printf("\n\n-------------------输出员工信息----------------------\n");
	printf("职工号   姓名     性别         职称       实发工资       \n");
	struct person_info *i;
	for(i=p->next;i!=NULL;i=i->next)
	{
		printf("%4d   %6s    %6s    %8s  %10.3f\n",i->id,i->name,(i->sex==0)?"male":"female",i->position,i->salary_total);
	}
	
	if(p->next==NULL)printf("NULL");
	printf("---------------  员工信息输出完毕--------------------\n");
	printf("\n");
}

void show_data(struct person_info* p)
{
	B:struct person_info* tmp;
	printf("1、按职工号排序\n");
	printf("2、按姓名排序\n");
	printf("3、按工资总额排序\n");
	printf("4、按职务工资排序\n");
	printf("5、按奖金排序\n");
	printf("0、返回主菜单\n\n");
	printf("请输入您的选择");
	int option_choose;
	scanf("%d",&option_choose);
	if(option_choose==1)
	{
		printf("\n\n\n按职工号排序\n");
		tmp=sortID(p);
		print_data(tmp);
		goto B;
	}
	if(option_choose==3)
	{
		printf("\n\n\n按工资总额排序\n");
		tmp=sortTOTALSalary(p);
		print_data(tmp);
		goto B;
	}
	if(option_choose==4)
	{
		printf("\n\n\n按职务工资排序\n");
		tmp=sortsalary_position(p);
		print_data(tmp);
		goto B;
	}
	if(option_choose==5)
	{
		printf("\n\n\n按奖金排序\n");
		tmp=sortextra_money(p);
		print_data(tmp);
		goto B;
	}
}

void func6(struct person_info* p)
{
	printf("\n\n-------------------计算实发工资----------------------\n");
	printf("职工号   姓名     性别         职称       **实发工资**       \n");
	struct person_info *i;
	for(i=p->next;i!=NULL;i=i->next)
	{
		printf("%4d   %6s    %6s    %8s   %10.3f \n",i->id,i->name,(i->sex==0)?"male":"female",i->position,i->salary_total);
	}
	
	if(p->next==NULL)printf("NULL");
	printf("---------------  实发工资输出完毕--------------------\n");
	printf("\n");
}

struct person_info* sortID(struct person_info* p)
{
	struct person_info *i,*head,*x,*y;
	int i1,i2,n;
	head=p;
	for(n=-1;p!=NULL;p=p->next,n++);
	i1=n;
	while(i1>1)
	{
		i=head;
		i2=n-i1;
		while(i2<n-1)
		{
			if(i->next->next->id<i->next->id)
			{
				y=i->next->next->next;
				x=i->next;
				i->next=i->next->next;
				i->next->next=x;
				x->next=y;
			}
			i=i->next;
			i2++;
		}
		i1--;
	}
	return(head);
}
struct person_info* sortTOTALSalary(struct person_info* p)
{
	struct person_info *i,*head,*x,*y;
	int i1,i2,n;
	head=p;
	for(n=-1;p!=NULL;p=p->next,n++);
	i1=n;
	while(i1>1)
	{
		i=head;
		i2=n-i1;
		while(i2<n-1)
		{
			if(i->next->next->salary_total>i->next->salary_total)
			{
				y=i->next->next->next;
				x=i->next;
				i->next=i->next->next;
				i->next->next=x;
				x->next=y;
			}
			i=i->next;
			i2++;
		}
		i1--;
	}
	return(head);
}
struct person_info* sortsalary_position(struct person_info* p)
{
	struct person_info *i,*head,*x,*y;
	int i1,i2,n;
	head=p;
	for(n=-1;p!=NULL;p=p->next,n++);
	i1=n;
	while(i1>1)
	{
		i=head;
		i2=n-i1;
		while(i2<n-1)
		{
			if(i->next->next->salary_position>i->next->salary_position)
			{
				y=i->next->next->next;
				x=i->next;
				i->next=i->next->next;
				i->next->next=x;
				x->next=y;
			}
			i=i->next;
			i2++;
		}
		i1--;
	}
	return(head);
}
struct person_info* sortextra_money(struct person_info* p)
{
	struct person_info *i,*head,*x,*y;
	int i1,i2,n;
	head=p;
	for(n=-1;p!=NULL;p=p->next,n++);
	i1=n;
	while(i1>1)
	{
		i=head;
		i2=n-i1;
		while(i2<n-1)
		{
			if(i->next->next->extra_money>i->next->extra_money)
			{
				y=i->next->next->next;
				x=i->next;
				i->next=i->next->next;
				i->next->next=x;
				x->next=y;
			}
			i=i->next;
			i2++;
		}
		i1--;
	}
	return(head);
}


struct person_info* add(struct person_info* p,int n)
{
	int i;
	struct person_info *head,*q;
	head=p;
	for(;p->next!=NULL;p=p->next);	//遍历 ，直到最后一个尾结点 
	q=p,p=p->next;
	for(i=0;i<n;i++)
	{
		p=(struct person_info*)malloc(SIZE);
		q->next=p;
		p->last=q;
		q=p;
		printf("请输入第%d名员工的 职工号：",i+1);
		scanf("%d",&q->id);
		printf("请输入第%d名员工的 姓名：",i+1);
		scanf("%s",q->name);
		printf("请输入第%d名员工的 性别[0-男性，1-女性]：",i+1);
		scanf("%d",&q->sex);
		printf("请输入第%d名员工的 职称：",i+1);
		scanf("%s",q->position);
		printf("请输入第%d名员工的 职务工资：",i+1);
		scanf("%f",&q->salary_position);
		printf("请输入第%d名员工的 奖金：",i+1);
		scanf("%f",&q->extra_money);
		printf("请输入第%d名员工的 水电费：",i+1);
		scanf("%f",&q->water_elec_fee);
		printf("请输入第%d名员工的 保险费：",i+1);
		scanf("%f",&q->insur_fee);
		q->salary_total = q->salary_position + q->extra_money - q->water_elec_fee - q->insur_fee;
		printf("第%d名员工信息录入成功！\n\n",i+1);
	}
	q->next=NULL;
	return(head);
}

struct person_info* delete_main(struct person_info* p)
{
	printf("\n----------提示：可以根据职工号或姓名删除数据----------\n");
	printf("1.根据职工号删除数据\n");
	printf("2.根据姓名删除数据\n");
	printf("3.返回主菜单\n");
	printf("--------------------------------------------------------\n");
	int func4_choose;
	printf("请选择功能对应的序号:\n");
	scanf("%d",&func4_choose);
	if(func4_choose == 1)
	{
		int id_input;
		printf("请输入要删除的职工号:\n");
		scanf("%d",&id_input);
		p=delete_id(p,id_input);
		print_data(p);
	}
	if(func4_choose == 2)
	{
		char de_name[100];
		printf("请输入要删除的姓名:\n");
		scanf("%s",de_name);
		p=delete_name(p,de_name);
		print_data(p);
	}
	return (p);
}

struct person_info* delete_id(struct person_info* p,int id)
{
	struct person_info *b,*c,*head;
	head=c=p;
	b=head->next;
	while(b!=NULL)
	{
		if(b->id== id)
		{
			printf("确认删除 id 为 [%d] 姓名 为 [%s] 的数据？【删除请输入1，取消此操作请输入0】 ",id,b->name);
			int check1;
			scanf("%d",&check1);
			if(check1==1)
			{
				c->next=b->next;
				free(b);
				printf("操作成功\n\n");
			}
			if(check1==0)
			{
				printf("终止操作\n\n");
				break; 
			}
		}
		else c=b;
		b=c->next;
	}
	return(head);
}

struct person_info* delete_name(struct person_info* p,char name[100])
{
	struct person_info *b,*c,*head;
	head=c=p;
	b=head->next;
	while(b!=NULL)
	{
		if(strcmp(name,b->name) == 0)
		{
			printf("确认删除 id 为 [%d] 姓名 为 [%s] 的数据？【删除请输入1，取消此操作请输入0】 ",b->id,b->name);
			int check1;
			scanf("%d",&check1);
			if(check1==1)
			{
				c->next=b->next;
				free(b);
				printf("操作成功\n\n");
			}
			if(check1==0)
			{
				printf("终止操作\n\n");
				break; 
			}
		}
		else c=b;
		b=c->next;
	}
	return(head);
}

struct person_info* find_main(struct person_info* p)
{
	//当选择查询功能时，用户可以按某种方式查询，如按职工号或姓名查询、按职称查询等；用户也可以查询某一范围内的数据，
	//如工资总额小于2000元的职工的数据，介于1000～2000元的职工的数据等，根据具体要求列出菜单供用户选择。
	printf("\n----------提示：可以根据职工号、姓名、职称查询数据------\n");
	printf("1.根据职工号查询数据\n");
	printf("2.根据姓名查询数据\n");
	printf("3.根据职称查询数据\n");
	printf("4.返回主菜单\n");
	printf("--------------------------------------------------------\n");
	int func5_choose;
	printf("请选择功能对应的序号:\n");
	scanf("%d",&func5_choose);
	if(func5_choose==1)
	{
		int id_ch;
		printf("请输入要查询的职工号:\n");
		scanf("%d",&id_ch);
		find_id(p,id_ch);
	}
	if(func5_choose==2)
	{
		char ch_name[100];
		printf("请输入要查询的姓名:\n");
		scanf("%s",ch_name);
		find_name(p,ch_name);
	}
	if(func5_choose==3)
	{
		char ch_posi[100];
		printf("请输入要查询的职称:\n");
		scanf("%s",ch_posi);
		find_posi(p,ch_posi);
	}
}

struct person_info* find_id(struct person_info* p,int id)
{
	struct person_info *b,*c,*head;
	bool find=false;
	head=c=p;
	b=head->next;
	while(b!=NULL)
	{
		if(b->id== id)
		{
			find=true;
			printf("找到 id 为 [%d] 姓名 为 [%s] 的数据\n\n",id,b->name);
			printf("职工号   姓名     性别         职称       **实发工资**       \n");
			printf("%4d   %6s    %6s    %8s   %10.3f \n",b->id,b->name,(b->sex==0)?"male":"female",b->position,b->salary_total);
			break; 
		}
		else c=b;
		b=c->next;
	}
	if(!find) printf("没有找到 id 为 %d 的数据\n\n",id);
	return(head);
}

struct person_info* find_name(struct person_info* p,char name1[100])
{
	struct person_info *b,*c,*head;
	bool find=false;
	head=c=p;
	b=head->next;
	while(b!=NULL)
	{
		if(strcmp(name1,b->name) == 0)
		{
			find=true;
			printf("找到 id 为 [%d] 姓名 为 [%s] 的数据\n\n",b->id,b->name);
			printf("职工号   姓名     性别         职称       **实发工资**       \n");
			printf("%4d   %6s    %6s    %8s   %10.3f \n",b->id,b->name,(b->sex==0)?"male":"female",b->position,b->salary_total);
			break; 
		}
		else c=b;
		b=c->next;
	}
	if(!find) printf("没有找到 姓名 为 %s 的数据\n\n",name1);
	return(head);
}

struct person_info* find_posi(struct person_info* p,char posi[100])
{
	struct person_info *b,*c,*head;
	bool find=false;
	head=c=p;
	b=head->next;
	while(b!=NULL)
	{
		if(strcmp(posi,b->position) == 0)
		{
			find=true;
			printf("找到 职称为 为 [%s] 的数据\n\n",b->position);
			printf("职工号   姓名     性别         职称       **实发工资**       \n");
			printf("%4d   %6s    %6s    %8s   %10.3f \n",b->id,b->name,(b->sex==0)?"male":"female",b->position,b->salary_total);
		}
		c=b;
		b=c->next;
	}
	if(!find) printf("没有找到 职称 为 %s 的数据\n\n",posi);
	return(head);
}