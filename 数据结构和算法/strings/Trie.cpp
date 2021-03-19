// 单词查找树
// 单词前缀树
#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <typename V = int, int R = 256>
class Node
{
public:
    Node() : val(), next(R, nullptr) {}
    V val;
    vector<Node *> next;
};

template <typename V = int, int R = 256>
class TrieST
{
public:
    TrieST() : root(nullptr) {}
    typedef Node<V, R> NodeType;
    typedef Node<V, R> *iterator;
    // 查找整个单词
    NodeType *find(string key) { return find(root, key, 0); }
    // 从节点x开始查找key，d表示正在对比key中的第d个字符
    NodeType *find(NodeType *x, string key, int d);
    // 插入单词，值为v，返回根节点
    NodeType *insert(string key, V v) { return (root = insert(root, key, v, 0)); }
    NodeType *insert(NodeType *x, string key, V v, int d);
    int size() { return size(root); }
    int size(NodeType *x);
    // 返回所有储存的字符串
    vector<string> keys() { return keysWithPrefix(""); }
    // 返回以pre开头的字符串
    vector<string> keysWithPrefix(string pre);
    // 从节点x开始，查找以pre开头的字符串，储存在res中
    void collect(NodeType *x, string pre, vector<string> &res);

private:
    NodeType *root;
};

template <typename V, int R>
typename TrieST<V, R>::NodeType *TrieST<V, R>::find(NodeType *x, string key, int d)
{
    // x为空时，查找失败
    if (x == nullptr)
        return x;
    // 表示已经查找到了尾部，查找成功
    if (d == key.size())
        return x;
    char c = key[d];
    return find(x->next[c], key, d + 1);
}

template <typename V, int R>
typename TrieST<V, R>::NodeType *TrieST<V, R>::insert(NodeType *x, string key, V v, int d)
{
    // 如果x为空，需要创建新的节点
    if (x == nullptr)
        x = new NodeType();
    // 到了单词结尾，存入值
    if (d == key.size())
    {
        x->val = v;
        return x;
    }
    char c = key[d];
    x->next[c] = insert(x->next[c], key, v, d + 1);
    return x;
}

template <typename V, int R>
int TrieST<V, R>::size(NodeType *x)
{
    if (x == nullptr)
        return 0;
    int cnt = 0;
    if (x->val != V())
        ++cnt;
    for (int c = 0; c < R; ++c)
        cnt += size(x->next[c]);
    return cnt;
}

template <typename V, int R>
vector<string> TrieST<V, R>::keysWithPrefix(string pre)
{
    vector<string> res;
    collect(find(root, pre, 0), pre, res);
    return res;
}

template <typename V, int R>
void TrieST<V, R>::collect(NodeType *x, string pre, vector<string> &res)
{
    if (x == nullptr)
        return;
    if (x->val != V())
        res.push_back(pre);
    for (int c = 0; c < R; ++c)
        collect(x->next[c], pre + char(c), res);
}

int main()
{
    TrieST<int> t;
    t.insert("hello", 11);
    t.insert("i", 10);
    t.insert("hell", 100);
    t.insert("my", 23);
    t.insert("hello", 21);
    t.insert("whiat", 34);
    TrieST<int>::iterator iter = t.find("iwe");
    if (iter)
        cout << iter->val << endl;
    else
        cout << "not find" << endl;
    cout << t.size() << endl;
    vector<string> ss = t.keys();
    for (auto s : ss)
        cout << s << ' ';
}

/************一种更简介的代码**************************************************/

class Trie
{
private:
    bool is_string = false;
    Trie *next[26] = {nullptr};

public:
    Trie() {}

    void insert(const string &word) //插入单词
    {
        Trie *root = this;
        for (const auto &w : word)
        {
            if (root->next[w - 'a'] == nullptr)
                root->next[w - 'a'] = new Trie();
            root = root->next[w - 'a'];
        }
        root->is_string = true;
    }

    bool search(const string &word) //查找单词
    {
        Trie *root = this;
        for (const auto &w : word)
        {
            if (root->next[w - 'a'] == nullptr)
                return false;
            root = root->next[w - 'a'];
        }
        return root->is_string;
    }

    bool startsWith(const string &prefix) //查找前缀
    {
        Trie *root = this;
        for (const auto &p : prefix)
        {
            if (root->next[p - 'a'] == nullptr)
                return false;
            root = root->next[p - 'a'];
        }
        return true;
    }
};