#include "EdgeWeightedGraph.h"

int main()
{
    fstream f("data/tinyEWG.txt");
    EdgeWeightedGraph ewg(f);
    cout << ewg.tostring();
    LazyPrimMST lpm(ewg);
    cout << lpm.weight() << endl;
    vector<Edge> ve = lpm.edges();
    for (auto e : ve)
        cout << e.toString() << endl;
}