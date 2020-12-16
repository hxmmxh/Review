#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Subject;

// 观察者接口
class Obeserver
{
public:
    virtual void update(Subject *sub) = 0;
};

// 具体观察者
// 观察者都包含有一个update函数，会用到被观测对象传递过来的信息
// 目标对象状态发生改变时就会调用这个update函数
class ConcreteObeserver : public Obeserver
{
public:
    ConcreteObeserver(string name) : m_objName(name) {}
    virtual void update(Subject *sub);
private:
    string m_objName;
    int m_obeserverState;
};

// 目标接口
class Subject
{
public:
    void attach(Obeserver *pObeserver)
    {
        m_vtObj.push_back(pObeserver);
    }
    void detach(Obeserver *pObeserver)
    {
        for (vector<Obeserver *>::iterator itr = m_vtObj.begin();
             itr != m_vtObj.end(); itr++)
        {
            if (*itr == pObeserver)
            {
                m_vtObj.erase(itr);
                return;
            }
        }
    }
    void notify()
    {
        for (vector<Obeserver *>::iterator itr = m_vtObj.begin();
             itr != m_vtObj.end();
             itr++)
        {
            // 调用观察者自己的update函数
            (*itr)->update(this);
        }
    }
    virtual int getState() = 0;
    virtual void setState(int i) = 0;

private:
    vector<Obeserver *> m_vtObj;
};

// 具体目标
class ConcreteSubject : public Subject
{
public:
    virtual int getState()
    {
        return m_nState;
    }
    virtual void setState(int i)
    {
        m_nState = i;
        // 状态发生改变自动通知所有观察者
        notify();
    }

private:
    int m_nState;
};

void ConcreteObeserver::update(Subject *sub)
{
    m_obeserverState = sub->getState();
    cout << "update oberserver[" << m_objName << "] state:" << m_obeserverState << endl;
}

int main(int argc, char *argv[])
{
    Subject *subject = new ConcreteSubject();
    Obeserver *objA = new ConcreteObeserver("A");
    Obeserver *objB = new ConcreteObeserver("B");
    subject->attach(objA);
    subject->attach(objB);

    subject->setState(1);

    cout << "--------------------" << endl;
    subject->detach(objB);
    subject->setState(2);

    delete subject;
    delete objA;
    delete objB;

    return 0;
}

