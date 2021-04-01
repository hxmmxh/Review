#include <iostream>
#include <string>
using namespace std;
//1. 为电视创建一个接口
class TV
{
public:
    virtual void watch() = 0;
};

//2. 创建实现接口的实体类
class HaierTV : public TV
{
public:
    void watch() override
    {
        cout << "Haier TV\n";
    }
};

class XiaomiTV : public TV
{
public:
    void watch() override
    {
        cout << "Xiaomi TV\n";
    }
};

class HuaweiTV : public TV
{
public:
    void watch() override
    {
        cout << "Huawei TV\n";
    }
};

//3.为手机创建一个接口
class Phone
{
public:
    virtual void call() = 0;
};

//4. 创建实现接口的实体类
class HaierPhone : public Phone
{
public:
    void call() override
    {
        cout << "Haier Phone\n";
    }
};

class XiaomiPhone : public Phone
{
public:
    void call() override
    {
        cout << "Xiaomi Phone\n";
    }
};

class HuaweiPhone : public Phone
{
public:
    void call() override
    {
        cout << "Huawei Phone\n";
    }
};

//5.创建抽象类来获取工厂
class AbstractFactory
{
public:
    virtual TV *createTV() = 0;
    virtual Phone *createPhone() = 0;
};

//6. 创建扩展了 AbstractFactory 的工厂类，基于给定的信息生成实体类的对象。
class HaierFactory : public AbstractFactory
{
public:
    TV *createTV() override
    {
        return new HaierTV();
    }
    Phone *createPhone() override
    {
        return new HaierPhone();
    }
};

class XiaomiFactory : public AbstractFactory
{
public:
    TV *createTV() override
    {
        return new XiaomiTV();
    }
    Phone *createPhone() override
    {
        return new XiaomiPhone;
    }
};

class HuaweiFactory : public AbstractFactory
{
public:
    TV *createTV() override
    {
        return new HuaweiTV();
    }
    Phone *createPhone() override
    {
        return new HuaweiPhone;
    }
};

//7. 创建一个工厂创造器/生成器类，通过传递形状或颜色信息来获取工厂。
class FactoryProducer
{
public:
    static AbstractFactory *getFactory(string choice)
    {
        if (choice == "Haier")
            return new HaierFactory();
        else if (choice == "Xiaomi")
            return new XiaomiFactory();
        else if (choice == "Huawei")
            return new HuaweiFactory();
    }
};

//8.使用 FactoryProducer 来获取 AbstractFactory，通过传递类型信息来获取实体类的对象。
int main()
{
    AbstractFactory *haierFactory = FactoryProducer::getFactory("Haier");
    TV *pa1 = haierFactory->createTV();
    Phone *pb1 = haierFactory->createPhone();
    AbstractFactory *XiaomiFactory = FactoryProducer::getFactory("Xiaomi");
    TV *pa2 = XiaomiFactory ->createTV();
    Phone *pb2 = XiaomiFactory ->createPhone();
    AbstractFactory *HuaweiFactory = FactoryProducer::getFactory("Huawei");
    TV *pa3 = HuaweiFactory ->createTV();
    Phone *pb3 = HuaweiFactory ->createPhone();
    pa1->watch();
    pb1->call();
    pa2->watch();
    pb2->call();
    pa3->watch();
    pb3->call();
}