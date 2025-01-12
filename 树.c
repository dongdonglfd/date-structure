#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"链式队列.c"
struct elemtype
{
    int value;
};
typedef struct bitnode
{
    int date;
    struct bitnode *lchild,*rchild;
}bitnode,*bitree;
//插入新节点
bool insertnode(bitree root,int e)
{
    bitnode *p=(bitnode*)malloc(sizeof(bitnode));
    p->date=e;
    p->lchild=NULL;
    p->rchild=NULL;
    root->lchild=p;//作为根节点的左节点
}
void visit(bitree t)
{
    printf("%d",t->date);
}
//先序遍历
void preorder(bitree t)
{
    if(t!=NULL)
    {
        visit(t);
        preorder(t->lchild);
        preorder(t->rchild);
    }
}
//中序遍历
void inorder(bitree t)
{
    if(t!=NULL)
    {
        inorder(t->lchild);
        visit(t);
        inorder(t->rchild);
    }
}
//后序遍历
void postorder(bitree t)
{
    if(t!=NULL)
    {
        postorder(t->lchild);
        postorder(t->rchild);
        visit(t);
    }
}
//求数的深度
int treedepth(bitree t)
{
    if(t!=NULL)
    {
        return 0;
    }
    else
    {
        int l=treedepth(t->lchild);
        int r=treedepth(t->rchild);
        return l>r ? l+1 : r+1;
    }
    
}
//层次遍历
void levelorder(bitree t)
{
    linkqueue q;
    initqueue(&q);
    bitree p;
    enqueue(&q,t->date);//根节点入队
    while(!isempty(q))
    {
        dequeue(&q,p->date);//队头节点出队
        visit(p);
        if(p->lchild!=NULL)
        {
            enqueue(&q,p->lchild->date);
        }
        if(p->rchild!=NULL)
        {
            enqueue(&q,p->rchild->date);
        }
    }


}
// int main()
// {
//     //定义一颗空树
//     bitree root=NULL;
//     //插入根节点
//     root=(bitree)malloc(sizeof(bitnode));
//     root->date=1;
//     root->lchild=NULL;
//     root->rchild=NULL;
    
// }