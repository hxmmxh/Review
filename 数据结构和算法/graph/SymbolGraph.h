//符号图
//使用字符串来表示和指代顶点

#pragma once

#include "graph_base.h"
#include <map>
#include <sstream>

vector<string> splitstr(string &str, char delim) //切割字符串函数
{
	vector<string> res;
	string tem;
	int start = 0;
	while (true)
	{
		int pos = str.find_first_of(delim, start);
		if (pos == -1)
		{
			res.push_back(str.substr(start));
			break;
		}
		else
		{
			res.push_back(str.substr(start, pos - start));
			start = pos + 1;
		}
	}
	return res;
}

class Symbol_Graph : public Graph
{
public:
	Symbol_Graph(istream &, char);
	bool containes(string key) { return names.count(key) == 0; } //是否包含key
	int index(string key) { return names[key]; }								 //查看key的索引
	string name(int v) { return keys[v]; }											 //索引v的顶点名
	string tostring() const override;

private:
	map<string, int> names; //记录每个顶点名的索引,符合名->索引
	vector<string> keys;		//记录每个索引的顶点名，索引->符号名
};

Symbol_Graph::Symbol_Graph(istream &in, char sp) //sp代表分隔符
{
	string line;
	while (getline(in, line))
	{
		vector<string> strs = splitstr(line, sp);
		if (!names.count(strs[0]))
		{
			names[strs[0]] = names.size();
			++nv;
			veadj.push_back({});
			keys.push_back(strs[0]);
		}
		for (int i = 1; i < strs.size(); ++i)
		{
			if (!names.count(strs[i]))
			{
				names[strs[i]] = names.size();
				++nv;
				veadj.push_back({});
				keys.push_back(strs[i]);
			}
			++ne;
			addEdge(names[strs[0]], names[strs[i]]);
		}
	}
}

string Symbol_Graph::tostring() const
{
	string s = to_string(V()) + "vertices, " + to_string(E()) + " edges\n";
	for (int i = 0; i < V(); ++i)
	{
		s += keys[i] + ": ";
		for (int j : adj(i))
			s += keys[j] + " ";
		s += '\n';
	}
	return s;
}
