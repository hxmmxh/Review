#include <iostream>
using namespace std;

class Context;

// 抽象状态类
class State
{
public:
    virtual void handle(Context *c) = 0;
};

// 具体状态类
class ConcreteStateA : public State
{

public:
    virtual ~ConcreteStateA();

    static State *Instance()
    {
        if (NULL == m_pState)
        {
            m_pState = new ConcreteStateA();
        }
        return m_pState;
    }

    virtual void handle(Context *c)
    {
        cout << "doing something in State A.\n done,change state to B" << endl;
        c->changeState(ConcreteStateB::Instance());
    }

private:
    ConcreteStateA();
    static State *m_pState;
};
State *ConcreteStateA::m_pState = NULL;

class ConcreteStateB : public State
{

public:
    static State *Instance()
    {
        if (NULL == m_pState)
        {
            m_pState = new ConcreteStateB();
        }
        return m_pState;
    }
    virtual void handle(Context *c)
    {
        cout << "doing something in State B.\n done,change state to A" << endl;
        c->changeState(ConcreteStateA::Instance());
    }

private:
    ConcreteStateB();
    static State *m_pState;
};

State *ConcreteStateB::m_pState = NULL;

// 环境类
class Context
{
public:
    Context()
    {
        // 初始状态设为A
        m_pState = ConcreteStateA::Instance();
    }
    virtual ~Context();

    void changeState(State *st)
    {
        m_pState = st;
    }
    void request()
    {
        m_pState->handle(this);
    }

private:
    State *m_pState;
};

int main(int argc, char *argv[])
{
    Context *c = new Context();
    c->request();
    c->request();
    c->request();

    delete c;
    return 0;
}
