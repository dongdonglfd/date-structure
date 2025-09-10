#include<stdio.h>
#include<stdlib.h>
typedef struct Node{
    int id;
    int password;
    struct Node* next;
}Node;
Node* createlinklist(int n,int passwords[])
{
    if (n <= 0) return NULL;
    
    Node* head = (Node*)malloc(sizeof(Node));
    head->id = 1;
    head->password = passwords[0];
    head->next = NULL;
    
    Node* current = head;
    for (int i = 2; i <= n; i++) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->id = i;
        newNode->password = passwords[i-1];
        newNode->next = NULL;
        current->next = newNode;
        current = newNode;
    }
    return head;
}
void josephus(int n, int m, int passwords[]) 
{
    Node* head=createlinklist(n,passwords);
    if(head==NULL) return ;
    int currentpassword =m;
    Node* current=head;
    Node*prev=NULL;
    printf("出列顺序: ");
    while(n>0)
    {
        for(int i=1;i<currentpassword;i++)
        {
            prev=current;
            current=current->next;
            if(current==NULL)
            {
                current=head;
                prev=NULL;
            }
        }
        printf("%d", current->id);
        if (n > 1) printf(" -> ");
        currentpassword=current->password;
        if(prev==NULL)
        {
            head=current->next;
            Node* temp = current;
            free(temp);
            current=head;
        }
        else{
            prev->next=current->next;
            Node* temp = current;
            free(temp);
            current=prev->next;
            if(current==NULL)
            {
                current = head;
                prev = NULL;
            }
        }
        n--;
    }
    printf("\n");
}
int main()
{
    int n,m;
    printf("请输入总人数: ");
    scanf("%d", &n);
    printf("请输入初始密码: ");
    scanf("%d", &m);
    int * passwords=(int *)malloc(n*sizeof(int));
    printf("请依次输入%d个人的密码:\n", n);
    for (int i = 0; i < n; i++) {
        printf("人员 %d 的密码: ", i+1);
        scanf("%d", &passwords[i]);
    }
    // 求解约瑟夫环问题
    josephus(n, m, passwords);
    
    // 释放内存
    free(passwords);
    
    return 0;

}
