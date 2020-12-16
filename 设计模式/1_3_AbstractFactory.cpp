#include <iostream>
#include <string>
using namespace std;
//1. 为形状创建一个接口
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

//3.为颜色创建一个接口
class Color
{
public:
    virtual void fill() = 0;
};

//4. 创建实现接口的实体类
class Red : public Color
{
public:
    void fill() override
    {
        cout << "RED\n";
    }
};

class Blue : public Color
{
public:
    void fill() override
    {
        cout << "BLUE\n";
    }
};

class Green : public Color
{
public:
    void fill() override
    {
        cout << "GREEN\n";
    }
};

//5.创建抽象类来获取工厂
class AbstractFactory
{
public:
    virtual Color *getColor(string) = 0;
    virtual Shape *getShape(string) = 0;
};

//6. 创建扩展了 AbstractFactory 的工厂类，基于给定的信息生成实体类的对象。
class ShapeFactory : public AbstractFactory
{
public:
    Shape *getShape(string shapeType) override
    {

        if (shapeType == "CIRCLE")
        {
            return new Circle();
        }
        else if (shapeType == "RECTANGLE")
        {
            return new Rectangle();
        }
        else if (shapeType == "SQUARE")
        {
            return new Square();
        }
        return nullptr;
    }
    Color *getColor(string) override
    {
        return nullptr;
    }
};

class ColorFactory : public AbstractFactory
{
public:
    Shape *getShape(string shapeType) override
    {
        return nullptr;
    }
    Color *getColor(string colorType) override
    {
        if (colorType == "RED")
            return new Red();
        else if (colorType == "BLUE")
            return new Blue();
        else if (colorType == "GREEN")
            return new Green();
        return nullptr;
    }
};

//7. 创建一个工厂创造器/生成器类，通过传递形状或颜色信息来获取工厂。
class FactoryProducer
{
public:
    static AbstractFactory *getFactory(string choice)
    {
        if (choice == "SHAPE")
            return new ShapeFactory();
        else if (choice == "COLOR")
            return new ColorFactory();
    }
};

//8.使用 FactoryProducer 来获取 AbstractFactory，通过传递类型信息来获取实体类的对象。
int main()
{
    AbstractFactory *shapefactory = FactoryProducer::getFactory("SHAPE");
    Shape *p1 = shapefactory->getShape("CIRCLE");
    Shape *p2 = shapefactory->getShape("RECTANGLE");
    Shape *p3 = shapefactory->getShape("SQUARE");
    p1->draw();
    p2->draw();
    p3->draw();
    AbstractFactory *colorfactory = FactoryProducer::getFactory("COLOR");
    Color *q1 = colorfactory->getColor("RED");
    Color *q2 = colorfactory->getColor("BLUE");
    Color *q3 = colorfactory->getColor("GREEN");
    q1->fill();
    q2->fill();
    q3->fill();
}