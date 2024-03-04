#include<stdio.h> 
#include<stdlib.h>
#include<string.h>
int zs=0;
struct student{
	long xh;
	char xm[5];
	double cj[2];
	struct student *next;
}; 
struct student *chuanjiang(struct student *h,struct student *pnew){//创建 
	static int k=1;
	struct student *head;
	head=(struct student*)malloc(sizeof(struct student));
	printf("请输入数据");
	scanf("%ld %s %lf %lf",&pnew->xh,pnew->xm,&pnew->cj[0],&pnew->cj[1]);
	if(k==1){
		pnew->next=NULL;
		head->next=pnew;
		k++;
	} else{
		head=h;
		while(head->next!=NULL){
			head=head->next;
		}
		pnew->next=NULL;
		head->next=pnew;
		head=h;
	}
	return head;
}

void tianjia(struct student *h,struct student *pnew,int v){//添加 
	int j;
	struct student *head=h;
	for(j=1;j<v&&head;j++){
		head=head->next;
	}
	pnew->next=head->next;
	head->next=pnew;
}

void shanchu(struct student *h,int v){//删除 
	int j;
	struct student *head=h;
	for(j=1;j<v&&head;j++){
		head=head->next;
	}
	head->next=head->next->next;
}
void maopao(struct student *h,int v){//排序 
	int i,j;
	struct student *head,*p,*q,*tmp;
	head=(struct student*)malloc(sizeof(struct student));
	tmp=(struct student*)malloc(sizeof(struct student));
	head->next=h;
	for(i=0;i<zs-1;i++){
		head=h;
		p=head->next;
		q=p->next;
		for(j=0;j<zs-1-i&&p!=NULL;j++){
			if(v==1){
				if(p->cj[0]>q->cj[0]){
				head->next=q;
				p->next=q->next;
				q->next=p;
				tmp=q;
				q=p;
				p=tmp;
			    }
			} else if(v==2){
				if(p->cj[1]>q->cj[1]){
				head->next=q;
				p->next=q->next;
				q->next=p;
				tmp=q;
				q=p;
				p=tmp;
			    }
			} else if(v==3){
				if((p->cj[0]+p->cj[1])>(q->cj[0]+q->cj[1])){
				head->next=q;
				p->next=q->next;
				q->next=p;
				tmp=q;
				q=p;
				p=tmp;
			  }
			}
			head=head->next;
			p=p->next;
			q=q->next;
		}
	}
}

void chaxun(struct student *h,struct student *p,int v){
	int n,count=0;
	double fs;
	char cx[5]; 
	if(v==1){
		printf("请输入学号:");
		scanf("%d",&n);
		for(p=h->next;p!=NULL;p=p->next){
			if(p->xh==n){
				printf("%ld %s %0.lf %0.lf\n",p->xh,p->xm,p->cj[0],p->cj[1]);
				return;
			}
		}
		printf("找不到该信息\n");
	}
	if(v==2){
		printf("请输入姓名:");
		scanf("%s",cx);
		for(p=h->next;p!=NULL;p=p->next){
			if(strcmp(p->xm,cx)==0){
				printf("%ld %s %0.lf %0.lf\n",p->xh,p->xm,p->cj[0],p->cj[1]);
				return;
			}
		}
		printf("找不到该信息\n");
	}
	if(v==3){
		printf("请输入分数：");
		scanf("%lf",&fs);
		for(p=h->next;p!=NULL;p=p->next){
			if(p->cj[0]>=fs){
				printf("%ld %s %0.lf\n",p->xh,p->xm,p->cj[0]);
			    count++;
			}
		}
		printf("人数%d\n",count);
	}
	if(v==4){
		printf("请输入分数：");
		scanf("%lf",&fs);
		for(p=h->next;p!=NULL;p=p->next){
			if(p->cj[1]>=fs){
				printf("%ld %s %0.lf\n",p->xh,p->xm,p->cj[1]);
			    count++;
			}
		}
		printf("%人数d\n",count);
	}
	if(v==5){
		printf("请输入总分：");
		scanf("%lf",&fs);
		for(p=h->next;p!=NULL;p=p->next){
			if(p->cj[1]+p->cj[0]>=fs){
				printf("%ld %s %0.lf %0.lf\n",p->xh,p->xm,p->cj[0],p->cj[1]);
				count++;
			}
		}
		printf("%人数d\n",count);
	}
}

int main(){
	struct student *h=NULL,*p1,*p2,*p;
	int n,v;
	printf("1．新建数据\n2．添加数据\n3．删除数据\n4．排序\n5．查询\n6．退出屏幕提示：请输入序号选择相应操作:");
	scanf("%d",&n);
	while(n!=6){
		if(n==1){
			p1=(struct student*)malloc(sizeof(struct student));
			h=chuanjiang(h,p1);
			zs++;
		}
		if(n==2){
			printf("添加到第几位？");
			scanf("%d",&v); 
			p1=(struct student*)malloc(sizeof(struct student));
			printf("请输入数据"); 
			scanf("%ld %s %lf %lf",&p1->xh,p1->xm,&p1->cj[0],&p1->cj[1]);
			tianjia(h,p1,v);
			zs++;
		}
		if(n==3){
			printf("删除第几位？");
			scanf("%d",&v); 
			shanchu(h,v);
			zs--;
		}
		if(n==4){
			printf("1．数学成绩排序\n2．程序设计成绩排序\n3．总分排序。\n4．返回主菜单\n请按序号选择相应操作:");
			scanf("%d",&v);
			if(v!=4){
		      maopao(h,v);
			} 
		}
		if(n==5){
			printf("1．学号查询\n2．姓名查询\n3．数学成绩查询\n4．程序设计成绩查询\n5．总分查询\n6．返回主菜单\n按序号选择相应操作:");
			scanf("%d",&v);
			if(v!=6){
				chaxun(h,p,v); 
			}
		}
		printf("1．新建数据\n2．添加数据\n3．删除数据\n4．排序\n5．查询\n6．退出屏幕提示：请输入序号选择相应操作:");
		scanf("%d",&n);
	}
}