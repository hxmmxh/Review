//图的表示

#pragma once
#ifndef GRAPH_BASE
#define GRAPH_BASE

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

//基础图结构
class Graph_Base
{
  public:
    Graph_Base(int v = 0);
    //输入格式为2E+2个整数，首先是V，然后是E，再然后是E对边
    int V() const { return nv; };                      //顶点数
    int E() const { return ne; };                      //边数
    virtual void addEdge(int, int) = 0;                //向图中添加边
    vector<int> adj(int v) const { return veadj[v]; }; //相邻的所有顶点
    virtual string tostring() const;                   //图的字符串表示，用邻接表方
    int degree(int) const;                             //计算顶点的度
    int maxDegree() const;                             //计算所有顶点的最大度
    double avgDegree() const;                          //计算所有顶点的平均度数
    int numberOfSelfLoops() const;                     //计算自环的个数

  protected:
    int nv;                    //顶点数
    int ne;                    //边数
    vector<vector<int>> veadj; //邻接表数组
};

Graph_Base::Graph_Base(int v)
{
    nv = v;
    ne = 0;
    for (int i = 0; i < v; ++i)
        veadj.push_back({});
}

string Graph_Base::tostring() const
{
    string s = to_string(V()) + "vertices, " + to_string(E()) + " edges\n";
    for (int i = 0; i < V(); ++i)
    {
        s += to_string(i) + ": ";
        for (int j : adj(i))
            s += to_string(j) + " ";
        s += '\n';
    }
    return s;
}

int Graph_Base::degree(int v) const
{
    return (adj(v)).size();
}

int Graph_Base::maxDegree() const
{
    int res = 0;
    for (int i = 0; i < V(); ++i)
        res = max(res, degree(i));
    return res;
}

double Graph_Base::avgDegree() const
{
    return 2.0 * E() / V();
}

int Graph_Base::numberOfSelfLoops() const
{
    int res = 0;
    for (int v = 0; v < V(); ++v)
        for (int w : adj(v))
            if (v == w)
                ++res;
    return res / 2;
}

//无向图
class Graph : public Graph_Base
{
  public:
    Graph(int v = 0) : Graph_Base(v) {}
    Graph(istream &input);
    void addEdge(int, int) override;
};

void Graph::addEdge(int v, int w)
{
    veadj[v].push_back(w);
    veadj[w].push_back(v);
    ++ne;
}

Graph::Graph(istream &in)
{
    int v, e;
    in >> v;
    in >> e;
    *this = Graph(v);
    for (int i = 0; i < e; ++i)
    {
        int v, w;
        in >> v;
        in >> w;
        addEdge(v, w);
    }
}

//有向图
class Digraph : public Graph_Base
{
  public:
    Digraph(int v = 0) : Graph_Base(v) {}
    Digraph(istream &);
    Digraph Direverse();
    void addEdge(int, int) override;
};

void Digraph::addEdge(int v, int w)
{
    veadj[v].push_back(w);
    ++ne;
}

Digraph::Digraph(istream &in)
{
    int v, e;
    in >> v;
    in >> e;
    *this = Digraph(v);
    for (int i = 0; i < e; ++i)
    {
        int v, w;
        in >> v;
        in >> w;
        addEdge(v, w);
    }
}

Digraph Digraph::Direverse()
{
    Digraph res = Digraph(nv);
    for (int i = 0; i < nv; ++i)
        for (int j : adj(i))
            res.addEdge(j, i);
    return res;
}

#endif
