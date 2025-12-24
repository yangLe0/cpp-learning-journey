//
//  treetest.cpp
//  test
//
//  Created by 天塌不惊 on 2025/12/24.
//

#include <stdio.h>
#include <iostream>
#include <queue>
#include <stack>
using namespace std;

// 定义二叉树节点结构
struct TreeNode {
    int val;                // 节点存储的数据
    TreeNode* left;         // 左子节点指针
    TreeNode* right;        // 右子节点指针
    // 构造函数：初始化节点
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
//DFS
// 1.1 前序遍历：根节点 → 左子树 → 右子树
void preOrder(TreeNode* root) {
    if (root == nullptr) return;  // 递归终止条件：空节点
    cout << root->val << " ";     // 访问根节点
    preOrder(root->left);         // 遍历左子树
    preOrder(root->right);        // 遍历右子树
}

// 1.2 中序遍历：左子树 → 根节点 → 右子树（二叉搜索树的中序是升序）
void inOrder(TreeNode* root) {
    if (root == nullptr) return;
    inOrder(root->left);
    cout << root->val << " ";
    inOrder(root->right);
}

// 1.3 后序遍历：左子树 → 右子树 → 根节点（常用于释放节点内存）
void postOrder(TreeNode* root) {
    if (root == nullptr) return;
    postOrder(root->left);
    postOrder(root->right);
    cout << root->val << " ";
}
//迭代版遍历：递归遍历易栈溢出，迭代版用栈（DFS）/ 队列（BFS）实现
void preOrderIter(TreeNode* root) {
    if (root == nullptr) return;
    stack<TreeNode*> st;
    st.push(root);
    while (!st.empty()) {
        TreeNode* curr = st.top();
        st.pop();
        cout << curr->val << " ";
        // 先压右子节点（栈后进先出，保证左子节点先访问）
        if (curr->right) st.push(curr->right);
        if (curr->left) st.push(curr->left);
    }
}
// 迭代版中序遍历
/*
 先沿着左子树一直走，把所有左节点依次压入栈，直到左子节点为空；
 弹出栈顶节点（此时无左子节点），访问该节点；
 把指针指向该节点的右子节点，重复步骤 1-2。
 curr 指针负责遍历左子树，stack 负责记录 “待访问的根节点”；
 内层 while 循环是 “找最左” 的过程，比如树 5->3->2，会先把 5、3、2 依次压栈，直到 2 的左子节点为空；
 弹出 2 后，curr 指向 2 的右子节点（空），接着弹出 3，curr 指向 3 的右子节点，以此类推。
 */
void inOrderIter(TreeNode* root) {
    if (root == nullptr) return;
    stack<TreeNode*> st;  // 存储待访问的节点
    TreeNode* curr = root; // 遍历指针，初始指向根节点

    // 循环条件：指针非空 或 栈非空
    while (curr != nullptr || !st.empty()) {
        // 步骤1：遍历到最左子节点，沿途压栈
        while (curr != nullptr) {
            st.push(curr);
            curr = curr->left;
        }

        // 步骤2：弹出栈顶（最左节点），访问
        curr = st.top();
        st.pop();
        cout << curr->val << " ";

        // 步骤3：处理右子节点
        curr = curr->right;
    }
}
// 迭代版后序遍历（标记法）
void postOrderIter(TreeNode* root) {
    if (root == nullptr) return;
    // 栈中存储 pair：<节点指针，是否已访问>
    stack<pair<TreeNode*, bool>> st;
    st.push({root, false});

    while (!st.empty()) {
        auto [curr, visited] = st.top();
        st.pop();

        if (visited) {
            // 已访问：直接输出
            cout << curr->val << " ";
        } else {
            // 未访问：先压当前节点（标记为已访问），再压右、左子节点（未访问）
            st.push({curr, true});
            if (curr->right != nullptr) {
                st.push({curr->right, false});
            }
            if (curr->left != nullptr) {
                st.push({curr->left, false});
            }
        }
    }
}
// 迭代版后序遍历（双栈法）
void postOrderIter2(TreeNode* root) {
    if (root == nullptr) return;
    stack<TreeNode*> st1, st2;
    st1.push(root);

    // 栈1处理：根 → 右 → 左
    while (!st1.empty()) {
        TreeNode* curr = st1.top();
        st1.pop();
        st2.push(curr); // 压入栈2

        // 先压左子节点（栈1后进先出，保证右子节点先处理）
        if (curr->left != nullptr) st1.push(curr->left);
        if (curr->right != nullptr) st1.push(curr->right);
    }

    // 栈2弹出：左 → 右 → 根
    while (!st2.empty()) {
        cout << st2.top()->val << " ";
        st2.pop();
    }
}
//BFS
void levelOrder(TreeNode* root) {
    if (root == nullptr) return;
    queue<TreeNode*> q;  // 队列存储待访问的节点
    q.push(root);        // 根节点入队

    while (!q.empty()) {
        TreeNode* curr = q.front();  // 取出队首节点
        q.pop();
        cout << curr->val << " ";    // 访问当前节点

        // 左子节点非空则入队
        if (curr->left != nullptr) q.push(curr->left);
        // 右子节点非空则入队
        if (curr->right != nullptr) q.push(curr->right);
    }
}
// 2.1 插入节点（递归）
TreeNode* insertBST(TreeNode* root, int val) {
    // 空节点处插入新节点
    if (root == nullptr) return new TreeNode(val);
    // 小于根节点：插入左子树
    if (val < root->val) {
        root->left = insertBST(root->left, val);
    }
    // 大于根节点：插入右子树（等于时一般不插入，避免重复）
    else if (val > root->val) {
        root->right = insertBST(root->right, val);
    }
    return root;  // 返回根节点（保持树结构）
}
// 2.2 查找节点（递归）
TreeNode* searchBST(TreeNode* root, int val) {
    // 空节点或找到目标节点：返回结果
    if (root == nullptr || root->val == val) return root;
    // 小于根节点：查找左子树
    if (val < root->val) {
        return searchBST(root->left, val);
    }
    // 大于根节点：查找右子树
    return searchBST(root->right, val);
}
void deleteTree(TreeNode* root) {
    if (root == nullptr) return;
    deleteTree(root->left);   // 释放左子树
    deleteTree(root->right);  // 释放右子树
    delete root;              // 释放当前节点
    root = nullptr;           // 避免野指针
}
int main() {
    // 构建二叉搜索树
    TreeNode* root = nullptr;
    root = insertBST(root, 5);
    insertBST(root, 3);
    insertBST(root, 7);
    insertBST(root, 2);
    insertBST(root, 4);

    // 遍历测试
    cout << "前序遍历：";
    preOrder(root);  // 输出：5 3 2 4 7
    cout << endl;

    cout << "中序遍历：";
    inOrder(root);   // 输出：2 3 4 5 7（BST中序升序）
    cout << endl;
    cout << "中序遍历：";
    inOrderIter(root);   // 输出：2 3 4 5 7（BST中序升序）
    cout << endl;
    
    cout << "后序遍历：";
    postOrder(root);   // 输出：2 3 4 5 7（BST中序升序）
    cout << endl;
    cout << "后序遍历：";
    postOrderIter(root);   // 输出：2 3 4 5 7（BST中序升序）
    cout << endl;
    cout << "后序遍历：";
    postOrderIter2(root);   // 输出：2 3 4 5 7（BST中序升序）
    cout << endl;

    cout << "层序遍历：";
    levelOrder(root);// 输出：5 3 7 2 4
    cout << endl;

    // 查找测试
    TreeNode* found = searchBST(root, 3);
    if (found) cout << "找到节点：" << found->val << endl;  // 输出：找到节点：3

    // 释放内存
    deleteTree(root);
    return 0;
}
