#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <queue>

using namespace std;

unordered_map<int, int> memo;

int dp(int K, int N)
{
    if (memo.find(N * 100 + K) == memo.end())
    {
        int ans;
        if (N == 0)
            ans = 0;
        // 只有一个鸡蛋了，必须从第一层开始一层层往上试
        else if (K == 1)
            ans = N;
        else
        {
            int lo = 1, hi = N;
            // 当lo==hi，或者两者只间隔1时停止
            while (lo + 1 < hi)
            {
                int x = (lo + hi) / 2;
                // 如果在x层丢掉下去，鸡蛋碎了，下一步是从第一层到第x-1层找
                // t1随着x的增加，递增
                int t1 = dp(K - 1, x - 1);
                // 如果鸡蛋没碎，从第x+1层到第N层找
                // t2随着x的增加，递减
                int t2 = dp(K, N - x);
                // 我们要尝试找到一个x,使t1=t2，这样的话max(t1,t2)是最小的
                // 所以如果t1<t2，x要变大，因此把lo设为x
                if (t1 < t2)
                    lo = x;
                // 如果t1>t2，x要变小，因此把hi设为x
                else if (t1 > t2)
                    hi = x;
                else
                    lo = hi = x;
            }
            // 最终找的的lo是最大的满足t1<t2的值
            // hi是最小的满足 t1>t2的值
            ans = 1 + min(max(dp(K - 1, lo - 1), dp(K, N - lo)), max(dp(K - 1, hi - 1), dp(K, N - hi)));
        }
        memo[N * 100 + K] = ans;
    }
    return memo[N * 100 + K];
}

int superEggDrop(int K, int N)
{
    return dp(K, N);
}