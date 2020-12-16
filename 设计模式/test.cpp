#include <iostream>
#include <string>

using namespace std;

// 抽象基类
class Product
{
public:
	virtual void Use() = 0;
};
// 实例A
class ConcreteProductA : public Product
{
public:
	virtual void Use();
};
void ConcreteProductA::Use()
{
	cout << "use productA" << endl;	
}
// 实例B
class ConcreteProductB : public Product
{
public:
	ConcreteProductB();
	virtual ~ConcreteProductB();
	virtual void Use();
};
void ConcreteProductB::Use()
{
	cout << "use productA" << endl;	
}
// 工厂
class Factory
{
public:
	Factory();
	virtual ~Factory();
	static Product * createProduct(string proname);
};
Product* Factory::createProduct(string proname){
	if ( "A" == proname )
	{
		return new ConcreteProductA();
	}
	else if("B" == proname)
	{
		return new ConcreteProductB();
	}
	return  NULL;
}
// 主函数
int main(int argc, char *argv[])
{
	Product * proda = Factory::createProduct("A");
	proda->Use();
    Product * prodb = Factory::createProduct("B");
	prodb->Use();
	delete proda;
    delete prodb;
	return 0;
}