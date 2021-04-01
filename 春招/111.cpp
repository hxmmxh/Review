#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <set>
#include <queue>
#include <atomic>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <numeric>
#include <math.h>
#include <algorithm>

#include <bits/stdc++.h>
using namespace std;

bool search(vector<vector<int>> &nums, vector<int> l, vector<int> r, int target)
{
    int m = nums.size(), n = nums[0].size();
    if (l[0] * m + l[1] > r[0] * m + r[1])
        return false;
    int midid = (l[0] * m + l[1] + r[0] * m + l[2]) / 2;
    if (nums[midid / m][midid % m] == target)
        return true;
    else if (nums[midid / m][midid % m] > target)
        return search(nums, l, {(midid - 1) / m, (midid - 1) % m}, target);
    else
        return search(nums, {(midid + 1) / m, (midid + 1) % m}, r, target);
}

bool searchMatrix(vector<vector<int>> &matrix, int target)
{
    int m = matrix.size(), n = matrix[0].size();
    return search(matrix, {0, 0}, {m - 1, n - 1}, target);
}