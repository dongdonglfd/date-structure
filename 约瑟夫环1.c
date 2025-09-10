#include <stdio.h>
#include <stdlib.h>

// 定义链表节点结构
typedef struct Node {
    int id;           // 人员编号
    int password;     // 个人密码
    struct Node* next; // 指向下一个节点的指针
} Node;

// 创建循环链表
Node* createCircularList(int n, int passwords[]) {
    if (n <= 0) return NULL;
    
    Node* head = (Node*)malloc(sizeof(Node));
    head->id = 1;
    head->password = passwords[0];
    
    Node* current = head;
    for (int i = 2; i <= n; i++) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->id = i;
        newNode->password = passwords[i-1];
        current->next = newNode;
        current = newNode;
    }
    current->next = head; // 形成循环链表
    return head;
}

// 约瑟夫环求解函数
void josephus(int n, int m, int passwords[]) {
    Node* head = createCircularList(n, passwords);
    if (head == NULL) return;
    
    int currentPassword = m;
    Node* current = head;
    Node* prev = NULL;
    
    // 找到尾节点（即头节点的前一个节点）
    Node* tail = head;
    while (tail->next != head) {
        tail = tail->next;
    }
    prev = tail;  // 初始化prev为尾节点
    
    printf("出列顺序: ");
    
    while (n > 0) {
        // 找到要出列的节点
        for (int i = 1; i < currentPassword; i++) {
            prev = current;
            current = current->next;
        }
        
        // 输出出列人员信息
        printf("%d", current->id);
        if (n > 1) printf(" -> ");
        
        // 更新密码为出列人员的密码
        currentPassword = current->password;
        
        // 从链表中移除节点
        prev->next = current->next;
        
        // 释放节点内存
        Node* temp = current;
        current = current->next;
        free(temp);
        
        n--;
    }
    printf("\n");
}

int main() {
    int n, m;
    
    // 输入人数和初始密码
    printf("请输入总人数: ");
    scanf("%d", &n);
    printf("请输入初始密码: ");
    scanf("%d", &m);
    
    // 输入每个人的密码
    int* passwords = (int*)malloc(n * sizeof(int));
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