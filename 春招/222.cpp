#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N;
    cin >> N;
    string l;
    getline(cin, l);
    unordered_map<string, unordered_set<string>> all;
    for (int i = 0; i < N; ++i)
    {
        string line;
        getline(cin, line);
        int pos = 0;
        while (line[pos] == ' ')
            ++pos;
        int start = pos;
        while (line[pos] != ' ')
            ++pos;
        string key = line.substr(start, pos - start);
        all[key].insert(key);
        while (line[pos] == ' ')
            ++pos;
        start = pos;
        while (pos < line.size())
        {
            if (line[pos] == ' ')
            {
                string word = line.substr(start, pos - start);
                all[word].insert(key);
                while (line[pos] == ' ')
                    ++pos;
                start = pos;
            }
            else
                ++pos;
        }
        string word = line.substr(start, pos - start);
        all[word].insert(key);
    }
    unordered_map<string, int> ok;
    for (auto it = all.begin(); it != all.end(); ++it)
    {
        auto mss = it->first;
        ok[mss] = 0;
    }
    cin >> N;
    for (int i = 0; i < N; ++i)
    {
        string s;
        cin >> s;
        if (!ok[s])
        {
            auto ms = all[s];
            for (auto it = ms.begin(); it != ms.end(); ++it)
            {
                auto mss = all[*it];
                for (auto it = mss.begin(); it != mss.end(); ++it)
                    ms.insert(*it);
            }
        }
        cout << all[s].size();
    }
}

void makeok(unordered_map<string,unordered_set<string>> &all)
{
    
}