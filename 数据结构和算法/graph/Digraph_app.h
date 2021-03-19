//有向图
//1.寻找有向环
//2.拓扑排序

#pragma once

#include "graph_base.h"

using namespace std;

//判断有向图中是否有环
class DirectedCycle
{
  public:
	DirectedCycle(Digraph G);
	bool hasCycle() { return !path.empty(); }
	vector<int> cycle() { return path; };
	void dfs(int);

  private:
	Digraph g;
	vector<bool> marked;
	vector<int> edgeto;
	vector<int> path;
	vector<bool> onpath;
};

DirectedCycle::DirectedCycle(Digraph G)
{
	g = G;
	for (int i = 0; i < G.V(); ++i)
	{
		onpath.push_back(0);
		marked.push_back(0);
		edgeto.push_back(-1);
	}
	for (int i = 0; i < G.V(); ++i)
		if (!marked[i])
			dfs(i);
}

void DirectedCycle::dfs(int v)
{
	onpath[v] = true;
	marked[v] = true;
	for (int w : g.adj(v))
		if (hasCycle())
			return;
		else if (!marked[w])
		{
			edgeto[w] = v;
			dfs(w);
		}
		else if (onpath[w])
		{
			for (int i = v; i != w; i = edgeto[i])
			{
				path.push_back(i);
			}
			path.push_back(w);
			path.push_back(v);
			reverse(path.begin(), path.end());
		}
	onpath[v] = false;
}

//基于深度优先搜索的顶点排序
class DepthFirstOrder
{
  public:
	DepthFirstOrder(Digraph G);
	void dfs(int);
	vector<int> pre() { return _pre; }
	vector<int> post() { return _post; }
	vector<int> reversePost() { return _reversePost; }

  private:
	Digraph g;
	vector<bool> marked;
	vector<int> _pre;		  //前序排列,在递归调用前将顶点加入队列
	vector<int> _post;		  //后序排序，在递归调用之后将顶点加入队列
	vector<int> _reversePost; //逆后序排序，后序排序的反序
};

DepthFirstOrder::DepthFirstOrder(Digraph G)
{
	g = G;
	for (int i = 0; i < g.V(); ++i)
		marked.push_back(0);
	for (int i = 0; i < g.V(); ++i)
		if (!marked[i])
			dfs(i);
	for (int i = _post.size() - 1; i >= 0; --i)
		_reversePost.push_back(_post[i]);
}

void DepthFirstOrder::dfs(int v)
{
	_pre.push_back(v);
	marked[v] = true;
	for (int w : g.adj(v))
		if (!marked[w])
			dfs(w);
	_post.push_back(v);
}

//拓扑排序
class Topological
{
  public:
	Topological(Digraph G);
	vector<int> order() { return _order; }
	bool isDAG() { return !_order.empty(); }

  private:
	vector<int> _order;
};

Topological::Topological(Digraph G)
{
	DirectedCycle cyclefinder(G);
	if (!cyclefinder.hasCycle()) //先检测是否无环
	{
		DepthFirstOrder dfsorder(G); //一幅有向无环图的拓扑排序即为所有顶点的逆后序排列
		_order = dfsorder.reversePost();
	}
}

//计算强连通分量的kosaraju算法
class KosarajuSCC
{
  public:
	KosarajuSCC(Digraph G);
	bool stronglyConnected(int v, int w) { return _id[v] == _id[w]; } //判断两个顶点是否在同一个强连通分量上
	int id(int v) { return _id[v]; }
	int count() { return _count; }
	string resultSCC();
	void dfs(int);

  private:
	Digraph g;
	vector<bool> marked;
	vector<int> _id;
	int _count;
	vector<vector<int>> components;
};

KosarajuSCC::KosarajuSCC(Digraph G)
{
	g = G;
	_count = 0;
	for (int i = 0; i < G.V(); ++i)
	{
		marked.push_back(0);
		_id.push_back(-1);
	}
	DepthFirstOrder order(G.Direverse());
	for (int i : order.reversePost())
		if (!marked[i])
		{
			dfs(i);
			++_count;
		}
	for (int i = 0; i < _count; ++i)
		components.push_back({});
	for (int i = 0; i < g.V(); ++i)
		components[_id[i]].push_back(i);
}

void KosarajuSCC::dfs(int v)
{
	marked[v] = true;
	_id[v] = _count;
	for (int i : g.adj(v))
		if (!marked[i])
			dfs(i);
}

string KosarajuSCC::resultSCC()
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