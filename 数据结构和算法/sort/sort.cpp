#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <chrono>
#include <string>

using namespace std;

class Sort
{
    friend std::istream &operator>>(std::istream &, Sort &);
    friend std::ostream &operator<<(std::ostream &, Sort &);
    typedef std::vector<int>::size_type size;

public:
    Sort() = default;
    Sort(vector<int> &s) : nums(s) {}
    void getrandom(int n, int r = 100);
    void rerandom();
    void Select_sort();
    void Insert_sort();
    void Bubble_sort();
    void Shell_sort();
    void Merge_sort();   //自顶向下
    void MergeBU_sort(); //自底向上
    void Quick_sort();
    void Heap_sort();
    using sortmethod = void (Sort::*)();
    enum method
    {
        select,
        insert,
        bubble,
        shell,
        merge,
        mergeBU,
        quick,
        heap
    };
    double timer(sortmethod);
    void sort(method, bool b = true);
    int _partition(int, int);
    void _quick_sort(int, int);
    int aux_partition(int, int);
    void sink(int, int);

private:
    std::vector<int> nums;
    static sortmethod sm[];
    static std::string methodname[];

private:
    void exchange(size p, size q)
    {
        if (p == q)
            return;
        int temp;
        temp = nums[p];
        nums[p] = nums[q];
        nums[q] = temp;
    }
    bool issorted()
    {
        for (size i = 0; i < nums.size() - 1; ++i)
            if (nums[i] > nums[i + 1])
                return false;
        return true;
    }
    bool less(size p, size q)
    {
        return (nums[p] < nums[q]) ? true : false;
    }
};

Sort::sortmethod Sort::sm[] = {
    &Select_sort,
    &Insert_sort,
    &Bubble_sort,
    &Shell_sort,
    &Merge_sort,
    &MergeBU_sort,
    &Quick_sort,
    &Heap_sort};

std::string Sort::methodname[] = {
    "select",
    "insert",
    "bubble",
    "shell",
    "merge",
    "mergeBU",
    "quick",
    "heap"};

void Sort::sort(method m, bool b)
{
    double t = timer(sm[m]);
    if (b)
        cout << *this << endl;
    cout << methodname[m] << " method cost " << t << "ms" << endl;
}

std::istream &operator>>(std::istream &is, Sort &array)
{
    int i;
    while (is >> i)
        array.nums.push_back(i);
    return is;
}

std::ostream &operator<<(std::ostream &os, Sort &array)
{
    for (auto i : array.nums)
        os << i << " ";
    return os;
}

void Sort::getrandom(int n, int r)
{
    static std::default_random_engine e(time(0));
    static std::uniform_int_distribution<unsigned> u(0, r);
    for (int i = 0; i < n; ++i)
        nums.push_back(u(e));
}

void Sort::rerandom()
{
    static std::default_random_engine e(time(0));
    for (int i = nums.size() - 1; i > 0; --i)
    {
        static std::uniform_int_distribution<unsigned> u(0, i);
        int sw = u(e);
        exchange(sw, i);
    }
}

double Sort::timer(sortmethod m)
{
    auto start = std::chrono::high_resolution_clock::now();
    (this->*m)();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    return static_cast<double>(duration.count());
}

void Sort::Select_sort() //每次循环找出当前位置之后的最小值与自身交换
{
    for (size i = 0; i < nums.size() - 1; ++i)
    {
        size m = i;
        for (size j = i + 1; j < nums.size(); ++j)
            if (less(j, m))
                m = j;
        exchange(i, m);
    }
}

void Sort::Insert_sort() //每次循环把当前值往前移动直到合适的位置
{
    for (size i = 1; i < nums.size(); ++i)
        for (size j = i; j > 0 && less(j, j - 1); --j)
            exchange(j - 1, j);
}

void Sort::Bubble_sort() //从后往前排，插入排序的反向
{
    for (size i = nums.size() - 1; i > 0; --i)
        for (size j = 0; j < i; ++j)
            if (!less(j, j + 1))
                exchange(j, j + 1);
}

void Sort::Shell_sort() //间隔一定量排序
{
    int h = 1;
    while (h < nums.size() / 3)
        h = h * 3 + 1;
    while (h >= 1)
    {
        for (int i = h; i < nums.size(); ++i) //内部使用插入排序
            for (int j = i; j >= h && less(j, j - h); j -= h)
                exchange(j - h, j);
        h = h / 3;
    }
}

void aux_merge(vector<int> &num, int lo, int mid, int hi) //将lo-mid和mid+1-hi合并,左闭右闭
{
    int i = lo, j = mid + 1;
    vector<int> aux(num.begin() + lo, num.begin() + hi + 1); //左闭右开
    for (int k = lo; k <= hi; ++k)
    {
        if (i > mid)
            num[k] = aux[j++ - lo];
        else if (j > hi)
            num[k] = aux[i++ - lo];
        else if (aux[i - lo] > aux[j - lo])
            num[k] = aux[j++ - lo];
        else
            num[k] = aux[i++ - lo];
    }
}

void aux_merge_sort(vector<int> &num, int lo, int hi)
{
    if (hi <= lo)
        return;
    int mid = lo + (hi - lo) / 2;
    aux_merge_sort(num, lo, mid);
    aux_merge_sort(num, mid + 1, hi);
    aux_merge(num, lo, mid, hi);
}

void Sort::Merge_sort()
{
    aux_merge_sort(nums, 0, nums.size() - 1);
}

void Sort::MergeBU_sort()
{
    int N = nums.size();
    for (int sz = 1; sz < N; sz *= 2)
        for (int lo = 0; lo < N - sz; lo += sz + sz)
            aux_merge(nums, lo, lo + sz - 1, (lo + sz + sz - 1) < (N - 1) ? lo + sz + sz - 1 : N - 1);
}

int Sort::aux_partition(int low, int high)
{
    int x = nums[high];
    int i = low;
    for (int j = low; j < high; ++j)
    {
        if (nums[j] <= x)
        {
            exchange(i, j);
            ++i;
        }
    }
    exchange(i, high);
    return i;
}

void Sort::_quick_sort(int low, int high)
{
    if (low < high)
    {
        int q = aux_partition(low, high);
        _quick_sort(low, q - 1);
        _quick_sort(q + 1, high);
    }
}

void Sort::Quick_sort()
{
    _quick_sort(0, nums.size() - 1);
}

//使用数组的第一个位置时，位置K的父结点为（k-1)/2,左子结点为2k+1,右子结点为2k+2
//构造的是最大堆
void Sort::sink(int n, int length)
{
    while (2 * n + 1 <= length)
    {
        int j = 2 * n + 1;
        // j指向两个子节点中的较大者
        if (j < length && nums[j + 1] > nums[j])
            ++j;
        // 当父结点大于所有子节点时，停止下沉
        if (nums[n] >= nums[j])
            break;
        // 否则交换
        exchange(n, j);
        n = j;
    }
}

void Sort::Heap_sort()
{
    int l = nums.size() - 1;
    // 从最后一个节点的父结点开始调整
    for (int i = (l-1) / 2; i >= 0; --i)
        sink(i, l);
    // 这时已经构建好得了最大堆
    // 每次循环都把当前的堆顶(也就是最大值)移动到尾部
    // 同时重新调整了堆
    while (l > 0)
    {
        exchange(0, l--);
        sink(0, l);
    }
}

int main()
{
    Sort data;
    data.getrandom(20000);
    //cout << data << endl;
    bool b = false;
    data.sort(Sort::select, b);
    data.rerandom();
    data.sort(Sort::insert, b);
    data.rerandom();
    data.sort(Sort::bubble, b);
    data.rerandom();
    data.sort(Sort::shell, b);
    data.rerandom();
    data.sort(Sort::merge, b);
    data.rerandom();
    data.sort(Sort::mergeBU, b);
    data.rerandom();
    data.sort(Sort::quick, b);
    data.rerandom();
    data.sort(Sort::heap, b);
}