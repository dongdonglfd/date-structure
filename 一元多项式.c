#include <stdio.h>
#include <stdlib.h>

// 多项式节点结构
typedef struct PolyNode {
    float coef;         // 系数
    int exp;            // 指数
    struct PolyNode *next;
} PolyNode, *Polynomial;

// 初始化多项式（创建头节点）
void InitPolynomial(Polynomial *P) {
    *P = (Polynomial)malloc(sizeof(PolyNode));
    if (*P == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    (*P)->next = NULL;
}

// 插入节点（按指数降序）
void InsertNode(Polynomial P, float coef, int exp) {
    if (coef == 0) return; // 系数为0不插入
    
    PolyNode *prev = P;
    PolyNode *curr = P->next;
    
    // 查找插入位置
    while (curr != NULL && curr->exp > exp) {
        prev = curr;
        curr = curr->next;
    }
    
    // 指数相同则合并
    if (curr != NULL && curr->exp == exp) {
        curr->coef += coef;
        if (curr->coef == 0) { // 合并后系数为0则删除
            prev->next = curr->next;
            PolyNode *tmp=curr;
            free(tmp);
        }
    } else { // 创建新节点
        PolyNode *newNode = (PolyNode*)malloc(sizeof(PolyNode));
        if (newNode == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        newNode->coef = coef;
        newNode->exp = exp;
        newNode->next = curr;
        prev->next = newNode;
    }
}

// 创建多项式
void CreatePolynomial(Polynomial P) {
    float coef;
    int exp;
    printf("输入系数和指数（输入0 0结束）: ");
    while (scanf("%f %d", &coef, &exp) == 2) {
        if (coef == 0 && exp == 0) break;
        InsertNode(P, coef, exp);
    }
}

// 打印多项式
void PrintPolynomial(Polynomial P) {
    PolyNode *node = P->next;
    if (node == NULL) {
        printf("0\n");
        return;
    }
    
    while (node != NULL) {
        if (node->coef > 0 && node != P->next) printf(" + ");
        else if (node->coef < 0) printf(" - ");
        
        float abs_coef = (node->coef < 0) ? -node->coef : node->coef;
        
        if (abs_coef != 1 || node->exp == 0) 
            printf("%.1f", abs_coef);
        
        if (node->exp > 0) printf("x");
        if (node->exp > 1) printf("^%d", node->exp);
        
        node = node->next;
    }
    printf("\n");
}

// 多项式相加
void AddPolynomial(Polynomial A, Polynomial B, Polynomial C) {
    PolyNode *p = A->next;
    PolyNode *q = B->next;
    
    while (p != NULL && q != NULL) {
        if (p->exp > q->exp) {
            InsertNode(C, p->coef, p->exp);
            p = p->next;
        } else if (p->exp < q->exp) {
            InsertNode(C, q->coef, q->exp);
            q = q->next;
        } else {
            float sum = p->coef + q->coef;
            if (sum != 0) InsertNode(C, sum, p->exp);
            p = p->next;
            q = q->next;
        }
    }
    
    while (p != NULL) {
        InsertNode(C, p->coef, p->exp);
        p = p->next;
    }
    
    while (q != NULL) {
        InsertNode(C, q->coef, q->exp);
        q = q->next;
    }
}

// 多项式相减
void SubtractPolynomial(Polynomial A, Polynomial B, Polynomial C) {
    PolyNode *p = A->next;
    PolyNode *q = B->next;
    
    while (p != NULL && q != NULL) {
        if (p->exp > q->exp) {
            InsertNode(C, p->coef, p->exp);
            p = p->next;
        } else if (p->exp < q->exp) {
            InsertNode(C, -q->coef, q->exp);
            q = q->next;
        } else {
            float diff = p->coef - q->coef;
            if (diff != 0) InsertNode(C, diff, p->exp);
            p = p->next;
            q = q->next;
        }
    }
    
    while (p != NULL) {
        InsertNode(C, p->coef, p->exp);
        p = p->next;
    }
    
    while (q != NULL) {
        InsertNode(C, -q->coef, q->exp);
        q = q->next;
    }
}

// 多项式求导
void DerivativePolynomial(Polynomial P, Polynomial C) {
    PolyNode *curr = P->next;
    while (curr != NULL) {
        if (curr->exp != 0) {
            float new_coef = curr->coef * curr->exp;
            int new_exp = curr->exp - 1;
            InsertNode(C, new_coef, new_exp);
        }
        curr = curr->next;
    }
}

// 多项式相乘
void MultiplyPolynomial(Polynomial A, Polynomial B, Polynomial C) {
    PolyNode *p = A->next;
    while (p != NULL) {
        PolyNode *q = B->next;
        while (q != NULL) {
            float new_coef = p->coef * q->coef;
            int new_exp = p->exp + q->exp;
            InsertNode(C, new_coef, new_exp);
            q = q->next;
        }
        p = p->next;
    }
}

// 释放多项式内存
void FreePolynomial(Polynomial P) {
    PolyNode *curr = P->next;
    while (curr != NULL) {
        PolyNode *temp = curr;
        curr = curr->next;
        free(temp);
    }
    free(P);
}

int main() {
    Polynomial A, B, C;
    
    // 初始化多项式
    InitPolynomial(&A);
    InitPolynomial(&B);
    InitPolynomial(&C);
    
    printf("创建多项式A:\n");
    CreatePolynomial(A);
    printf("多项式A: ");
    PrintPolynomial(A);
    
    printf("创建多项式B:\n");
    CreatePolynomial(B);
    printf("多项式B: ");
    PrintPolynomial(B);
    
    // 相加
    AddPolynomial(A, B, C);
    printf("A + B = ");
    PrintPolynomial(C);
    FreePolynomial(C);
    
    // 相减
    InitPolynomial(&C);
    SubtractPolynomial(A, B, C);
    printf("A - B = ");
    PrintPolynomial(C);
    FreePolynomial(C);
    
    // 求导
    InitPolynomial(&C);
    DerivativePolynomial(A, C);
    printf("A的导数 = ");
    PrintPolynomial(C);
    FreePolynomial(C);
    
    // 相乘
    InitPolynomial(&C);
    MultiplyPolynomial(A, B, C);
    printf("A * B = ");
    PrintPolynomial(C);
    FreePolynomial(C);
    
    // 释放内存
    FreePolynomial(A);
    FreePolynomial(B);
    
    return 0;
}