#include <iostream>

using namespace std;

class Target
{
public:
    virtual void request()
    {
        cout << "this is original request " << endl;
    }
};

// 适配者
class Adaptee
{
public:
    void specificRequest()
    {
        cout << "specificRequest()|this is real Request from Adaptee!" << endl;
    }
};

// 对象适配器
class Adapter1 : public Target
{
public:
    Adapter1(Adaptee *adaptee)
    {
        m_pAdaptee = adaptee;
    }
    virtual void request()
    {
        m_pAdaptee->specificRequest();
    }
private:
    Adaptee *m_pAdaptee;
};

// 类适配器，采用多重继承
// 公共继承接口，私有继承适配者
class Adapter2 : public Target, Adaptee
{
public:
    virtual void request()
    {
        specificRequest();
    }
};

int main(int argc, char *argv[])
{
    Adaptee *adaptee = new Adaptee();
    Target *tar1 = new Adapter1(adaptee);
    tar1->request();
    Target *tar2 = new Adapter2();
    tar2->request();
    return 0;
}



