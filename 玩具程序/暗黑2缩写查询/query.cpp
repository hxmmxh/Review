#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

int main()
{
    string file = "input.txt";
    ifstream input(file);
    map<string, string> database;
    string line;
    while (getline(input, line))
    {
        istringstream record(line);
        string key, value;
        record >> key;
        record >> value;
        database[key] = value;
    }
    cout<<"qqq为退出指令\n";
    while(true)
    { 
    cout << "请输入要查询的缩写:";
    string name;
    cin >> name;
    for(auto &c : name)
        c= tolower(c);
    if(name=="qqq")
         break;
    if (database.find(name) == database.end())
        cout << "不存在！！" << endl;
    else
        cout << database[name] << endl;
    }
    // cout << "按任意键退出\n"    
    system("pause");//会自己显示”按任意键继续“
}    


