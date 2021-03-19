
// https://zhuanlan.zhihu.com/p/93647900/

#include <iostream>
#include <vector>
#include <fstream>

// 并查集
class UF
{
public:
	UF(int);
	// 集合个数
	int count() { return c; }
	// 判断两个元素是否在同一集合
	bool connected(int p, int q) { return find(p) == find(q); }
	// 查询元素所在的集合
	virtual int find(int) = 0;
	// 把两个不相交的集合合并为一个集合，有时函数名称也叫做union
	virtual void link(int, int) = 0;

protected:
	std::vector<int> id;
	int c;
};

UF::UF(int n)
{
	c = n;
	for (int i = 0; i < n; ++i)
		id.push_back(i);
}

//下面有三种link的方式

// 最简单方式
class QF_UF : public UF
{
public:
	QF_UF(int i) : UF(i) {}
	int find(int) override;
	void link(int, int) override;
};

int QF_UF::find(int i)
{
	return id[i];
}

// 合并时,遍历所有元素，把属于另一个集合的元素都改为这个集合
void QF_UF::link(int a, int b)
{
	int ia = find(a);
	int ib = find(b);
	if (ia == ib)
		return;
	for (int i = 0; i < id.size(); ++i)
		if (find(i) == ia)
			id[i] = ib;
	--c;
}

// 第二种
// 会组成一个树状的结构，要寻找集合的代表元素，只需要一层一层往上访问父节点，直达树的根节点
// 根节点的父结点是它自己
// 此时数组id的含义变成每个元素的父结点
class QU_UF : public UF
{
public:
	QU_UF(int n) : UF(n) {}
	int find(int) override;
	void link(int, int) override;
};

int QU_UF::find(int a)
{
	// 一层一层访问父节点，直至根节点
	// 根节点的标志就是父节点是本身
	// 要判断两个元素是否属于同一个集合，只需要看它们的根节点是否相同即可。
	while (id[a] != a)
		a = id[a];
	return a;
}

inline void QU_UF::link(int a, int b)
{
	int ia = find(a);
	int ib = find(b);
	if (ia == ib)
		return;
	id[ia] = ib;
	--c;
}

// 第三种，加入一个新数组size，记录每个类含有多少成员
// 在find中实现路径压缩
// 通过size数组在link中实现按秩合并
class WQU_UF : public UF
{
public:
	WQU_UF(int n) : UF(n)
	{
		for (int i = 0; i < n; ++i)
			size.push_back(1);
	}
	int find(int) override;
	void link(int, int) override;
	void linkDepth(int, int);

private:
	std::vector<int> size;
};

// 实现了路径压缩
int WQU_UF::find(int i)
{
	// 为了防止树退化成链，增加查询时循环的次数
	// 在查询的过程中，把沿途的每个节点的父节点都设为根节点
	if(i==id[i])
		return i;
	else
	{
		id[i] = find(id[i]);
		return id[i];
	}
}

// 按秩（树里的节点数量）合并
void WQU_UF::link(int a, int b)
{
	int ia = find(a);
	int ib = find(b);
	if (ia == ib)
		return;
	// 把节点少的树往节点多的树上合并
	if (size[ia] < size[ib])
	{
		id[ia] = ib;
		size[ib] += size[ia];
	}
	else
	{
		id[ib] = ia;
		size[ia] += size[ib];
	}
	--c;
}

// 还有一种合并方式是按树的深度合并
// 短的树合并到深的树上面，把size较小者往较大者上合并
// 下面代码中size数据记录的是每个根节点对应的树的深度
// 初始化可以不用变，因为深度一开始也都是1
void WQU_UF::linkDepth(int a, int b)
{
	int ia = find(a);
	int ib = find(b);
	if (ia == ib)
		return;
	if (size[ia] <= size[ib])
	{
		id[ia] = ib;
	}
	else
	{
		id[ib] = ia;
	}
	// 如果深度相同且根节点不同，则新的根节点的深度+1
	if(size[ia]==size[ib])
		size[ib]++;
	--c;
}

//测试程序
void quickfind_test()
{
	std::fstream input("data/tinyUF.txt");
	int n;
	input >> n;
	WQU_UF uf(n);
	while (input.peek() != EOF) //注意，读取文件中方法，如果有问题会读取最后一行两次
	{
		int a, b;
		input >> a;
		input >> b;
		if (input.fail())
			break;
		if (uf.connected(a, b))
			continue;
		uf.link(a, b);
		std::cout << a << ' ' << b << '\n';
	}
	std::cout << uf.count() << " components" << std::endl;
}

int main()
{
	quickfind_test();
}
