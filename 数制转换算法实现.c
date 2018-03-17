#include"stdio.h" 
#include"stdlib.h"
#define maxsize 100

typedef struct{/*����ջ,ע��˴�������data����Ϊ�ַ��ͣ���������ʱ������ͳһת��Ϊ�ַ�*/
	char data[maxsize];
	int top; 
}seqstack,*pseqstack;

pseqstack init_seqstack(void)
{
	pseqstack p;
	p=(pseqstack)malloc(sizeof(seqstack));
	if(p)
		p->top=-1;
	return p;
}

int empty_seqstack(pseqstack p)
{
	if(p->top==-1)
		return 1;
	else
		return 0;
}

int push_seqstack(pseqstack p,char c)
{
	if(p->top==maxsize-1)
		return 0;	/*ջ��������ջ*/
	else
	{
		p->top++;
		p->data[p->top]=c;
		return 1;
	}
}

char pop_seqstack(pseqstack p)
{
	char s;
	if(empty_seqstack(p))
		return 0;
	else
	{
		s=p->data[p->top];
		p->top--;
		return s;
	}
}

void destroy_seqstack(pseqstack *p)
{
	if(*p)
		free(*p);
	*p=NULL;
	return;
}

typedef struct node{
	char data;
	struct node *next;
}qnode,*pqnode;
typedef struct{
	pqnode front,rear;
}linkqueue,*plinkqueue;/*�������*/

plinkqueue init_linkqueue(void)
{
	plinkqueue q;
	q=(plinkqueue)malloc(sizeof(linkqueue));
	if(q)
	{
		q->front=NULL;
		q->rear=NULL;
	}
	return(q);
}

int empty_linkqueue(plinkqueue q)
{
	if(q&&q->front==NULL&&q->rear==NULL)
		return(1);
	else
		return(0);
}

int in_linkqueue(plinkqueue q,char x)
{
	pqnode p;
	p=(pqnode)malloc(sizeof(qnode));
	if(!p)
	{
		printf("�ڴ����\n");
		return(0);
	}
	p->data=x;
	p->next=NULL;
	if(empty_linkqueue(q))
		q->rear=q->front=p;
	else
	{
		q->rear->next=p;
		q->rear=p;
	}
	return(1);
}

char out_linkqueue(plinkqueue q)
{
	char s;
	pqnode p;
	if(empty_linkqueue(q))
	{
		printf("�ӿ�\n");
		return(0);
	}
	s=q->front->data;
	p=q->front;
	q->front=q->front->next;
	free(p);
	if(!q->front)
		q->rear=NULL;
	return(s);
}

void destroy_linkqueue(plinkqueue *q)
{
	pqnode p;
	if(*q)
	{
		while((*q)->front)
		{
			p=(*q)->front;
			(*q)->front=(*q)->front->next;
			free(p);
		}
		free(*q);
	}
	*q=NULL;
}

void zhengshu(int n,int r)
{//ʵ������������ת��
	pseqstack p;
	char m;
	p=init_seqstack();
	if(n==0)
		printf("0");
	while(n)
	{
		if(n%r>9)//ע��˴�������������9����ƿ϶�����10����
		{
			m=(char)(n%r-9+64);//������������9��������ת��Ϊ��Ӧ�Ĵ�д��ĸ�ַ�
			push_seqstack(p,m);
		}
		else
		{
			m=(char)(n%r+48);//��������С��9��������ת��Ϊ��Ӧ�������ַ�
			push_seqstack(p,m);
		}
		n=n/r;
	}
	while(empty_seqstack(p)==0)
		printf("%c",pop_seqstack(p));
	destroy_seqstack(&p);
}

void xiaoshu(double n,int r)
{//ʵ����С������ת��
	int i,t=0;
	char m;
	plinkqueue q;
	q=init_linkqueue();
	for(i=0;n!=0&&i<32;i++)//ע�⣡�������ǲ�����ѭ��ִ�д�������ѭ�����ܱ����ѭ��
	{
		t=(int)(n*r);
		if(t>9)//ע��˴�����ȡ���õ���������9����ƿ϶�����10����
		{
			m=(char)(t-9+64);//����ȡ���õ�����t����9����tת��Ϊ��Ӧ�Ĵ�д��ĸ�ַ�
			in_linkqueue(q,m);
		}
		else
		{
			m=(char)(t+48);//����ȡ���õ�����tС��9����tת��Ϊ��Ӧ�������ַ�
			in_linkqueue(q,m);
		}
		n=n*r-t;
	}
	while(empty_linkqueue(q)==0)
		printf("%c",out_linkqueue(q));
	destroy_linkqueue(&q);
}

void dayu_ling(double n,int r)
{
	if(n==(int)n)//��ʵ��������
		zhengshu((int)n,r);
	else
	{//��ʵ�������������֣�����С������
		zhengshu((int)n,r);
		printf(".");
		xiaoshu(n-(int)n,r);
	}
}

void zhuanhua(double n,int r)
{//������һ��ʮ����ʵ��ת��Ϊr����������ڲ�����ʵ��n������r�����ڲ�������
	if(n>=0)
	{//��ʵ�����ڵ�����
		dayu_ling(n,r);
	}
	else
	{//��ʵ��С����
		printf("-");//��ʵ��С�������������
		n=-n;//��ȡ����ֵ
		dayu_ling(n,r);//Ȼ�����ô������ʵ����ת�������Ϳ�����
	}
	printf("\n");
}

int main()
{
	double n;
	int r;
	printf("��������Ҫת����ʮ��������\n");
	if(scanf("%lf",&n)==0)
	{
		printf("�����������������!");
		return -1;
	}
	printf("��������Ҫת���Ľ���r(2~36)��\n");
	scanf("%d",&r);
	if(r>36||r<2)
	{	printf("�����޷�ʶ��ǰ���ƣ�\n");
		return 0;
	}
	printf("ת��Ϊ%d���ƺ�Ϊ��\n",r);
	zhuanhua(n,r);
	return 1;
}