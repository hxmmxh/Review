#include <mutex>

using namespace std;
#include <iostream>

using namespace std;

// 1. 懒汉式
class Singleton1
{
public:
    static Singleton1 *GetInstance()
    {
        if (m_pSingleton1 == NULL)
            m_pSingleton1 = new Singleton1();
        return m_pSingleton1;
    }

private:
    Singleton1() {} // 构造函数（被保护）
private:
    static Singleton1 *m_pSingleton1; // 指向单例对象的指针
};

// 2. 懒汉式，加锁，线程安全
class Singleton2
{
public:
    static Singleton2 *getSingleton2()
    {
        std::lock_guard<mutex> guard(_mutex);
        if (value2 == nullptr)
        {
            value2 = new Singleton2();
        }
        return value2;
    }

private:
    // 让构造函数是私有的，保证不会被实例化
    Singleton2();
    static mutex _mutex;
    static Singleton2 *value2;
};
// 3.饿汉式
class Singleton3
{
public:
    static Singleton3 *GetInstance()
    {
        return m_pSingleton3;
    }

private:
    Singleton3() {} // 构造函数（被保护）
private:
    static Singleton3 *m_pSingleton3; // 指向单例对象的指针
};
Singleton3 *Singleton3::m_pSingleton3 = new Singleton3();

// 4. 双重锁(DCL)单例对象类
class Singleton4
{
public:
    static Singleton4 *getSingleton()
    {
        if (value == nullptr)
        {
            std::lock_guard<mutex> guard(_mutex);
            if (value == nullptr)
                value = new Singleton4();
        }
        return value;
    }

private:
    // 让构造函数是私有的，保证不会被实例化
    Singleton4();
    static mutex _mutex;
    static Singleton4 *value;
};

//5. 局部静态变量
// 为了防止在Singleton single = Singleton::GetInstance()时发生拷贝，违背单例的特性
// 方法1：将 GetInstance() 函数的返回类型修改为指针
class Singleton
{
public:
    // 修改返回类型为指针类型
    static Singleton *GetInstance()
    {
        static Singleton instance;
        return &instance;
    }

private:
    Singleton() {}
};
// 方法2： 显式地声明类的拷贝构造函数，并重载赋值运算符
// 这样的话，需要用下面的方式使用这个单例
// Singleton::GetInstance().doSomething(); // OK
// Singleton single = Singleton::GetInstance(); // Error 不能编译通过
class Singleton
{
public:
    static Singleton &GetInstance()
    {
        static Singleton instance;
        return instance;
    }
    void doSomething()
    {
        cout << "Do something" << endl;
    }

private:
    Singleton() {}                           // 构造函数（被保护）
    Singleton(Singleton const &);            // 无需实现
    Singleton &operator=(const Singleton &); // 无需实现
};

// 6. pthread_once方法
class Singleton
{
public:
    static Singleton *getInstance()
    { //pthread_once所注册的函数在多线程环境下只会被执行一次
        //线程安全的
        pthread_once(&_once, init);
        return _pInstance;
    }

    static void init()
    {
        _pInstance = new Singleton;
        atexit(destroy);//进程终止处理程序
    }

    static void destroy()
    {
        if (_pInstance)
            delete _pInstance;
    }

private:
    Singleton() { cout << "Singleton()" << endl; }
    ~Singleton() { cout << "~Singleton()" << endl; }

private:
    static Singleton *_pInstance;
    static pthread_once_t _once;
};
//静态数据成员的初始化
Singleton * Singleton::_pInstance = NULL;//饿(懒)汉模式  --> 懒加载
pthread_once_t Singleton::_once = PTHREAD_ONCE_INIT;