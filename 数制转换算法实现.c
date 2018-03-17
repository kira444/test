#include"stdio.h" 
#include"stdlib.h"
#define maxsize 100

typedef struct{/*定义栈,注意此处将数据data定义为字符型，输入数据时必须先统一转化为字符*/
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
		return 0;	/*栈满不能入栈*/
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
}linkqueue,*plinkqueue;/*定义队列*/

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
		printf("内存溢出\n");
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
		printf("队空\n");
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
{//实数的整数部分转化
	pseqstack p;
	char m;
	p=init_seqstack();
	if(n==0)
		printf("0");
	while(n)
	{
		if(n%r>9)//注意此处若是余数大于9则进制肯定大于10进制
		{
			m=(char)(n%r-9+64);//若是余数大于9，则将余数转化为对应的大写字母字符
			push_seqstack(p,m);
		}
		else
		{
			m=(char)(n%r+48);//若是余数小于9，则将余数转化为对应的数字字符
			push_seqstack(p,m);
		}
		n=n/r;
	}
	while(empty_seqstack(p)==0)
		printf("%c",pop_seqstack(p));
	destroy_seqstack(&p);
}

void xiaoshu(double n,int r)
{//实数的小数部分转化
	int i,t=0;
	char m;
	plinkqueue q;
	q=init_linkqueue();
	for(i=0;n!=0&&i<32;i++)//注意！！！若是不限制循环执行次数，此循环可能变成死循环
	{
		t=(int)(n*r);
		if(t>9)//注意此处若是取整得到的数大于9则进制肯定大于10进制
		{
			m=(char)(t-9+64);//若是取整得到的数t大于9，则将t转化为对应的大写字母字符
			in_linkqueue(q,m);
		}
		else
		{
			m=(char)(t+48);//若是取整得到的数t小于9，则将t转化为对应的数字字符
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
	if(n==(int)n)//若实数是整数
		zhengshu((int)n,r);
	else
	{//若实数既有整数部分，又有小数部分
		zhengshu((int)n,r);
		printf(".");
		xiaoshu(n-(int)n,r);
	}
}

void zhuanhua(double n,int r)
{//将任意一个十进制实数转化为r进制数，入口参数：实数n，进制r，出口参数：无
	if(n>=0)
	{//若实数大于等于零
		dayu_ling(n,r);
	}
	else
	{//若实数小于零
		printf("-");//若实数小于零先输出负号
		n=-n;//再取绝对值
		dayu_ling(n,r);//然后运用大于零的实数的转化函数就可以了
	}
	printf("\n");
}

int main()
{
	double n;
	int r;
	printf("请输入想要转化的十进制数：\n");
	if(scanf("%lf",&n)==0)
	{
		printf("输入错误，请输入数字!");
		return -1;
	}
	printf("请输入想要转化的进制r(2~36)：\n");
	scanf("%d",&r);
	if(r>36||r<2)
	{	printf("错误！无法识别当前进制！\n");
		return 0;
	}
	printf("转化为%d进制后为：\n",r);
	zhuanhua(n,r);
	return 1;
}