#include <vector>
#include <iostream>
#include <random>
#include <time.h>
using namespace std;

void print(vector<int> &nums)
{
    for (int i : nums)
        cout << i << ' ';
    cout << endl;
}

void getrandom(vector<int> &nums, int n)
{
    static std::default_random_engine e(time(0));
    static std::uniform_int_distribution<unsigned> u(0, 100);
    for (int i = 0; i < n; ++i)
        nums.push_back(u(e));
}

void Select(vector<int> nums)
{
    cout << "Select:\n";
    for (int i = 0; i < nums.size(); ++i)
    {
        int cur = i;
        for (int j = i + 1; j < nums.size(); ++j)
            if (nums[j] < nums[cur])
                cur = j;
        swap(nums[i], nums[cur]);
    }
    print(nums);
}

void Insert(vector<int> nums)
{
    cout << "Insert:\n";
    for (int i = 1; i < nums.size(); ++i)
    {
        for (int j = i; j > 0 && nums[j] < nums[j - 1]; --j)
            swap(nums[j], nums[j - 1]);
    }
    print(nums);
}

void Bubble(vector<int> nums)
{
    cout << "Bubble:\n";
    for (int i = 0; i < nums.size(); ++i)
    {
        for (int j = nums.size() - 1; j > i; --j)
            if (nums[j] < nums[j - 1])
                swap(nums[j], nums[j - 1]);
    }
    print(nums);
}

void Shell(vector<int> nums)
{
    cout << "Shell:\n";
    int h = 1;
    while (h < nums.size() / 3)
        h = h * 3 + 1;
    while (h >= 1)
    {
        for (int i = h; i < nums.size(); ++i)
            for (int j = i; j >= h && nums[j] < nums[j - h]; j -= h)
                swap(nums[j], nums[j - h]);
        h /= 3;
    }
    print(nums);
}

// 合并[l,m],[m+1,r]
void _aux_merge(vector<int> &nums, int l, int m, int r)
{
    vector<int> aux(nums.begin() + l, nums.begin() + r + 1);
    int posa = l, posb = m + 1;
    for (int i = l; i <= r; ++i)
        if (posa > m)
            nums[i] = aux[posb++ - l];
        else if (posb > r)
            nums[i] = aux[posa++ - l];
        else if (aux[posa - l] < aux[posb - l])
            nums[i] = aux[posa++ - l];
        else
            nums[i] = aux[posb++ - l];
}

void _aux_merge_sort(vector<int> &nums, int l, int r)
{
    if (l >= r)
        return;
    int mid = l + (r - l) / 2;
    _aux_merge_sort(nums, l, mid);
    _aux_merge_sort(nums, mid + 1, r);
    _aux_merge(nums, l, mid, r);
}

void Merge(vector<int> nums)
{
    cout << "Merge:\n";
    _aux_merge_sort(nums, 0, nums.size() - 1);
    print(nums);
}

void MergeBU(vector<int> nums)
{
    cout << "MergeBU:\n";
    for (int sz = 1; sz < nums.size(); sz *= 2)
        for (int i = 0; i < nums.size() - sz; i += sz * 2)
            _aux_merge(nums, i, i + sz - 1, i + sz * 2 - 1 >= nums.size() ? nums.size() - 1 : i + sz * 2 - 1);
    print(nums);
}

void _aux_quick(vector<int> &nums, int l, int r)
{
    if (l >= r)
        return;
    int pos = l;
    int k = nums[r];
    for (int i = l; i < r; ++i)
        if (nums[i] < k)
        {
            swap(nums[pos], nums[i]);
            ++pos;
        }
    swap(nums[pos], nums[r]);
    _aux_quick(nums, l, pos - 1);
    _aux_quick(nums, pos + 1, r);
}

void Quick(vector<int> nums)
{
    cout << "Quick:\n";
    _aux_quick(nums, 0, nums.size() - 1);
    print(nums);
}

void _aux_sink(vector<int> &nums, int pos, int end)
{
    while (2 * pos + 1 <= end)
    {
        int i = 2 * pos + 1;
        if (i + 1 <= end && nums[i + 1] > nums[i])
            ++i;
        if (nums[i] > nums[pos])
        {
            swap(nums[pos], nums[i]);
            pos = i;
        }
        else
            break;
    }
}

void Heap(vector<int> nums)
{
    cout << "Heap:\n";
    for (int i = (nums.size() - 2) / 2; i >= 0; --i)
        _aux_sink(nums, i, nums.size() - 1);
    for (int i = nums.size() - 1; i > 0; --i)
    {
        swap(nums[0], nums[i]);
        _aux_sink(nums, 0, i - 1);
    }
    print(nums);
}

int main()
{
    vector<int> nums;
    getrandom(nums, 20);
    Select(nums);
    Insert(nums);
    Bubble(nums);
    Shell(nums);
    Merge(nums);
    MergeBU(nums);
    Quick(nums);
    Heap(nums);
}