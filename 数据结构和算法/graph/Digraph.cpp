#include "graph_base.h"
#include "Digraph_app.h"
#include <fstream>
#include <iostream>

void print(vector<int> a)
{
    for (int i : a)
        cout << i << ' ';
    cout << endl;
}

int main()
{
    fstream f("data/tinyDG.txt");
    Digraph g(f);
    string s = g.tostring();
    cout << s << endl;
    cout << g.Direverse().tostring();
    DirectedCycle cycle(g);
    if (cycle.hasCycle())
        cout << "has cycle" << endl;
    else
        cout << "no cycle" << endl;
    print(cycle.cycle());
    DepthFirstOrder dfsorder(g);
    vector<int> pre = dfsorder.pre();
    vector<int> post = dfsorder.post();
    vector<int> reversepost = dfsorder.reversePost();
    print(pre);
    print(post);
    print(reversepost);
    Topological topo(g);
    if (topo.isDAG())
        cout << "isDAG" << endl;
    else
    {
        cout << "is not dag" << endl;
    }
    vector<int> order = topo.order();
    print(order);
    KosarajuSCC scc(g);
    cout << scc.resultSCC() << endl;
}