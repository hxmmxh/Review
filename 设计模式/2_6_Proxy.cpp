#include <iostream>
#include <string>
using namespace std;

// 抽象主题角色
class Subject
{
public:
    virtual void request() = 0;
};

// 真实主题角色
class RealSubject : public Subject
{

public:
    void request()
    {
        cout << "RealSubject::request" << endl;
    }
};

// 代理主题角色
class Proxy : public Subject
{

public:
    Proxy()
    {
        m_pRealSubject = new RealSubject();
    }
    virtual ~Proxy()
    {
        delete m_pRealSubject;
    }

    void request()
    {
        preRequest();
        m_pRealSubject->request();
        afterRequest();
    }

private:
    void afterRequest()
    {
        cout << "Proxy::afterRequest" << endl;
    }
    void preRequest()
    {
        cout << "Proxy::preRequest" << endl;
    }
    RealSubject *m_pRealSubject;
};

// 抽象主题角色
class Image
{
public:
    virtual void display() = 0;
};

// 真实主题角色
class RealImage : public Image
{
public:
    RealImage(string filename) : fileName(filename)
    {
        loadFromDisk(filename);
    }
    void display()
    {
        cout << "Displaying " + fileName << endl;
    }

private:
    void loadFromDisk(string f)
    {
        cout << "Loading " << f << endl;
    }
    string fileName;
};

class ProxyImage : public Image
{
public:
    ProxyImage(string s) : fileName(s),realImage(nullptr) {}
    void display() override
    {
        if (realImage == nullptr)
        {
            realImage = new RealImage(fileName);
        }
        realImage->display();
    }

private:
    RealImage *realImage;
    string fileName;
};


int main(int argc, char *argv[])
{
    Proxy proxy;
    proxy.request();

    Image* image = new ProxyImage("test_10mb.jpg");
    image->display();
    image->display();
    return 0;
}
