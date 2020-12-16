#include <iostream>

using namespace std;

// 抽象构件
class Component
{
public:
    virtual void operation() = 0;
};

// 具体构建
class ConcreteComponent : public Component
{
public:
    void operation()
    {
        cout << "ConcreteComponent's normal operation!" << endl;
    }
};

// 抽象装饰类，也是抽象构件类的子类
// 并且也包含一个抽象构件
class Decorator : public Component
{
public:
    Decorator(Component *pcmp)
    {
        m_pComponent = pcmp;
    }
    void operation()
    {
        m_pComponent->operation();
    }

private:
    Component *m_pComponent;
};

// 具体装饰类
class ConcreteDecoratorA : public Decorator
{
public:
    ConcreteDecoratorA(Component *pcmp) : Decorator(pcmp) {}
    void addBehavior()
    {
        cout << "addBehavior AAAA" << endl;
    }
    virtual void operation()
    {
        Decorator::operation();
        addBehavior();
    }
};

class ConcreteDecoratorB : public Decorator
{
public:
    ConcreteDecoratorB(Component *pcmp) : Decorator(pcmp) {}
    void addBehavior()
    {
        cout << "addBehavior BBBB" << endl;
    }
    virtual void operation()
    {
        Decorator::operation();
        addBehavior();
    }
};

// 抽象构件
class Shape
{
public:
    virtual void draw() = 0;
};

// 具体构件
class Rectangle : public Shape
{
public:
    void draw()
    {
        cout << "Shape:Rectangle" << endl;
    }
};

class Circle : public Shape
{
public:
    void draw()
    {
        cout << "Shape:Circle" << endl;
    }
};

// 实现了 Shape 接口的抽象装饰类
class ShapeDecorator : public Shape
{
public:
    ShapeDecorator(Shape *s)
    {
        decoratedShape = s;
    }
    virtual void draw()=0;

protected:
    Shape *decoratedShape;
};

// 具体装饰类
class RedShapeDecorator : public ShapeDecorator
{
public:
    RedShapeDecorator(Shape *s) : ShapeDecorator(s) {}
    virtual void draw()
    {
        decoratedShape->draw();
        setRedBorder();
    }
    void setRedBorder()
    {
        cout << "Border Color: Red" << endl;
    }
};

int main(int argc, char *argv[])
{
    ConcreteComponent *pRealProd = new ConcreteComponent();
    Component *pA = new ConcreteDecoratorA(pRealProd);
    pA->operation();
    Component *pB = new ConcreteDecoratorB(pA);
    pB->operation();

    Shape *circle = new Circle();
    Shape *redCircle = new RedShapeDecorator(new Circle());
    Shape *redRectangle = new RedShapeDecorator(new Rectangle());
    circle->draw();
    redCircle->draw();
    redRectangle->draw();

    return 0;
}
