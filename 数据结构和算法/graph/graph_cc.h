//寻找图的连通分量

#pragma once
#ifndef GRAPH_CC
#define GRAPH_CC

#include "graph_base.h"

//读取一幅图并打印其中的连通分量数，其后是每个子图的所有顶点，每行一个子图

class Graph_CC //连通分量
{
  public:
    Graph_CC(Graph G) : g(G), c(0), _id(g.V(), -1) { cc_init(); }
    bool connected(int v, int w) { return _id[v] == _id[w]; } //两个顶点是否连通
    int count() { return c; }                                 //连通分量数
    int id(int v) { return _id[v]; }                          //所在连通分量的标识符
    string resultCC();                                        //打印结果

  private:
    Graph g;
    int c;           //连通分量数
    vector<int> _id; //_id被初始化为-1
    vector<vector<int>> components;
    void cc_init(); //初始化函数
    void dfs(int);  //用深度优先搜索的方法找连通分量
};

string Graph_CC::resultCC()
{
    string res;
    int num = count();
    res += to_string(num) + " components" + '\n';
    for (int i = 0; i < num; ++i)
    {
        res += "components " + to_string(i) + ": ";
        for (int j : components[i])
            res += to_string(j) + ' ';
        res += '\n';
    }
    return res;
}

void Graph_CC::cc_init()
{
    for (int i = 0; i < g.V(); ++i)
        if (_id[i] == -1) //_id为-1表示没有被标记过
        {
            dfs(i);
            ++c;
        }
    for (int i = 0; i < c; ++i)
        components.push_back({});
    for (int i = 0; i < g.V(); ++i)
        components[_id[i]].push_back(i);
}

void Graph_CC::dfs(int v)
{
    _id[v] = c;
    for (int i : g.adj(v))
        if (_id[i] == -1)
            dfs(i);
}

#endif