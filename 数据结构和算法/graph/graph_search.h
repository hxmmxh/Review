//将图的表示和实现分离开来
//为每个任务创建一个相应的类，用例可以创建相应的对象来完成任务
//图的搜索，深度优先和广度优先

#pragma once
#ifndef GRAPH_SEARCH
#define GRAPH_SEARCH

#include "graph_base.h"

class Graph_Search_Path //搜索和查找路径的基类
{
  public:
    Graph_Search_Path(Graph G, int i) : g(G), s(i), marked(g.V(), 0), edgeTo(g.V(), 0), c(0) {}
    bool linked(int v) //判断两点是否连通
    {
        return marked[v];
    }
    int count() //与该点连通的顶点总数
    {
        return c;
    }
    vector<int> pathTo(int); //给出到某个顶点的路径
    string resultSearch();   //以字符串格式输出查找结果，先返回与点s连通的顶点编号，再返回图g是否是连通图
    string resultPath();     //以字符串格式输出路径结果

  protected:
    Graph g;
    int s;               //从哪个顶点开始搜索，起点
    vector<bool> marked; //是否联通
    vector<int> edgeTo;  //从起点到一个顶点的已知路径的最后一个顶点
    int c;               //连通的点的数目
};

class DFS : public Graph_Search_Path //深度优先搜索
{
  public:
    DFS(Graph G, int i) : Graph_Search_Path(G, i) { dfs(s); }
    void dfs(int);
};

class BFS : public Graph_Search_Path //广度优先搜索
{
  public:
    BFS(Graph G, int i) : Graph_Search_Path(G, i) { bfs(s); }
    void bfs(int);
};

void DFS::dfs(int v)
{
    marked[v] = true;
    ++c;
    for (int i : g.adj(v))
        if (!marked[i])
        {
            edgeTo[i] = v;
            dfs(i);
        }
}

void BFS::bfs(int v)
{
    ++c;
    queue<int> aux;
    marked[v] = true;
    aux.push(v);
    while (!aux.empty())
    {
        int i = aux.front();
        aux.pop();
        for (int j : g.adj(i))
            if (!marked[j])
            {
                ++c;
                marked[j] = true;
                edgeTo[j] = i;
                aux.push(j);
            }
    }
}

vector<int> Graph_Search_Path::pathTo(int v)
{
    vector<int> res;
    if (!linked(v))
        return res;
    for (int x = v; x != s; x = edgeTo[x])
        res.push_back(x);
    res.push_back(s);
    reverse(res.begin(), res.end());
    return res;
}

string Graph_Search_Path::resultSearch()
{
    string res;
    for (int i = 0; i < g.V(); ++i)
        if (marked[i])
            res += to_string(i) + ' ';
    res += '\n';
    if (c != g.V())
        res += "NOT ";
    res += "connected";
    return res;
}

string Graph_Search_Path::resultPath()
{
    string res;
    for (int i = 0; i < g.V(); ++i)
    {
        res += to_string(s) + " to " + to_string(i) + ": ";
        if (linked(i))
            for (int x : pathTo(i))
                if (x == s)
                    res += to_string(x);
                else
                    res += "-" + to_string(x);
        res += '\n';
    }
    if (count() != g.V())
        res += "NOT ";
    res += "connected";
    return res;
}

#endif