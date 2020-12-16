#include <iostream>
#include <string>
#include <map>

using namespace std;

class Colleague;

// 抽象中介者
class Mediator
{
public:
    virtual void operation(int nWho, string str) = 0;
    virtual void registered(int nWho, Colleague *aColleague) = 0;
};

// 抽象同事类
// 每一个同事对象都引用一个中介者对象
class Colleague
{
public:
    virtual void receivemsg(string str)
    {
        cout << "reveivemsg:" << str << endl;
    }
    virtual void sendmsg(int toWho, string str) = 0;
    void setMediator(Mediator *aMediator)
    {
        m_pMediator = aMediator;
    }

protected:
    Mediator *m_pMediator;
};

// 具体中介者
// 中介者关联了各个同事对象
class ConcreteMediator : public Mediator
{
public:
    virtual void operation(int nWho, string str)
    {
        map<int, Colleague *>::const_iterator itr = m_mpColleague.find(nWho);
        if (itr == m_mpColleague.end())
        {
            cout << "not found this colleague!" << endl;
            return;
        }

        Colleague *pc = itr->second;
        pc->receivemsg(str);
    }
    virtual void registered(int nWho, Colleague *aColleague)
    {
        map<int, Colleague *>::const_iterator itr = m_mpColleague.find(nWho);
        if (itr == m_mpColleague.end())
        {
            m_mpColleague.insert(make_pair(nWho, aColleague));
            //同时将中介类暴露给colleague
            aColleague->setMediator(this);
        }
    }

private:
    map<int, Colleague *> m_mpColleague;
};

// 具体同事类
class ConcreteColleagueA : public Colleague
{
public:
    virtual void sendmsg(int toWho, string str)
    {
        cout << "send msg from colleagueA,to:" << toWho << endl;
        m_pMediator->operation(toWho, str);
    }
    virtual void receivemsg(string str)
    {
        cout << "ConcreteColleagueA reveivemsg:" << str << endl;
    }
};

class ConcreteColleagueB : public Colleague
{
public:
    virtual void sendmsg(int toWho, string str)
    {
        cout << "send msg from colleagueB,to:" << toWho << endl;
        m_pMediator->operation(toWho, str);
    }
    virtual void receivemsg(string str)
    {
        cout << "ConcreteColleagueB reveivemsg:" << str << endl;
    }
};

// 同事类
class User
{
public:
    User(string n) : name(n) {}
    string getname()
    {
        return name;
    }
    void setname(string n)
    {
        name = n;
    }
    void sendMessage(string m);

private:
    string name;
};

// 中介者
class ChatRoom
{
public:
    static void showMessage(User *user, string message)
    {
        cout << "[" << user->getname() << "]" << message;
    }
};

void User::sendMessage(string m)
{
    ChatRoom::showMessage(this, m);
}

int main(int argc, char *argv[])
{
    ConcreteColleagueA *pa = new ConcreteColleagueA();
    ConcreteColleagueB *pb = new ConcreteColleagueB();
    ConcreteMediator *pm = new ConcreteMediator();
    pm->registered(1, pa);
    pm->registered(2, pb);

    // sendmsg from a to b
    pa->sendmsg(2, "hello,i am a");
    // sendmsg from b to a
    pb->sendmsg(1, "hello,i am b");

    delete pa, pb, pm;

    User* robert = new User("Robert");
    User* John = new User("John");
    robert->sendMessage("Hi! John!");
    John->sendMessage("Hi! Robert");

    return 0;
}