
#include "graph_base.h"
#include "graph_search.h"
#include "graph_cc.h"
#include "SymbolGraph.h"

int main()
{
    fstream f("data/tinyG.txt");
    Graph g(f);
    //string s=g.tostring();
    //cout<<s<<endl;
    DFS d1(g, 0);
    string s1 = d1.resultPath();
    BFS b1(g, 0);
    string s2 = b1.resultPath();
    cout << s1 << endl;
    cout << s2 << endl;
    Graph_CC cc(g);
    string s3 = cc.resultCC();
    cout << s3 << endl;
}

/*int main()
{
	fstream f("data/routes.txt");
	Symbol_Graph g(f,' ');
	string output=g.tostring();
	cout<<output;
}
*/