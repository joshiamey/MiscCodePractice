#include <iostream>
#include <map>
#include <string>
#include <list>
#include <fstream>
using namespace std;

struct Node
{
    int value;
    int key;
    Node(int k, int val) : key(k), value(val){};  
};

class Cache
{

protected:
    map<int, list<Node>::iterator> mp;            // map the key to the node in the linked list
int cp;                                          // capacity
    list<Node> cache_list;                       // cache list
    virtual void set(int, int) = 0;             // set function
    virtual int get(int) = 0;                   // get function
};

class LRUCache : public Cache
{
private:
    int num_keys;

public:
    LRUCache(int capacity) : num_keys(0)
    {
        cp = capacity;
    }

    void set(int key, int val) final
    {
        auto found = mp.find(key);
        if(found != mp.end())
        {
            found->second->value = val;
            //move the node to the head as it was recently accessed
            cache_list.splice(cache_list.begin(),cache_list,found->second);
        }
        else
        {
            ++num_keys;
            cache_list.emplace_front(key,val);
            mp.emplace(key,cache_list.begin());

            while(num_keys > cp)
            {
                mp.erase(cache_list.back().key);
                cache_list.pop_back();
                --num_keys;
            }
        }
    }

    int get(int key) final
    {
        int ret_val = -1;
        auto found = mp.find(key);

        if(found != mp.end())
        {
            ret_val = found->second->value;
            //move the node to the head as it was recently accessed
            cache_list.splice(cache_list.begin(),cache_list,found->second);
        }


        return ret_val;
    }
};

int main()
{
    int n, capacity, i;
    string test_file = "/home/ameya/MiscCodePractice/HackerRank/testcase/cache_test.txt";
    ifstream ifs(test_file);

    if (ifs.is_open())
    {
        ifs >> n >> capacity;
        LRUCache l(capacity);
        for (i = 0; i < n; i++)
        {
            string command;
            ifs >> command;
            if (command == "get")
            {
                int key;
                ifs >> key;
                cout << l.get(key) << endl;
            }
            else if (command == "set")
            {
                int key, value;
                ifs >> key >> value;
                l.set(key, value);
            }
        }
        ifs.close();
    }

    return 0;
}
