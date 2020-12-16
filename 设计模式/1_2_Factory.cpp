#include <iostream>
#include <string>

using namespace std;

//1. 创建一个接口
class Shape
{
public:
    virtual void draw() = 0;
};

//2. 创建实现接口的实体类
class Rectangle : public Shape
{
public:
    void draw() override
    {
        cout << "Rectangle\n";
    }
};

class Square : public Shape
{
public:
    void draw() override
    {
        cout << "Square\n";
    }
};

class Circle : public Shape
{
public:
    void draw() override
    {
        cout << "Circle\n";
    }
};

//3.虚拟工厂类
class ShapeFactory
{
public:
    virtual Shape *getShape() = 0;
};

// 4. 具体工厂类
class RectangleFactory : public ShapeFactory
{
public:
    Shape *getShape()
    {
        return new Rectangle();
    }
};

class SquareFactory : public ShapeFactory
{
public:
    Shape *getShape()
    {
        return new Square();
    }
};

class CircleFactory : public ShapeFactory
{
public:
    Shape *getShape()
    {
        return new Circle();
    }
};

//5.使用工厂

int main()
{
    ShapeFactory *CFactory = new CircleFactory();
    ShapeFactory *RFactory = new RectangleFactory();
    ShapeFactory *SFactory = new SquareFactory();
    Shape *p1 = CFactory->getShape();
    Shape *p2 = RFactory->getShape();
    Shape *p3 = SFactory->getShape();
    p1->draw();
    p2->draw();
    p3->draw();
}
