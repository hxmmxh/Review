//有一个文本串S，和一个模式串P，现在要查找P在S中的位置
//引用于 https://blog.csdn.net/v_july_v/article/details/7041827
//KMP解法
//Knuth-Morris-Pratt 字符串查找算法，简称为 “KMP算法”，常用于在一个文本串S内查找一个模式串P 的出现位置，
//这个算法由Donald Knuth、Vaughan Pratt、James H. Morris三人于1977年联合发表，故取这3人的姓氏命名此算法。

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//暴力解法
int ViolentMatch(string s, string p)
{
	int sLen = s.size();
	int pLen = p.size();
	int i = 0;
	int j = 0;
	while (i < sLen && j < pLen)
	{
		if (s[i] == p[j]) //①如果当前字符匹配成功（即S[i] == P[j]），则i++，j++
		{
			i++;
			j++;
		}
		else //②如果失配（即S[i]! = P[j]），令i = i - (j - 1)，j = 0
		{
			i = i - j + 1;
			j = 0;
		}
	}
	//匹配成功，返回模式串p在文本串s中的位置，否则返回-1
	if (j == pLen)
		return i - j;
	else
		return -1;
}

// next[i] 对应的下标，为 P[0...i - 1] 的最长公共前缀后缀的长度
/* 例如对于字符串 abcba：
 * 前缀：它的前缀包括：a, ab, abc, abcb，不包括本身；
 * 后缀：它的后缀包括：bcba, cba, ba, a，不包括本身；
 * 最长公共前缀后缀：abcba 的前缀和后缀中只有 a 是公共部分，字符串 a 的长度为 1。
 * actgpacy的next数组为
 * -1 0 0 0 0 0 1 2 
 */

/*
- 当 j 的值为 0 或 1 的时候，它们的 k 值都为 0，即 next[0] = 0、next[1] =0。但是为了后面 k 值计算的方便，我们将 next[0] 的值设置成 -1。
-  p[j] == p[k] 
	- 当 t[j] == t[k] 时，必然有"t[0]…t[k-1]" == " t[j-k]…t[j-1]"，此时的 k 即是相同子串的长度
	- 容易得到next[j+1]=k+1
- 当t[j] != t[k] 的情况
	- 
*/
vector<int> &buildNext(string &p)
{
	int n = p.size();
	vector<int> next(n + 1, -1); //这里数组大小为n+1，是为了方便计算p[n-1]
	int k = -1, j = 0;
	while (j < n)
	{
		if (k == -1 || p[k] == p[j])
			next[++j] = ++k;
		else
			k = next[k];
	}
	return next;
}

int KmpSearch(string s, string p)
{
	int i = 0;
	int j = 0;
	int sLen = s.size();
	int pLen = p.size();
	vector<int> next = buildNext(p);
	// i表示文本串S中匹配的位置
	// j表示模式串P中匹配的位置
	while (i < sLen && j < pLen)
	{
		// 如果j = -1，或者当前字符匹配成功（即S[i] == P[j]），都令i++，j++
		// 当j=-1，说明文本串S中要前进一步，同时P从头开始匹配
		if (j == -1 || s[i] == p[j])
		{
			i++;
			j++;
		}
		else
		{
			//如果j != -1，且当前字符匹配失败（即S[i] != P[j]），则令 i 不变，j = next[j]
			//next[j]即为j所对应的next值
			j = next[j];
		}
	}
	if (j == pLen)
		return i - j;
	else
		return -1;
}

int main()
{
	cout << "hello" << endl;
}