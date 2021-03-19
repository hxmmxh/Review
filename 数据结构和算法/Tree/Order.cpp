//层序遍历
#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/*********************前序遍历*******************************/
// 用栈实现，迭代
vector<int> preorderTraversal(TreeNode *root)
{
    vector<int> res;
    stack<TreeNode *> stk;
    while (root != nullptr || !stk.empty())
    {
        while (root != nullptr)
        {
            res.emplace_back(root->val);
            stk.emplace(root);
            root = root->left;
        }
        root = stk.top();
        stk.pop();
        root = root->right;
    }
    return res;
}
/*********************中序遍历*******************************/
// 中序遍历
// 用栈实现，迭代
vector<int> inorderTraversal1(TreeNode *root)
{
    vector<int> res;
    stack<TreeNode *> stk;
    while (root != nullptr || !stk.empty())
    {
        while (root != nullptr)
        {
            stk.emplace(root);
            root = root->left;
        }
        root = stk.top();
        stk.pop();
        res.emplace_back(root->val);
        root = root->right;
    }
    return res;
}

// 递归实现
void inorder(TreeNode *root, vector<int> &res)
{
    if (!root)
    {
        return;
    }
    inorder(root->left, res);
    res.push_back(root->val);
    inorder(root->right, res);
}
vector<int> inorderTraversal2(TreeNode *root)
{
    vector<int> res;
    inorder(root, res);
    return res;
}

/*********************后序遍历*******************************/
// 后序遍历
// 用栈实现
vector<int> postorderTraversal1(TreeNode *root)
{
    vector<int> res;
    stack<TreeNode *> stk;
    while (root != nullptr || !stk.empty())
    {
        while (root != nullptr)
        {
            stk.emplace(root);
            root = root->left;
        }
        root = stk.top();
        stk.pop();
        res.emplace_back(root->val);
        root = root->right;
    }
    return res;
}

/******************** 层序遍历******************************************************/
// 迭代实现
vector<vector<int>> levelOrder(TreeNode *root)
{
    vector<vector<int>> res;
    if (!root)
        return res;
    queue<TreeNode *> aux;
    aux.push(root);
    while (!aux.empty())
    {
        int n = aux.size();
        vector<int> tem;
        for (int i = 0; i < n; ++i)
        {
            TreeNode *p = aux.front();
            aux.pop();
            tem.emplace_back(p->val);
            if (p->left)
                aux.push(p->left);
            if (p->right)
                aux.push(p->right);
        }
        res.push_back(tem);
    }
    return res;
}

// 递归实现
vector<vector<int>> levelOrder_1(TreeNode *root)
{
    vector<vector<int>> res;
    levelorder(root, 0, res);
    return res;
}
void levelorder(TreeNode *node, int level, vector<vector<int>> &res)
{
    if (!node)
        return;
    if (res.size() == level)
        res.push_back({});
    res[level].push_back(node->val);
    if (node->left)
        levelorder(node->left, level + 1, res);
    if (node->right)
        levelorder(node->right, level + 1, res);
}

{
    int m = [](int x) { return [](int y) { return y * 2; }(x) + 6; }(5);
    std::cout << "m:" << m << std::endl;//输出m:16

    std::cout<< "n:" << [](int x, int y) { return x + y; }(5, 4) << std::endl; //输出n:9

    auto gFunc = [](int x) -> function<int(int)> { return [=](int y) { return x + y; }; };
    auto lFunc = gFunc(4);
    std::cout << lFunc(5) << std::endl;

    auto hFunc = [](const function<int(int)> &f, int z) { return f(z) + 1; };
    auto a = hFunc(gFunc(7), 8);

    int a = 111, b = 222;
    auto func = [=, &b]() mutable { a = 22; b = 333; std::cout << "a:" << a << " b:" << b << std::endl; };

    func();
    std::cout << "a:" << a << " b:" << b << std::endl;

    a = 333;
    auto func2 = [=, &a] { a = 444; std::cout << "a:" << a << " b:" << b << std::endl; };
    func2();

    auto func3 = [](int x) -> function<int(int)> { return [=](int y) { return x + y; }; };
    　　
　　　　 std::function<void(int x)> f_display_42 = [](int x) 
    {
         print_num(x);
         
    };
    f_display_42(44);
    　　
}