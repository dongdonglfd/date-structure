#include<stdio.h>
#include<stdbool.h>
#include<string.h>
//静态存储
typedef struct
{
    char ch[255];
    int length;
}sstring;
//动态存储
typedef struct
{
    char *ch;
    int length;
}hstring;
//链式存储
typedef struct stringnode
{
    char ch;//每一个节点存储一个字符
    struct stringnode*next;
}stringnode,*string;
typedef struct stringnNode
{
    char ch[4];//每个节点多个字符
    struct stringNode *next;
}stringNode,*String;
//求子串
bool substring(sstring *sub,sstring s,int pos,int len)
{
    int j=0;
    if(pos+len-1>s.length) return false;
    for(int i=pos;i<pos+len;i++)
    {
        sub->ch[j]=s.ch[i];
        j++;
    }
    sub->ch[len]='\0';
    sub->length = len;
    return true;
}
//定位操作
int dingwei(sstring s,sstring t)
{
    int i=0;
    int n=strlen(s.ch);
    int m=strlen(t.ch);
    sstring sub;
    while(i<n-m+1)
    {
        substring(&sub,s,i,m);
        printf("%s\n",sub.ch);
        if(strcmp(sub.ch,t.ch)!=0)
        {
            ++i;
        }
        else return i;
    }
    return -1;
}
//朴素模式匹配算法
int pusu(sstring s,sstring t)
{
    int i=0,j=0;
    int n=strlen(s.ch);
    int m=strlen(t.ch);
    while(i<n&&j<m)
    {
        if(s.ch[i]==t.ch[j])
        {
            ++i;
            ++j;
        }
        else
        {
            i=i-j+1;
            j=0;
        }
    }
    if(j>=m)
        return i-m;
    else
        return -1;
}
int main()
{   
    sstring s,x;
    strcpy(s.ch, "hello world");
    strcpy(x.ch, "llo");
    int k=dingwei(s,x);
    printf("%d\n",k);
    int p=pusu(s,x);
    printf("%d\n",p);
    // s.length=strlen(s.ch);
    // substring(&x,s,1,2);
    // printf("%s",x.ch);   
}