/*我们假设一个快餐店的商业案例，其中，一个典型的套餐可以是一个汉堡（Burger）和一杯冷饮（Cold drink）。汉
堡（Burger）可以是素食汉堡（Veg Burger）或鸡肉汉堡（Chicken Burger），它们是包在纸盒中。
冷饮（Cold drink）可以是可口可乐（coke）或百事可乐（pepsi），它们是装在瓶子中。
我们将创建一个表示食物条目（比如汉堡和冷饮）的 Item 接口和实现 Item 接口的实体类，
以及一个表示食物包装的 Packing 接口和实现 Packing 接口的实体类，汉堡是包在纸盒中，冷饮是装在瓶子中。
然后我们创建一个 Meal 类，带有 Item 的 ArrayList 和一个通过结合 Item 来创建不同类型的 Meal 对象的 MealBuilder。
BuilderPatternDemo，我们的演示类使用 MealBuilder 来创建一个 Meal。
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

//1. 创建一个表示食物条目和食物包装的接口。
class Packing
{
public:
    virtual string pack() = 0;
};

class Item
{
public:
    virtual string name() = 0;
    virtual Packing *packing() = 0;
    virtual float price() = 0;
};

//2.创建实现 Packing 接口的实体类。

class Wrapper : public Packing
{
public:
    string pack() override
    {
        return "Wrapper";
    }
};

class Bottle : public Packing
{
public:
    string pack() override
    {
        return "Bottle";
    }
};

//3.创建实现 Item 接口的抽象类，该类提供了默认的功能。

class Burger : public Item
{
    Packing *packing() override
    {
        return new Wrapper();
    }
};

class ColdDrink : public Item
{
    Packing *packing() override
    {
        return new Bottle();
    }
};

//4. 创建扩展了 Burger 和 ColdDrink 的实体类。
class VegBurger : public Burger
{
    string name() override
    {
        return "VegBurger";
    }
    float price() override
    {
        return 25.0f;
    }
};

class ChikenBurger : public Burger
{
    string name() override
    {
        return "ChikenBurder";
    }
    float price() override
    {
        return 50.0f;
    }
};

class Coke : public ColdDrink
{
    string name() override
    {
        return "Coke";
    }
    float price() override
    {
        return 30.0f;
    }
};

class Pepsi : public ColdDrink
{
    string name() override
    {
        return "Pepsi";
    }
    float price() override
    {
        return 35.0f;
    }
};

//5. 创建一个 Meal 类，带有上面定义的 Item 对象。
class Meal
{
public:
    void addItem(Item *i)
    {
        items.push_back(i);
    }
    float getCost()
    {
        float cost = 0.0;
        for (auto i : items)
            cost += i->price();
        return cost;
    }
    void showItems()
    {
        for (auto i : items)
        {
            cout << "Item: " << i->name() << ','
                 << "Packing: " << i->packing()->pack() << ','
                 << "Price: " << i->price() << endl;
        }
    }

private:
    vector<Item *> items;
};

//6. 创建一个 MealBuilder 类，实际的 builder 类负责创建 Meal 对象
class MealBuilder
{
public:
    Meal *prepareVegMeal()
    {
        Meal *meal = new Meal();
        meal->addItem(new VegBurger());
        meal->addItem(new Coke());
        return meal;
    }
    Meal *prepareChikenMeal()
    {
        Meal *meal = new Meal();
        meal->addItem(new ChikenBurger());
        meal->addItem(new Pepsi());
        return meal;
    }
};

//7.使用 MealBuider 来演示建造者模式（Builder Pattern）。
int main()
{
    MealBuilder *mb = new MealBuilder();
    Meal *vegMeal = mb->prepareVegMeal();
    cout << "Veg Meal: \n";
    vegMeal->showItems();
    cout << "Total Cost: " << vegMeal->getCost()<<endl;

    Meal *chikenMeal = mb->prepareChikenMeal();
    cout << "Chiken Meal: \n";
    chikenMeal->showItems();
    cout << "Total Cost: " << chikenMeal->getCost();

}