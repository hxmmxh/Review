#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <queue>
#include <stack>
#include <cctype>
#include <time.h>
#include <stdlib.h>
#include <cmath>

using namespace std;

int main()
{
    // str1和str2的地址不一样
    char str1[] = "hello world";
    char str2[] = "hello world";
    // str3个str4的地址一样
    char *str3 = "hello world";
    char *str4 = "hello world";
}

A *a = NULL;
try
{
    cout << typeid(*a).name() << endl; // Error condition
}
catch (bad_typeid)
{
    cout << "Object is NULL" << endl;
}
return 0;

#include <iostream>
using namespace std;

// 间接基类，即虚基类
class Base1
{
public:
    int var1;
};

// 直接基类
class Base2 : virtual public Base1 // 虚继承
{
public:
    int var2;
};

// 直接基类
class Base3 : virtual public Base1 // 虚继承
{
public:
    int var3;
};

// 派生类
class Derive : public Base2, public Base3
{
public:
    void set_var1(int tmp) { var1 = tmp; }
    void set_var2(int tmp) { var2 = tmp; }
    void set_var3(int tmp) { var3 = tmp; }
    void set_var4(int tmp) { var4 = tmp; }

private:
    int var4;
};

int main()
{
    Derive d;
    return 0;
}

unique_ptr<string> p2(p1.release());
unique_ptr<string> p3.reset(p2.release());