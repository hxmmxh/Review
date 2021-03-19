#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <queue>

using namespace std;

int checkCPUendian()
{
    union
    {
        unsigned int a;
        unsigned char b;
    } c;
    c.a = 1;
    return (c.b == 1);

} /*return 1 : little-endian, return 0:big-endian*/

int main()
{
    if(checkCPUendian())
        cout << "Xiao";
}