//红黑树

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const bool RED = true;
const bool BLACK = false;

template <typename K, typename V>
class RB_tree;

template <typename K, typename V=K>
class Node
{
    friend class RB_tree<K, V>;
    Node(K k, V v, bool c) : key(k), val(v), color(c), parent(nullptr), left(nullptr), right(nullptr) {}

private:
    K key;
    V val;
    bool color;
    Node *parent, *left, *right;
};

template <typename K, typename V=K>
class RB_tree
{
    typedef Node<K, V> Node_type;

private:
    Node_type *root = nil;
    static Node_type *nil;

public:
    //和二叉搜索树一样的成员函数
    Node_type *tree_minimum(Node_type *);
    Node_type *tree_maximum(Node_type *);
    Node_type *search(K k) { return search(root, k); }
    Node_type *search(Node_type *, K);

    //RB_Tree特有的函数
    void print_order();
    void left_rotate(Node_type *);
    void right_rotate(Node_type *);
    void insert(K k) { return insert(k, k); }
    void insert(K k, V v) { return insert(new Node_type(k, v, RED)); }
    void insert(Node_type *);
    void insert_fixup(Node_type *);
    void transplant(Node_type *, Node_type *);
    void erase(K k);
    void erase(Node_type *);
    void erase_fixup(Node_type *);
};

template <typename K, typename V>
typename RB_tree<K, V>::Node_type *RB_tree<K, V>::nil = new Node_type(K(), V(), BLACK);

template <typename K, typename V>
typename RB_tree<K, V>::Node_type *RB_tree<K, V>::tree_minimum(Node_type *x)
{
    while (x->left != nil)
        x = x->left;
    return x;
}

template <typename K, typename V>
typename RB_tree<K, V>::Node_type *RB_tree<K, V>::tree_maximum(Node_type *x)
{
    while (x->right != nil)
        x = x->right;
    return x;
}

template <typename K, typename V>
typename RB_tree<K, V>::Node_type *RB_tree<K, V>::search(Node_type *x, K k)
{
    if (x == nil || k == x->key)
        return x;
    if (k < x->key)
        return search(x->left, k);
    else
        return search(x->right, k);
}

//强化版输出，搜一下leetcode对称输出树的题目，第655题
template <typename K, typename V>
void RB_tree<K, V>::print_order()
{
    if (root == nil)
        return;
    queue<Node_type *> q;
    q.push(root);
    while (!q.empty())
    {
        int n = q.size();
        for (int i = 0; i < n; ++i)
        {
            Node_type *x = q.front();
            q.pop();
            if (x != nil)
            {
                cout << x->val << ' ' << (x->color ? "RED" : "BLACK") << "  /  ";
                q.push(x->left);
                q.push(x->right);
            }
            else
            {
                cout << "   NIL   "
                     << "  /  ";
            }
        }
        cout << endl;
    }
}

template <typename K, typename V>
void RB_tree<K, V>::left_rotate(Node_type *x)
{
    Node_type *y = x->right;
    x->right = y->left;
    if (y->left != nil)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == nil)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

template <typename K, typename V>
void RB_tree<K, V>::right_rotate(Node_type *x)
{
    Node_type *y = x->left;
    x->left = y->right;
    if (y->right != nil)
        y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == nil)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->right = x;
    x->parent = y;
}

template <typename K, typename V>
void RB_tree<K, V>::insert(Node_type *z)
{
    Node_type *x = root, *y = nil;
    while (x != nil)
    {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if (y == nil)
        root = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;
    z->left = nil;
    z->right = nil;
    insert_fixup(z);
}

template <typename K, typename V>
void RB_tree<K, V>::insert_fixup(Node_type *z)
{
    while (z->parent->color == RED)
    {
        if (z->parent == z->parent->parent->left)
        {
            Node_type *y = z->parent->parent->right; //叔结点
            if (y->color == RED)
            {
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                y->color = BLACK;
                z = z->parent->parent;
            }
            else if (z == z->parent->right)
            {
                z = z->parent;
                left_rotate(z);
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                right_rotate(z->parent->parent);
            }
            else
            {
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                right_rotate(z->parent->parent);
            }
        }
        else
        {
            Node_type *y = z->parent->parent->left; //叔结点
            if (y->color == RED)
            {
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                y->color = BLACK;
                z = z->parent->parent;
            }
            else if (z == z->parent->left)
            {
                z = z->parent;
                right_rotate(z);
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                left_rotate(z->parent->parent);
            }
            else
            {
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                left_rotate(z->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

template <typename K, typename V>
void RB_tree<K, V>::transplant(Node_type *u, Node_type *v) //用结点v替代结点u
{
    if (u->parent == nil)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    v->parent = u->parent;
}

template <typename K, typename V>
void RB_tree<K, V>::erase(K k)
{
    Node_type *x = search(k);
    if (x == nil)
        return;
    else
        erase(x);
}

template <typename K, typename V>
void RB_tree<K, V>::erase(Node_type *z)
{
    Node_type *y = z, *x;
    bool y_original_color = y->color;
    //z只有一个子结点的情况，y指向被删除的结点，x为y的后继
    if (z->left == nil)
    {
        x = z->right;
        transplant(z, z->right);
    }
    else if (z->right == nil)
    {
        x = z->left;
        transplant(z, z->left);
    }
    //z有两个子结点的情况，y是z的后继，x是y的右孩子，y是没有左孩子的
    else
    {
        y = tree_minimum(z->right);
        x = y->right;
        y_original_color = y->color;
        if (y->parent == z)
            x->parent = y; //当x是nil，需要此语句
        else
        {
            transplant(y, x); //用x替代y
            y->right = z->right;
            y->right->parent = y;
        }
        //用y代替z
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if (y_original_color == BLACK)
        erase_fixup(x);
}

template <typename K, typename V>
void RB_tree<K, V>::erase_fixup(Node_type *x)
{
    while (x != root && x->color == BLACK)
    {
        if (x == x->parent->left)
        {
            Node_type *w = x->parent->right;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                left_rotate(x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
                continue;
            }
            else
            {
                if (w->right->color == BLACK)
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    right_rotate(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                left_rotate(x->parent);
                x = root; //只是用于将循环终止
            }
        }
        else
        {
            Node_type *w = x->parent->left;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                right_rotate(x->parent);
                w = x->parent->left;
            }
            if (w->left->color == BLACK && w->right->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
                continue;
            }
            else
            {
                if (w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    left_rotate(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                right_rotate(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

int main()
{
    RB_tree<int> rb;
    vector<int> data{10, 7, 8, 15, 5, 6, 11, 13, 12};
    for (auto i : data)
    {
        rb.insert(i);
        rb.print_order();
        cout << "---------" << endl;
    }
    for (auto i : data)
    {
        rb.erase(i);
        rb.print_order();
        cout << "---------" << endl;
    }
}