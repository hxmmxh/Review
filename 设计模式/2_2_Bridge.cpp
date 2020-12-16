#include <iostream>

using namespace std;

// 实现类接口
class Implementor
{
public:
    virtual void operationImp() = 0;
};

// 具体实现类
class ConcreteImplementorA : public Implementor
{
public:
    virtual void operationImp()
    {
        cout << "imp in ConcreteImplementorA style." << endl;
    }
};

class ConcreteImplementorB : public Implementor
{
public:
    virtual void operationImp()
    {
        cout << "imp in ConcreteImplementorB style." << endl;
    }
};

// 抽象类，包含有实现类的成员
class Abstraction
{
public:
    virtual ~Abstraction()
    {
        delete m_pImp;
    }
    Abstraction(Implementor *imp)
    {
        m_pImp = imp;
    }
    virtual void operation() = 0;

protected:
    Implementor *m_pImp;
};

// 扩展抽象类，扩充抽象类的操作
class RefinedAbstraction : public Abstraction
{
public:
    RefinedAbstraction(Implementor *imp) : Abstraction(imp) {}
    virtual ~RefinedAbstraction() {}
    virtual void operation()
    {
        cout << "do something else ,and then " << endl;
        m_pImp->operationImp();
    }
};

// 实现类接口
class DrawAPI
{
public:
    virtual void drawCircle(int radius) = 0;
};

// 具体实现类
class RedCircle : public DrawAPI
{
public:
    void drawCircle(int radius)
    {
        cout << "Drawing Circle[ color: red, radius: " << radius << endl;
    }
};

class GreenCircle : public DrawAPI
{
public:
    void drawCircle(int radius)
    {
        cout << "Drawing Circle[ color: green, radius: " << radius << endl;
    }
};

// 抽象类，包含有实现类的成员
class Shape
{
public:
    Shape(DrawAPI *d, int r)
    {
        drawAPI = d;
        raduis = r;
    }
    virtual void draw() = 0;

protected:
    DrawAPI *drawAPI;
    int raduis;
};

// 扩展抽象类，扩充抽象类的操作
class Circle : public Shape
{
public:
    Circle(DrawAPI *d, int r) : Shape(d, r) {}
    void draw()
    {
        drawAPI->drawCircle(raduis);
    }
};

int main(int argc, char *argv[])
{
    Implementor *pImp = new ConcreteImplementorA();
    Abstraction *pa = new RefinedAbstraction(pImp);
    pa->operation();

    Abstraction *pb = new RefinedAbstraction(new ConcreteImplementorB());
    pb->operation();

    delete pa;
    delete pb;

    Shape *redCircle = new Circle(new RedCircle(), 100);
    Shape *greenCircle = new Circle(new GreenCircle(), 10);

    redCircle->draw();
    greenCircle->draw();

    return 0;
}