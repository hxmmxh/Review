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

//3. 创建一个工厂，生成基于给定信息的实体类的对象
class ShapeFactory
{
public:
    //使用 getShape 方法获取形状类型的对象
    Shape *getShape(string shapeType)
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
};

//4. 使用该工厂，通过传递类型信息来获取实体类的对象
int main()
{
    ShapeFactory factory;
    Shape *p1 = factory.getShape("CIRCLE");
    Shape *p2 = factory.getShape("RECTANGLE");
    Shape *p3 = factory.getShape("SQUARE");
    p1->draw();
    p2->draw();
    p3->draw();
}