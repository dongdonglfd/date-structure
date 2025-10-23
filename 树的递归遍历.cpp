#include <iostream>
using namespace std;

// 二叉树节点结构
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// 递归前序遍历：根->左->右
void preorderTraversal(TreeNode* root) {
    if (root == nullptr) return;
    
    cout << root->val << " "; // 访问根节点
    preorderTraversal(root->left); // 递归遍历左子树
    preorderTraversal(root->right); // 递归遍历右子树
}

// 递归中序遍历：左->根->右
void inorderTraversal(TreeNode* root) {
    if (root == nullptr) return;
    
    inorderTraversal(root->left); // 递归遍历左子树
    cout << root->val << " "; // 访问根节点
    inorderTraversal(root->right); // 递归遍历右子树
}

// 递归后序遍历：左->右->根
void postorderTraversal(TreeNode* root) {
    if (root == nullptr) return;
    
    postorderTraversal(root->left); // 递归遍历左子树
    postorderTraversal(root->right); // 递归遍历右子树
    cout << root->val << " "; // 访问根节点
}

int main() {
    /*创建一棵示例二叉树
          1
         / \
        2   3
       / \ 
      4   5
    */ 
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    
    cout << "前序遍历: ";
    preorderTraversal(root);
    cout << endl;
    
    cout << "中序遍历: ";
    inorderTraversal(root);
    cout << endl;
    
    cout << "后序遍历: ";
    postorderTraversal(root);
    cout << endl;
    
    // 清理内存（实际应用中可能需要更复杂的删除逻辑）
    delete root->left->right;
    delete root->left->left;
    delete root->left;
    delete root->right;
    delete root;
    
    return 0;
}