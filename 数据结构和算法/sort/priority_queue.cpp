#include <vector>
#include <iostream>
#include <ctime>
#include <random>
#include <map>

using namespace std;

template <typename T>
class MaxPQ
{
public:
    MaxPQ(vector<T> a={});
    void insert(T);
    T max();
    void delmax();
    bool empty()
    {
        return N == 0;
    }
    int size()
    {
        return N;
    }
    void result()
    {
        while (!empty())
        {
            cout << max() << ' ';
            delmax();
        }
        cout << '\n';
    }

private:
    vector<T> data;         //不使用数组的第一个位置时，位置k的父节点为k/2，左子节点为2k，右子节点为2k+1
    int N;                  //元素个数，堆的大小
    void exch(int i, int j) //交换两个元素
    {
        T tem = data[i];
        data[i] = data[j];
        data[j] = tem;
    }
    void swim(int k) //上浮，由下至上堆有序化。产生原因：某个节点比它的父节点要大
    {
        //交换它和它的父节点
        while (k > 1 && data[k / 2] < data[k]) //k/2为根时终止循环
        {
            exch(k / 2, k);
            k = k / 2;
        }
    }
    void sink(int k) //下沉，由上至下的堆有序化。产生原因：某个节点比它的子节点要小
    {
        //将它和它的两个子节点中的较大者交换
        while (2 * k <= N)
        {
            int j = 2 * k;
            if (j < N && data[j] < data[j + 1]) //找两个子节点的较大者
                ++j;
            if (data[k] >= data[j])
                break;
            exch(k, j);
            k = j;
        }
    }
};

template <typename T>
MaxPQ<T>::MaxPQ(vector<T> a)
{
    N = 0;
    data.push_back(0); //不使用数组的第一个位置
    for (auto c : a)
        insert(c);
}

//堆的插入
//将新元素加到数组的末尾，增加堆的大小，并让这个元素上浮到合适的位置
template <typename T>
void MaxPQ<T>::insert(T val)
{
    data.push_back(val);
    swim(++N);
}

//删除元素，将最大的元素与最后一个元素交换，然后下沉
template <typename T>
void MaxPQ<T>::delmax()
{
    data[1] = data[N--];
    data.pop_back();
    sink(1);
}

template <typename T>
T MaxPQ<T>::max()
{
    return data[1];
}

int main()
{
    vector<int> nums;
    for (int i = 0; i < 20; ++i)
        nums.push_back(i);
    static std::default_random_engine e(time(0));
    static std::uniform_int_distribution<unsigned> u(0, 20);
    map<int, int> times;
    for (int i = 0; i < 1000; ++i)
        ++times[u(e)];
    for (auto p : times)
        cout << p.first << ": " << p.second << '\n';
    for (int i = nums.size() - 1; i > 0; --i)
    {
        static std::uniform_int_distribution<unsigned> u(0, i);
        int sw = u(e);
        swap(nums[sw], nums[i]);
    }
    MaxPQ<int> mp(nums);
    for (int i : nums)
    {
        cout << i << ' ';
        //mp.insert(i);
    }
    cout << '\n';
    mp.result();
}

