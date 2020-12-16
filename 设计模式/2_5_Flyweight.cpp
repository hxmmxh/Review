#include <iostream>
#include <string>
#include <map>
#include <stdlib.h>
#include <time.h>

using namespace std;

// 抽象享元类
class Flyweight
{
public:
    virtual void operation() = 0;
};

// 非共享的具体享元类
class UnsharedConcreteFlyweight : public Flyweight
{
public:
    void operation()
    {
    }

private:
    int allState;
};

// 共享的具体享元类
class ConcreteFlyweight : public Flyweight
{

public:
    ConcreteFlyweight(string str)
    {
        intrinsicState = str;
    }

    virtual void operation()
    {
        cout << "Flyweight[" << intrinsicState << "] do operation." << endl;
    }

private:
    string intrinsicState;
};

// 享元工厂类
class FlyweightFactory
{

public:
    Flyweight *getFlyweight(string str)
    {
        map<string, Flyweight *>::iterator itr = m_mpFlyweight.find(str);
        if (itr == m_mpFlyweight.end())
        {
            Flyweight *fw = new ConcreteFlyweight(str);
            m_mpFlyweight.insert(make_pair(str, fw));
            return fw;
        }
        else
        {
            cout << "aready in the pool,use the exist one:" << endl;
            return itr->second;
        }
    }

private:
    map<string, Flyweight *> m_mpFlyweight;
};

// 抽象享元类
class Shape
{
public:
    virtual void draw() = 0;
};

// 具体享元类
class Circle : public Shape
{
public:
    Circle(string c) : color(c) {}
    void setX(int x)
    {
        this->x = x;
    }
    void setY(int y)
    {
        this->y = y;
    }
    void setRadius(int r)
    {
        this->radius = r;
    }
    void draw() override
    {
        cout << "Circle:Draw() [Color : " << color << ", x:" << x
             << ", y:" << y << ",radius: " << radius << endl;
    }

private:
    string color;
    int x, y, radius;
};

// 享元工厂
class ShapeFactory
{
public:
    static Circle *getCircle(string color)
    {
        auto itr = circleMap.find(color);
        if (itr == circleMap.end())
        {
            Circle *circle = new Circle(color);
            circleMap.insert(make_pair(color, circle));
            cout << "Creating circle of color : " << color << endl;
            return circle;
        }
        else
        {
            cout << "aready in the pool,use the exist one:" << endl;
            return itr->second;
        }
    }
private:
    static map<string, Circle *> circleMap;
};

map<string, Circle *> ShapeFactory::circleMap;

int main(int argc, char *argv[])
{
    FlyweightFactory factory;
    Flyweight *fw = factory.getFlyweight("one");
    fw->operation();

    Flyweight *fw2 = factory.getFlyweight("two");
    fw2->operation();

    Flyweight *fw3 = factory.getFlyweight("one");
    fw3->operation();

    srand((unsigned int)time(NULL));
    string colors[] = {"Red", "Green", "Blue", "White", "Black"};
    for (int i = 0; i < 20; ++i)
    {
        Circle *circle = ShapeFactory::getCircle(colors[rand() % 5]);
        circle->setX(rand() % 100 + 1);
        circle->setY(rand() % 100 + 1);
        circle->setRadius(100);
        circle->draw();
    }

    return 0;
}