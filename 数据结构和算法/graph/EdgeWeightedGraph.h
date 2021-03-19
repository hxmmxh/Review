//加权无向图

#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdio>
#include <queue>

using namespace std;

class Edge
{
  public:
	Edge(int a, int b, double w) : _sta(a), _des(b), _weight(w) {}
	int either() { return _sta; }						   //随便得到一个顶点，默认给起点
	int other(int v) { return (v == _sta) ? _des : _sta; } //已知一个顶点，得到另一个顶点
	double weight() { return _weight; }
	/*bool operator< (Edge a) //想要让自定义类能够使用优先队列，我们要重载小于号
	{
		return _weight > a.weight(); //我们想让weight小的先出列，要很违和的给这个小于符号重载成实际上是大于的定义
	}
	!!!实践证明这个方法不行！！
	*/
	string toString()
	{
		char c[10];
		sprintf(c, "%.2f", weight());
		return (to_string(_sta) + "-" + to_string(_des) + ":" + c);
	}

  private:
	int _sta;		//边的起点
	int _des;		//边的终点
	double _weight; //边的权重
};

class EdgeWeightedGraph
{
  public:
	EdgeWeightedGraph(int v = 0) : nv(v), ne(0), veadj(v) {}
	EdgeWeightedGraph(istream &);
	int V() { return nv; }
	int E() { return ne; }
	void addEdge(Edge e);
	vector<Edge> adj(int v) { return veadj[v]; }
	vector<Edge> edges();
	string tostring();

  private:
	int nv;
	int ne;
	vector<vector<Edge>> veadj;
};

EdgeWeightedGraph::EdgeWeightedGraph(istream &input)
{
	int v, e;
	input >> v;
	input >> e;
	*this = EdgeWeightedGraph(v);
	for (int i = 0; i < e; ++i)
	{
		int a, b;
		double w;
		input >> a;
		input >> b;
		input >> w;
		Edge add(a, b, w);
		addEdge(add);
	}
}

void EdgeWeightedGraph::addEdge(Edge e)
{
	int v = e.either(), w = e.other(v);
	veadj[v].push_back(e);
	veadj[w].push_back(e);
	++ne;
}

vector<Edge> EdgeWeightedGraph::edges()
{
	vector<Edge> res;
	for (int i = 0; i < nv; ++i)
	{
		for (Edge e : adj(i))
			if (e.other(i) > i) //确保每条边只统计一次
				res.push_back(e);
	}
	return res;
}

string EdgeWeightedGraph::tostring()
{
	string s = to_string(V()) + "vertices, " + to_string(E()) + " edges\n";
	for (int i = 0; i < V(); ++i)
	{
		s += to_string(i) + ": ";
		for (Edge e : adj(i))
		{
			s += e.toString() + "  ";
		}
		s += '\n';
	}
	return s;
}

struct edgecom
{
	bool operator()(Edge a, Edge b) const
	{
		return a.weight() > b.weight();
	}
};
/*如果没有重载edge的小于号，构造优先队列需要这样
priority_queue<Edge, vector<Edge>, edgecom> pq;
*/
class LazyPrimMST
{
  public:
	LazyPrimMST(EdgeWeightedGraph G);
	vector<Edge> edges() { return mst; } //最小生成树的所有边
	double weight() { return _weight; }  //最小生成树的权重

  private:
	EdgeWeightedGraph g;
	double _weight;
	vector<bool> marked;							//最小生成树的顶点
	vector<Edge> mst;								//最小生成树的边
	priority_queue<Edge, vector<Edge>, edgecom> pq; //用优先队列储存横切边（包括失效的边），已重载Edge的小于号
	void visit(int v);								//标记顶点v并将所有连接v和未标记顶点的边加入优先队列
};

LazyPrimMST::LazyPrimMST(EdgeWeightedGraph G)
{
	g = G;
	marked = vector<bool>(g.V());
	visit(0); //从0号顶点开始
	while (!pq.empty())
	{
		Edge e = pq.top(); //找到权重最小的边
		pq.pop();
		int v = e.either(), w = e.other(v); //找到边的两个顶点
		if (marked[v] && marked[w])
			continue; //如果不是横切边，则跳过，继续寻找
					  //prim的延迟实现
		mst.push_back(e);
		_weight+=e.weight();
		if (!marked[v])
			visit(v);
		if (!marked[w])
			visit(w); //v或w有且只有一个被标记
	}
}

void LazyPrimMST::visit(int v)
{
	marked[v] = true;
	for (Edge e : g.adj(v))		 //对于顶点v连接的每条边
		if (!marked[e.other(v)]) //如果另一个顶点没有被标记（即不在最小生成树中），则说明这条边是横切边
			pq.push(e);			 //加入优先队列中
}