#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#define SIZE sizeof(struct person_info)
struct person_info{
	int id;					//ְ����
	char name[100];			//����
	int sex;				//�Ա� 0-male,1-female
	char position[100];		//ְ��
	float salary_position;	//ְ����
	float extra_money;		//����
	float water_elec_fee;	//ˮ���
	float insur_fee;		//���շ�
	float salary_total;		//ʵ������	
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
	printf("----------��˾ְ�����ʹ���ϵͳ----------\n");
	printf("|              1.�½�                  |\n");
	printf("|              2.��ʾ                  |\n");
	printf("|              3.����                  |\n");
	printf("|              4.ɾ��                  |\n");
	printf("|              5.��ѯ                  |\n");
	printf("|           6.����ʵ������             |\n");
	printf("|            0.�˳���ϵͳ              |\n");
	printf("----------------------------------------\n");
}
int main(void)
{
	struct person_info *p;
	bool choose_correct;//choose_correct �Է��û����벻�Ϸ�ָ�� 
	A:show_main_menu();	//��ʾ��ʼ���� 
	int user_choose; 	// user_choose ��¼�û���ѡ��
	
	printf("��ѡ���ܶ�Ӧ�����\n");
	scanf("%d",&user_choose);
	
	if(user_choose==1)
	{
		printf("����ѡ���� %d �½�����\n",user_choose);
		int total_num;
		printf("�����빫˾Ա��������"); 
		scanf("%d",&total_num);
		printf("����������%d��Ա������Ϣ��ְ���š��������Ա�ְ�ơ�ְ���ʡ�����ˮ��ѡ����շ�\n\n",total_num);
		p=create(total_num);
		print_data(p);
		goto A;
	}
	if(user_choose==2)
	{
		printf("����ѡ���� %d ��ʾ����\n",user_choose);
		print_data(p);
		//��ѡ����ʾ����ʱ���û�����ѡ��ĳ��������ʽ��ʾ��
		//�簴ְ���Ż�������˳�򡢹����ܶ��˳��ְ���ʻ򽱽��˳��
		show_data(p);
		goto A;
	}
	if(user_choose==6)
	{
		printf("����ѡ���� %d ����ʵ������\n",user_choose);
		func6(p);
		goto A;
	}
	if(user_choose==3)
	{
		printf("����ѡ���� %d ��������\n",user_choose);
		int func3_add; 		////��¼Ҫ��ӵ����� 
		printf("���������������");
		scanf("%d",&func3_add);
		p=add(p,func3_add);
		printf("�����ɹ�\n\n");
		goto A;
	}
	if(user_choose==4)
	{
		printf("����ѡ���� %d ɾ������\n",user_choose);
		p=delete_main(p);
		goto A;
	}
	if(user_choose==5)
	{
		printf("����ѡ���� %d ��ѯ����\n",user_choose);
		p=find_main(p);
		goto A;
	}
	if(user_choose == 0)
	{
		printf("����ѡ���� %d �˳���ϵͳ\n",user_choose);
		printf("��лʹ�ñ�ϵͳ,�ټ�\n");
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
		printf("�������%d��Ա���� ְ���ţ�",i+1);
		scanf("%d",&q->id);
		printf("�������%d��Ա���� ������",i+1);
		scanf("%s",q->name);
		printf("�������%d��Ա���� �Ա�[0-���ԣ�1-Ů��]��",i+1);
		scanf("%d",&q->sex);
		printf("�������%d��Ա���� ְ�ƣ�",i+1);
		scanf("%s",q->position);
		printf("�������%d��Ա���� ְ���ʣ�",i+1);
		scanf("%f",&q->salary_position);
		printf("�������%d��Ա���� ����",i+1);
		scanf("%f",&q->extra_money);
		printf("�������%d��Ա���� ˮ��ѣ�",i+1);
		scanf("%f",&q->water_elec_fee);
		printf("�������%d��Ա���� ���շѣ�",i+1);
		scanf("%f",&q->insur_fee);
		q->salary_total = q->salary_position + q->extra_money - q->water_elec_fee - q->insur_fee;
		printf("��%d��Ա����Ϣ¼��ɹ���\n\n",i+1);
	}
	q->next=NULL;
	printf("�����ɹ�,�ɹ�����%d��Ա����Ϣ����\n\n",i);
	return(head);
	
}
void print_data(struct person_info* p)
{
	printf("\n\n-------------------���Ա����Ϣ----------------------\n");
	printf("ְ����   ����     �Ա�         ְ��       ʵ������       \n");
	struct person_info *i;
	for(i=p->next;i!=NULL;i=i->next)
	{
		printf("%4d   %6s    %6s    %8s  %10.3f\n",i->id,i->name,(i->sex==0)?"male":"female",i->position,i->salary_total);
	}
	
	if(p->next==NULL)printf("NULL");
	printf("---------------  Ա����Ϣ������--------------------\n");
	printf("\n");
}

void show_data(struct person_info* p)
{
	B:struct person_info* tmp;
	printf("1����ְ��������\n");
	printf("2������������\n");
	printf("3���������ܶ�����\n");
	printf("4����ְ��������\n");
	printf("5������������\n");
	printf("0���������˵�\n\n");
	printf("����������ѡ��");
	int option_choose;
	scanf("%d",&option_choose);
	if(option_choose==1)
	{
		printf("\n\n\n��ְ��������\n");
		tmp=sortID(p);
		print_data(tmp);
		goto B;
	}
	if(option_choose==3)
	{
		printf("\n\n\n�������ܶ�����\n");
		tmp=sortTOTALSalary(p);
		print_data(tmp);
		goto B;
	}
	if(option_choose==4)
	{
		printf("\n\n\n��ְ��������\n");
		tmp=sortsalary_position(p);
		print_data(tmp);
		goto B;
	}
	if(option_choose==5)
	{
		printf("\n\n\n����������\n");
		tmp=sortextra_money(p);
		print_data(tmp);
		goto B;
	}
}

void func6(struct person_info* p)
{
	printf("\n\n-------------------����ʵ������----------------------\n");
	printf("ְ����   ����     �Ա�         ְ��       **ʵ������**       \n");
	struct person_info *i;
	for(i=p->next;i!=NULL;i=i->next)
	{
		printf("%4d   %6s    %6s    %8s   %10.3f \n",i->id,i->name,(i->sex==0)?"male":"female",i->position,i->salary_total);
	}
	
	if(p->next==NULL)printf("NULL");
	printf("---------------  ʵ������������--------------------\n");
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
	for(;p->next!=NULL;p=p->next);	//���� ��ֱ�����һ��β��� 
	q=p,p=p->next;
	for(i=0;i<n;i++)
	{
		p=(struct person_info*)malloc(SIZE);
		q->next=p;
		p->last=q;
		q=p;
		printf("�������%d��Ա���� ְ���ţ�",i+1);
		scanf("%d",&q->id);
		printf("�������%d��Ա���� ������",i+1);
		scanf("%s",q->name);
		printf("�������%d��Ա���� �Ա�[0-���ԣ�1-Ů��]��",i+1);
		scanf("%d",&q->sex);
		printf("�������%d��Ա���� ְ�ƣ�",i+1);
		scanf("%s",q->position);
		printf("�������%d��Ա���� ְ���ʣ�",i+1);
		scanf("%f",&q->salary_position);
		printf("�������%d��Ա���� ����",i+1);
		scanf("%f",&q->extra_money);
		printf("�������%d��Ա���� ˮ��ѣ�",i+1);
		scanf("%f",&q->water_elec_fee);
		printf("�������%d��Ա���� ���շѣ�",i+1);
		scanf("%f",&q->insur_fee);
		q->salary_total = q->salary_position + q->extra_money - q->water_elec_fee - q->insur_fee;
		printf("��%d��Ա����Ϣ¼��ɹ���\n\n",i+1);
	}
	q->next=NULL;
	return(head);
}

struct person_info* delete_main(struct person_info* p)
{
	printf("\n----------��ʾ�����Ը���ְ���Ż�����ɾ������----------\n");
	printf("1.����ְ����ɾ������\n");
	printf("2.��������ɾ������\n");
	printf("3.�������˵�\n");
	printf("--------------------------------------------------------\n");
	int func4_choose;
	printf("��ѡ���ܶ�Ӧ�����:\n");
	scanf("%d",&func4_choose);
	if(func4_choose == 1)
	{
		int id_input;
		printf("������Ҫɾ����ְ����:\n");
		scanf("%d",&id_input);
		p=delete_id(p,id_input);
		print_data(p);
	}
	if(func4_choose == 2)
	{
		char de_name[100];
		printf("������Ҫɾ��������:\n");
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
			printf("ȷ��ɾ�� id Ϊ [%d] ���� Ϊ [%s] �����ݣ���ɾ��������1��ȡ���˲���������0�� ",id,b->name);
			int check1;
			scanf("%d",&check1);
			if(check1==1)
			{
				c->next=b->next;
				free(b);
				printf("�����ɹ�\n\n");
			}
			if(check1==0)
			{
				printf("��ֹ����\n\n");
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
			printf("ȷ��ɾ�� id Ϊ [%d] ���� Ϊ [%s] �����ݣ���ɾ��������1��ȡ���˲���������0�� ",b->id,b->name);
			int check1;
			scanf("%d",&check1);
			if(check1==1)
			{
				c->next=b->next;
				free(b);
				printf("�����ɹ�\n\n");
			}
			if(check1==0)
			{
				printf("��ֹ����\n\n");
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
	//��ѡ���ѯ����ʱ���û����԰�ĳ�ַ�ʽ��ѯ���簴ְ���Ż�������ѯ����ְ�Ʋ�ѯ�ȣ��û�Ҳ���Բ�ѯĳһ��Χ�ڵ����ݣ�
	//�繤���ܶ�С��2000Ԫ��ְ�������ݣ�����1000��2000Ԫ��ְ�������ݵȣ����ݾ���Ҫ���г��˵����û�ѡ��
	printf("\n----------��ʾ�����Ը���ְ���š�������ְ�Ʋ�ѯ����------\n");
	printf("1.����ְ���Ų�ѯ����\n");
	printf("2.����������ѯ����\n");
	printf("3.����ְ�Ʋ�ѯ����\n");
	printf("4.�������˵�\n");
	printf("--------------------------------------------------------\n");
	int func5_choose;
	printf("��ѡ���ܶ�Ӧ�����:\n");
	scanf("%d",&func5_choose);
	if(func5_choose==1)
	{
		int id_ch;
		printf("������Ҫ��ѯ��ְ����:\n");
		scanf("%d",&id_ch);
		find_id(p,id_ch);
	}
	if(func5_choose==2)
	{
		char ch_name[100];
		printf("������Ҫ��ѯ������:\n");
		scanf("%s",ch_name);
		find_name(p,ch_name);
	}
	if(func5_choose==3)
	{
		char ch_posi[100];
		printf("������Ҫ��ѯ��ְ��:\n");
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
			printf("�ҵ� id Ϊ [%d] ���� Ϊ [%s] ������\n\n",id,b->name);
			printf("ְ����   ����     �Ա�         ְ��       **ʵ������**       \n");
			printf("%4d   %6s    %6s    %8s   %10.3f \n",b->id,b->name,(b->sex==0)?"male":"female",b->position,b->salary_total);
			break; 
		}
		else c=b;
		b=c->next;
	}
	if(!find) printf("û���ҵ� id Ϊ %d ������\n\n",id);
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
			printf("�ҵ� id Ϊ [%d] ���� Ϊ [%s] ������\n\n",b->id,b->name);
			printf("ְ����   ����     �Ա�         ְ��       **ʵ������**       \n");
			printf("%4d   %6s    %6s    %8s   %10.3f \n",b->id,b->name,(b->sex==0)?"male":"female",b->position,b->salary_total);
			break; 
		}
		else c=b;
		b=c->next;
	}
	if(!find) printf("û���ҵ� ���� Ϊ %s ������\n\n",name1);
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
			printf("�ҵ� ְ��Ϊ Ϊ [%s] ������\n\n",b->position);
			printf("ְ����   ����     �Ա�         ְ��       **ʵ������**       \n");
			printf("%4d   %6s    %6s    %8s   %10.3f \n",b->id,b->name,(b->sex==0)?"male":"female",b->position,b->salary_total);
		}
		c=b;
		b=c->next;
	}
	if(!find) printf("û���ҵ� ְ�� Ϊ %s ������\n\n",posi);
	return(head);
}