#include <iostream>
#include <sstream>
#include <bitset>
#include <string>
#include <unordered_map>
#include <queue>
#include <vector>

using namespace std;

class Node
{
public:
    Node(char c, int f, Node *l = nullptr, Node *r = nullptr) : ch(c), freq(f), left(l), right(r) {}
    bool isLeaf() { return left == nullptr && right == nullptr; }
    char ch;
    int freq;
    Node *left, *right;
};

auto comNode = [](Node *const &lhs, Node *const &rhs) {
    return lhs->freq > rhs->freq;
};

class Huffman
{
public:
    Huffman(string s) : data(s) {}
    Node *buildTrie(unordered_map<char, int>);
    void compress();
    unordered_map<char, string> buildCode(Node *);
    void buildCode(Node *, string);
    void writeTrie(Node *);
    void writestring();
    Node *readTrie(istringstream &);
    string expand();
    string Trie() { return trie; }
    string Code() { return code; }
    unordered_map<char, string> stmap() { return st; }

private:
    string data;
    string trie;
    string code;
    unordered_map<char, string> st;
};

Node *Huffman::buildTrie(unordered_map<char, int> fm)
{
    priority_queue<Node *, vector<Node *>, decltype(comNode)> pq(comNode);
    auto be = fm.begin(), en = fm.end();
    for (; be != en; ++be)
        pq.push(new Node(be->first, be->second));
    while (pq.size() > 1)
    {
        Node *x = pq.top();
        pq.pop();
        Node *y = pq.top();
        pq.pop();
        Node *parent = new Node('\0', x->freq + y->freq, x, y);
        pq.push(parent);
    }
    return pq.top();
}

unordered_map<char, string> Huffman::buildCode(Node *root)
{
    buildCode(root, "");
    return st;
}

void Huffman::buildCode(Node *x, string s)
{
    if (x->isLeaf())
    {
        st[x->ch] = s;
        return;
    }
    buildCode(x->left, s + '0');
    buildCode(x->right, s + '1');
}

void Huffman::writeTrie(Node *x)
{
    if (x->isLeaf())
    {
        trie += "1";
        trie += bitset<8>(x->ch).to_string();
        return;
    }
    trie += "0";
    writeTrie(x->left);
    writeTrie(x->right);
}

void Huffman::writestring()
{
    code = trie;
    code += bitset<32>(data.size()).to_string();
    for (auto c : data)
        code += st[c];
}

Node *Huffman::readTrie(istringstream &in)
{
    bitset<1> bit;
    in >> bit;
    if (bit.to_ulong())
    {
        bitset<8> val;
        in >> val;
        return new Node(char(val.to_ulong()), 0);
    }
    return new Node('\0', 0, readTrie(in), readTrie(in));
}

void Huffman::compress()
{
    unordered_map<char, int> freq;
    for (char c : data)
        ++freq[c];
    Node *root = buildTrie(freq);
    unordered_map<char, string> st;
    buildCode(root, "");
    writeTrie(root);
    writestring();
}

string Huffman::expand()
{
    string res;
    istringstream in(code);
    Node *root = readTrie(in);
    bitset<32> length;
    in >> length;
    int N = length.to_ulong();
    for (int i = 0; i < N; ++i)
    {
        bitset<1> bit;
        Node *x = root;
        while (!x->isLeaf())
        {
            in >> bit;
            if (bit.to_ulong())
                x = x->right;
            else
                x = x->left;
        }
        res += x->ch;
    }
    return res;
}

int main()
{
    //Huffman h("ABRACADABRA!");
    //Huffman h("it was the best of times it was the worst of times");
    Huffman h("hello world! ni hao! welcome to china! my name is jane! nice to meet you!");
    h.compress();
    string s = h.Code(), t = h.Trie();
    cout << t.size() << '\n'
         << t << endl;
    cout << s.size() << endl;
    cout << s << endl;
    auto sm = h.stmap();
    for (auto p : sm)
        cout << p.first << "   " << p.second << endl;
    string l = h.expand();
    cout << l << endl;
}