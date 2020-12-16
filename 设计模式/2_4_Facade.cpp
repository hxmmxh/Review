#include <iostream>

using namespace std;

// 子系统
class SystemA
{
public:
    void operationA()
    {
        cout << "operationA" << endl;
    }
};

class SystemB
{
public:
    void operationB()
    {
        cout << "operationB" << endl;
    }
};

class SystemC
{
public:
    void operationC()
    {
        cout << "operationC" << endl;
    }
};

// 外观类
class Facade
{
public:
    Facade()
    {
        m_SystemA = new SystemA();
        m_SystemB = new SystemB();
        m_SystemC = new SystemC();
    }
    ~Facade()
    {
        delete m_SystemA;
        delete m_SystemB;
        delete m_SystemC;
    }
    void wrapOpration()
    {
        m_SystemA->operationA();
        m_SystemB->operationB();
        m_SystemC->operationC();
    }

private:
    SystemC *m_SystemC;
    SystemA *m_SystemA;
    SystemB *m_SystemB;
};

// 子系统的接口
class Shape
{
public:
    virtual void draw() = 0;
};

// 子系统的实例
class Rectangle : public Shape
{
public:
    virtual void draw()
    {
        cout << "Rectangle::draw()" << endl;
    }
};

class Square : public Shape
{
public:
    virtual void draw()
    {
        cout << "Square::draw()" << endl;
    }
};

class Circle : public Shape
{
public:
    virtual void draw()
    {
        cout << "Circle::draw()" << endl;
    }
};

// 外观类

class ShapeMaker
{
public:
    ShapeMaker()
    {
        circle = new Circle();
        rectangle = new Rectangle();
        square = new Square();
    }
    ~ShapeMaker()
    {
        delete circle;
        delete rectangle;
        delete square;
    }
    void drawCircle()
    {
        circle->draw();
    }
    void drawRectangle()
    {
        rectangle->draw();
    }
    void drawSquare()
    {
        square->draw();
    }

private:
    Shape *circle;
    Shape *rectangle;
    Shape *square;
};

int main()
{
    Facade fa;
    fa.wrapOpration();

    ShapeMaker shapeMaker;
    shapeMaker.drawCircle();
    shapeMaker.drawRectangle();
    shapeMaker.drawSquare();

    return 0;
}