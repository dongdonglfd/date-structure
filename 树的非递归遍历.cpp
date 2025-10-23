#include <iostream>
#include <stack>
#include <queue>
using namespace std;

// 二叉树节点结构
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// 非递归前序遍历
void preorderTraversalIterative(TreeNode* root) {
    if (root == nullptr) return;
    
    stack<TreeNode*> st;
    st.push(root);
    
    while (!st.empty()) {
        TreeNode* node = st.top();
        st.pop();
        cout << node->val << " ";
        
        // 先右后左，保证左子树先被访问
        if (node->right) st.push(node->right);
        if (node->left) st.push(node->left);
    }
}

// 非递归中序遍历
void inorderTraversalIterative(TreeNode* root) {
    stack<TreeNode*> st;
    TreeNode* curr = root;
    
    while (curr != nullptr || !st.empty()) {
        // 遍历到最左节点
        while (curr != nullptr) {
            st.push(curr);
            curr = curr->left;
        }
        
        curr = st.top();
        st.pop();
        cout << curr->val << " ";
        
        // 转向右子树
        curr = curr->right;
    }
}

// 非递归后序遍历
void postorderTraversalIterative(TreeNode* root) {
    if (root == nullptr) return;
    
    stack<TreeNode*> st;
    TreeNode* curr = root;
    TreeNode* lastVisited = nullptr;
    
    while (curr != nullptr || !st.empty()) {
        // 遍历到最左节点
        while (curr != nullptr) {
            st.push(curr);
            curr = curr->left;
        }
        
        TreeNode* topNode = st.top();
        
        // 如果右子树存在且未被访问，则转向右子树
        if (topNode->right != nullptr && topNode->right != lastVisited) {
            curr = topNode->right;
        } else {
            // 访问节点
            cout << topNode->val << " ";
            lastVisited = topNode;
            st.pop();
        }
    }
}

// 非递归层次遍历
void levelOrderTraversal(TreeNode* root) {
    if (root == nullptr) return;
    
    queue<TreeNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        size_t levelSize = q.size();
        for (size_t i = 0; i < levelSize; i++) {
            TreeNode* node = q.front();
            q.pop();
            cout << node->val << " ";
            
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        cout << endl; // 每层换行
    }
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
    preorderTraversalIterative(root);
    cout << endl;
    
    cout << "中序遍历: ";
    inorderTraversalIterative(root);
    cout << endl;
    
    cout << "后序遍历: ";
    postorderTraversalIterative(root);
    cout << endl;
    
    cout << "层次遍历:\n";
    levelOrderTraversal(root);
    
    // 清理内存
    delete root->left->right;
    delete root->left->left;
    delete root->left;
    delete root->right;
    delete root;
    
    return 0;
}