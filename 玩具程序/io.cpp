#include <iostream>
#include <map>
#include <fstream>
using namespace std;

void getmes(string data, string &key, string &value)
{
    int st = 0, en = 0;
    while (data[en] != '\t')
        ++en;
    key = data.substr(st, en - st);
    ++en;
    st = en;
    while (en < data.size() && data[en] != '\t')
        ++en;
    value = data.substr(st, en - st);
}

int main()
{
    map<string, string> list;
    string file1 = "input1.txt", file2 = "input2.txt";
    ifstream input1(file1), input2(file2);
    string data;
    while (getline(input1, data))
    {
        string key, value;
        getmes(data, key, value);
        list.insert({key, value});
    }
    while (getline(input2, data))
    {
        string key, value;
        getmes(data, key, value);
        if (list.find(key) == list.end())
            list.insert({key, value});
    }
    ofstream output("output.txt");
    for (auto beg = list.begin(); beg != list.end(); ++beg)
    {
        output << beg->first << '\t' << beg->second << '\n';
    }
}