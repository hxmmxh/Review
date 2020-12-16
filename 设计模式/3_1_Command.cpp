#include <iostream>
using namespace std;

// 抽象命令类
class Command
{
public:
    virtual void execute() = 0;
};

// 接收者
class Receiver
{
public:
    void action()
    {
        cout << "receiver action." << endl;
    }
};

// 具体命令类
class ConcreteCommand : public Command
{

public:
    ConcreteCommand(Receiver *pReceiver)
    {
        m_pReceiver = pReceiver;
    }
    virtual void execute()
    {
        cout << "ConcreteCommand::execute" << endl;
        m_pReceiver->action();
    }

private:
    Receiver *m_pReceiver;
};

// 调用者
class Invoker
{

public:
    Invoker(Command *pCommand)
    {
        m_pCommand = pCommand;
    }
    void call()
    {
        cout << "invoker calling" << endl;
        m_pCommand->execute();
    }

private:
    Command *m_pCommand;
};

int main(int argc, char *argv[])
{
    Receiver *pReceiver = new Receiver();
    ConcreteCommand *pCommand = new ConcreteCommand(pReceiver);
    Invoker *pInvoker = new Invoker(pCommand);
    pInvoker->call();

    delete pReceiver;
    delete pCommand;
    delete pInvoker;
    return 0;
}

// 命令接口
class Order
{
    virtual void execute() = 0;
};

// 接收者，实际执行命令
class Stock
{
public:
    void buy()
    {
        cout << "Stock [ Name: " << name << ", Quantity: "
             << quantity << " ] bought" << endl;
    }
    void sell()
    {
        cout << "Stock [ Name: " << name << ", Quantity: "
             << quantity << " ] sold" << endl;
    }

private:
    string name = "ABC";
    int quantity = 10;
};

//具体的命令接口
class BuyStock : public Order
{
public:
    BuyStock(Stock a) : abcstock(a) {}
    void execute()
    {
        abcstock.buy();
    }
private:
    Stock abcstock;
};

class SellStock : public Order
{
public:
    SellStock(Stock a) : abcstock(a) {}
    void execute()
    {
        abcstock.sell();
    }
private:
    Stock abcstock;
};

// 调用者
class Broder
{
    
};