#include<stdio.h>
#include<stdbool.h>
typedef struct
{
    int date[10];
    int front,rear;
}sqqueue;
//初始化队列
void initqueue(sqqueue *q)
{
    q->rear=q->front=0;
}
//判断队列是否为空
bool queueempty(sqqueue q)
{
    if(q.rear==q.front) return true;
    else return false;
}
//入队
bool enqueue(sqqueue *q,int e)
{
    if((q->rear+1)%10==q->front) return false;
    q->date[q->rear]=e;
    q->rear=(q->rear+1)%10;
    return true;
}
//出队
bool dequeue(sqqueue *q,int x)
{
    if(q->rear==q->front) return false;
    x=q->date[q->front];
    q->front=(q->front+1)%10;
    return true;
}
//获得队头元素
bool gethead(sqqueue q,int x)
{
    if(q.rear==q.front) return false;
    x=q.date[q.front];
    return true;
}
int main()
{
    sqqueue q;
    initqueue(&q);
    printf("%d %d",q.front,q.rear);
}