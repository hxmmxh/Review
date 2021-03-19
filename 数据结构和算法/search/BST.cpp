//二叉查找树

#include <iostream>

template <typename, typename>
class BST;

template <typename K, typename V>
class Node
{
public:
    friend class BST<K, V>;
    Node(K k, V v, int n) : key(k), val(v), N(n), left(nullptr), right(nullptr) {}

private:
    int N;
    K key;
    V val;
    Node *left, *right;
};

template <typename K, typename V>
class BST
{
public:
    typedef Node<K, V> NodeType;
    int size() const { return size(root); }
    int size(NodeType *x) const
    {
        if (x == nullptr)
            return 0;
        else
            return x.N;
    }
    NodeType *find(Key key) const { return find(root, key); }
    NodeType *find(NodeType *, K) const;
    NodeType *insert(K key, V value)
    {
        root = insert(root, key, value);
        return root;
    }
    NodeType *insert(NodeType *, K, V);

private:
    NodeType *root;
};

template <typename K, typename V>
typename BST<K, V>::NodeType *BST<K, V>::find(NodeType *x, K key) const
{
    if (x == nullptr)
        return nullptr;
    if (key == x->key)
        return x;
    else if (key > x->key)
        return get(x->left, key);
    else
        return get(x->right, key);
}

template <typename K, typename V>
typename BST<K, V>::NodeType *BST<K, V>::insert(NodeType *x, K key, V value)
{
    if (x == nullptr)
        return new NodeType(key, val, 1);
    if (key == x->key)
        x->val = val;
    else if (key > x->key)
        x->right = insert(x->right, key, val);
    else
        x->left = insert(x->left, key, val);
    x->N = x->left->N + x->right->N + 1;
    return x;
}