#include <mutex>

using namespace std;
class Singleton
{
public:
    static Singleton* getSingleton()
    {
        if (value == nullptr)
        {
            std::lock_guard<mutex> guard(_mutex);
            if(value==nullptr)
                value = new Singleton();
        }
        return value;
    }

private:
    Singleton();
    static mutex _mutex;
    static Singleton *value;
};