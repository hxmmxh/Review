//钢条切割方法
#include <vector>
#include <limits.h>
#include <unordered_map>
#include <iostream>

using namespace std;

//自顶向下
void Up_bottom_cut_rod(vector<int> &rod, vector<vector<int>> &cut)
{
    for (int i = 0; i < cut.size(); ++i)
        cut[i] = {INT_MIN, INT_MIN};
}

int _aux_Up_bottom_cut_rod(int n, vector<int> &rod, vector<vector<int>> &cut)
{
    if (cut[n][0] >= 0)
        return cut[n][0];
    for(int i=0;i<n;++i)
        if(cut[i][0]<rod[i]+_aux_Up_bottom_cut_rod(n-i-1,rod,cut))
            {
                cut[n][0]=
            }
}

//自底向上

void Bottom_up_cut_rod(const vector<int> &rod, vector<vector<int>> &cut)
{
    for (int i = 0; i < rod.size(); ++i)
    {
        cut[i].push_back(rod[i]);
        cut[i].push_back(i + 1);
        for (int j = 0; j < i; ++j)
            if (cut[i][0] < rod[j] + cut[i - j - 1][0])
            {
                cut[i][0] = rod[j] + cut[i - j - 1][0];
                cut[i][1] = j + 1;
            }
    }
}

//切割需要付出成本

int main()
{
    vector<int> rod{1, 5, 8, 9, 10, 17, 17, 20, 24, 30}; //不同长度对应的价格，从1开始到10
    vector<vector<int>> cut(rod.size());                 //记录每个长度对应的 收益最大值以及第一段切割的长度
    Bottom_up_cut_rod(rod, cut);
    for (int i = 0; i < rod.size(); ++i)
        cout << cut[i][0] << "," << cut[i][1] << endl;
}