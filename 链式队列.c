#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
typedef struct lnode
{
    int date;
    struct lnode *next;
}lnode;
typedef struct 
{
    lnode * front,*rear;//队头队尾指针
}linkqueue;
//初始化
void initqueue(linkqueue*q)
{
    q->front=q->rear=(lnode *)malloc(sizeof(lnode));
    q->front->next=NULL;
}
//判断是否为空
bool isempty(linkqueue q)
{
    if(q.rear==q.front) return true;
    else return false;
}
//入队
void enqueue(linkqueue *q,int e)
{
    struct lnode*s=(lnode *)malloc(sizeof(lnode));
    s->date=e;
    s->next=NULL;
    q->rear->next=s;
    q->rear=s;
}
//出队
bool dequeue(linkqueue *q,int x)
{
    if(q->rear==q->front) return false;
    lnode *p=q->front->next;
    x=p->date;
    q->front->next=p->next;
    if(q->rear=p) q->rear=q->front;
    free(p);
    return true; 
}
int main()
{
    linkqueue q;
    initqueue(&q);

}