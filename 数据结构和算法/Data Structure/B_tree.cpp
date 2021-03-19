#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <queue>

//#define DEBUG

using namespace std;

//模拟硬盘读取，统计一共调用了多少次这两个函数
void Disk_read()
{
    static int nr = 0;
    ++nr;
#ifdef DEBUG
    cout << "Disk read" << nr << " times" << endl;
#endif
}

void Disk_write()
{
    static int nw = 0;
    ++nw;
#ifdef DEBUG
    cout << "Disk write " << nw << " times" << endl;
#endif
}

template <typename K, int T>
class B_tree;

template <typename K, int T = 2> //T表示B树的度数，这里默认设置为3
class Node
{
    friend class B_tree<K, T>;

public:
    Node(int _n = 0, bool b = true) : n(_n), isleaf(b), keys(2 * T - 1), children(2 * T) {}

private:
    int n;
    vector<K> keys;          //下标取值从0-n-1
    vector<Node *> children; //下标取值从0-n
    bool isleaf;
};

template <typename K, int T = 2>
class B_tree
{
    typedef Node<K, T> Node_type;

public:
    B_tree() { B_tree_create(); }
    void print_tree();
    void B_tree_create();
    pair<Node_type *, int> B_tree_search(Node_type *, K k);
    void B_tree_insert(K);
    void B_tree_split_child(Node_type *, int);
    void B_tree_insert_nonfull(Node_type *, K);

private:
    Node_type *root;
};

template <typename K, int T>
void B_tree<K, T>::print_tree()
{
    if (!root)
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
            cout << "[ ";
            for (int j = 0; j < x->n; ++j)
            {
                cout << x->keys[j] << ' ';
            }
            cout << "] ";
            if (!x->isleaf)
            {
                for (int j = 0; j <= x->n; ++j)
                    q.push(x->children[j]);
            }
        }
        cout << '\n'
             << "-----------------------" << '\n';
    }
}

template <typename K, int T>
pair<Node<K, T> *, int> B_tree<K, T>::B_tree_search(Node_type *x, K k)
{
    int i = 0;
    while (i < x->n && k > x->keys[i])
        ++i;
    if (i < x->n && k == x->keys[i]) //首先确保i的取值不会溢出
        return {x, i};
    else if (x->isleaf)
        return {nullptr, 0};
    else
    {
        Disk_read();
        return B_tree_search(x->children[i], k);
    }
}

template <typename K, int T>
void B_tree<K, T>::B_tree_create()
{
    Node_type *x = new Node_type();
    Disk_write();
    root = x;
}

//x的i号子结点是满的，x本身不满
template <typename K, int T>
void B_tree<K, T>::B_tree_split_child(Node_type *x, int i)
{
    Node_type *z = new Node_type();
    Node_type *y = x->children[i];
    z->isleaf = y->isleaf;
    z->n = T - 1; //满的结点的key共有2T-1个，分离一个满结点时，得到两个T-1规模的子节点，正中间的key去该结点的父结点
    for (int j = 0; j < T - 1; ++j)
        z->keys[j] = y->keys[j + T];
    if (!y->isleaf)
        for (int j = 0; j < T; ++j) //children共有2T个，每个分离出的结点分到T个
            z->children[j] = y->children[j + T];
    y->n = T - 1;
    for (int j = x->n; j >= i + 1; --j) //在x中移出个空位放置y中上来的中间key
        x->children[j + 1] = x->children[j];
    x->children[i + 1] = z;
    for (int j = x->n - 1; j >= i; --j)
        x->keys[j + 1] = x->keys[j];
    x->keys[i] = y->keys[T - 1];
    x->n += 1;
    Disk_write();
    Disk_write();
    Disk_write();
}

template <typename K, int T>
void B_tree<K, T>::B_tree_insert(K k)
{
    Node_type *r = root;
    if (r->n == 2 * T - 1)
    {
        Node_type *s = new Node_type();
        root = s;
        s->isleaf = false;
        s->n = 0;
        s->children[0] = r;
        B_tree_split_child(s, 0);
        B_tree_insert_nonfull(s, k);
    }
    else
        B_tree_insert_nonfull(r, k);
}

template <typename K, int T>
void B_tree<K, T>::B_tree_insert_nonfull(Node_type *x, K k)
{
    int i = x->n - 1;
    if (x->isleaf)
    {
        while (i >= 0 && k < x->keys[i])
        {
            x->keys[i + 1] = x->keys[i];
            --i;
        }
        x->keys[i + 1] = k;
        x->n += 1;
        Disk_write();
    }
    else
    {
        while (i >= 0 && k < x->keys[i])
            --i;
        ++i;
        Disk_read();
        if (x->children[i]->n == 2 * T - 1)
        {
            B_tree_split_child(x, i);
            if (k > x->keys[i])
                ++i;
        }
        B_tree_insert_nonfull(x->children[i], k);
    }
}

int main()
{
    string s = "FSQKCLHTVWMRNPABXYDZE";
    B_tree<char> bt;
    for (char c : s)
        bt.B_tree_insert(c);
    bt.print_tree();
}