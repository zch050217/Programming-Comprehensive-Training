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
struct student *chuanjiang(struct student *h,struct student *pnew){//���� 
	static int k=1;
	struct student *head;
	head=(struct student*)malloc(sizeof(struct student));
	printf("����������");
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

void tianjia(struct student *h,struct student *pnew,int v){//��� 
	int j;
	struct student *head=h;
	for(j=1;j<v&&head;j++){
		head=head->next;
	}
	pnew->next=head->next;
	head->next=pnew;
}

void shanchu(struct student *h,int v){//ɾ�� 
	int j;
	struct student *head=h;
	for(j=1;j<v&&head;j++){
		head=head->next;
	}
	head->next=head->next->next;
}
void maopao(struct student *h,int v){//���� 
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
		printf("������ѧ��:");
		scanf("%d",&n);
		for(p=h->next;p!=NULL;p=p->next){
			if(p->xh==n){
				printf("%ld %s %0.lf %0.lf\n",p->xh,p->xm,p->cj[0],p->cj[1]);
				return;
			}
		}
		printf("�Ҳ�������Ϣ\n");
	}
	if(v==2){
		printf("����������:");
		scanf("%s",cx);
		for(p=h->next;p!=NULL;p=p->next){
			if(strcmp(p->xm,cx)==0){
				printf("%ld %s %0.lf %0.lf\n",p->xh,p->xm,p->cj[0],p->cj[1]);
				return;
			}
		}
		printf("�Ҳ�������Ϣ\n");
	}
	if(v==3){
		printf("�����������");
		scanf("%lf",&fs);
		for(p=h->next;p!=NULL;p=p->next){
			if(p->cj[0]>=fs){
				printf("%ld %s %0.lf\n",p->xh,p->xm,p->cj[0]);
			    count++;
			}
		}
		printf("����%d\n",count);
	}
	if(v==4){
		printf("�����������");
		scanf("%lf",&fs);
		for(p=h->next;p!=NULL;p=p->next){
			if(p->cj[1]>=fs){
				printf("%ld %s %0.lf\n",p->xh,p->xm,p->cj[1]);
			    count++;
			}
		}
		printf("%����d\n",count);
	}
	if(v==5){
		printf("�������ܷ֣�");
		scanf("%lf",&fs);
		for(p=h->next;p!=NULL;p=p->next){
			if(p->cj[1]+p->cj[0]>=fs){
				printf("%ld %s %0.lf %0.lf\n",p->xh,p->xm,p->cj[0],p->cj[1]);
				count++;
			}
		}
		printf("%����d\n",count);
	}
}

int main(){
	struct student *h=NULL,*p1,*p2,*p;
	int n,v;
	printf("1���½�����\n2���������\n3��ɾ������\n4������\n5����ѯ\n6���˳���Ļ��ʾ�����������ѡ����Ӧ����:");
	scanf("%d",&n);
	while(n!=6){
		if(n==1){
			p1=(struct student*)malloc(sizeof(struct student));
			h=chuanjiang(h,p1);
			zs++;
		}
		if(n==2){
			printf("��ӵ��ڼ�λ��");
			scanf("%d",&v); 
			p1=(struct student*)malloc(sizeof(struct student));
			printf("����������"); 
			scanf("%ld %s %lf %lf",&p1->xh,p1->xm,&p1->cj[0],&p1->cj[1]);
			tianjia(h,p1,v);
			zs++;
		}
		if(n==3){
			printf("ɾ���ڼ�λ��");
			scanf("%d",&v); 
			shanchu(h,v);
			zs--;
		}
		if(n==4){
			printf("1����ѧ�ɼ�����\n2��������Ƴɼ�����\n3���ܷ�����\n4���������˵�\n�밴���ѡ����Ӧ����:");
			scanf("%d",&v);
			if(v!=4){
		      maopao(h,v);
			} 
		}
		if(n==5){
			printf("1��ѧ�Ų�ѯ\n2��������ѯ\n3����ѧ�ɼ���ѯ\n4��������Ƴɼ���ѯ\n5���ֲܷ�ѯ\n6���������˵�\n�����ѡ����Ӧ����:");
			scanf("%d",&v);
			if(v!=6){
				chaxun(h,p,v); 
			}
		}
		printf("1���½�����\n2���������\n3��ɾ������\n4������\n5����ѯ\n6���˳���Ļ��ʾ�����������ѡ����Ӧ����:");
		scanf("%d",&n);
	}
}