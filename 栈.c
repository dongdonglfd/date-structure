#include<stdio.h>
#include<stdbool.h>
typedef struct
{
    int date[10];
    int top;
}sqstack;
//初始化栈
void initstack(sqstack *s)
{
    s->top=-1;
}
//判断栈是否为空
bool stackempty(sqstack s)
{
    if(s.top==-1) return true;
    else return false;
}
//进栈
bool push(sqstack *s,int e)
{
    if(s->top==10-1) return false;
    s->top=s->top+1;
    s->date[s->top]=e;
    return true;
}
//出栈
bool pop(sqstack*s,int e)
{
    if(s->top==-1) return false;
    e=s->date[s->top];
    s->top=s->top-1;
    return true;
}
int main()
{
    int e=100;
    sqstack s;
    initstack(&s);
    printf("%d",s.top);
}