//两个深度优先搜索的应用
//判断是否有环
//判断是否是二分图
//能够将所有的结点分为两部分的图，其中图的每条边所连接的两个顶点都分别属于不同的部分

#pragma once

#include "graph_base.h"

class Graph_Cycle
{
  public:
    Graph_Cycle(Graph G) : g(G), hc(false), marked(g.V(), false) { init(); }
    bool hasCycle() { return hc; }

  private:
    Graph g;
    bool hc;
    vector<bool> marked;
    void init();
    void dfs(int, int);
};

void Graph_Cycle::init()
{
    for (int i = 0; i < g.V(); ++i)
        if (!marked[i])
            dfs(i, i);
}

void Graph_Cycle::dfs(int v, int u) //u是v的父结点
{
    marked[v] = true;
    for (int i : g.adj(v))
        if (!marked[i])
            dfs(i, v);
        else if (i != u) //如果是无环图的话，如果i已经被标记过，则i必定是v的父结点，也就是u
            hc = true;
}

class Graph_TwoColor
{
  public:
    Graph_TwoColor(Graph G) : g(G), marked(g.V(), 0), color(g.V(), 0), istwocolor(false) { init(); }
    bool isBipartite() { return istwocolor; }

  private:
    Graph g;
    vector<bool> marked;
    vector<bool> color;
    bool istwocolor;
    void init();
    void dfs(int);
};

void Graph_TwoColor::init()
{
    for(int i=0;i<g.V();++i)
        if(!marked[i])
            dfs(i);
}

void Graph_TwoColor::dfs(int v)
{
    marked[v]=true;
    for(int i : g.adj(v))
        if(!marked[v])
        {
            color[i]=!color[v];
            dfs(i);
        }
        else if (color[i]==color[v])
            istwocolor=false;
}