#include <iostream>
#include <map>
#include <string>
#include <list>
#include <fstream>
using namespace std;

struct Node
{
    int key;
    int value;
    int count;
    Node(int k, int val, int in_count) : key(k), value(val), count(in_count){};
};

class Cache
{

protected:
    map<int, list<Node>::iterator> mp; // map the key to the node in the linked list
    int cp;                            // capacity
    list<Node> cache_list;             // cache list
    virtual void set(int, int) = 0;    // set function
    virtual int get(int) = 0;          // get function
public:
    Cache(int in_cp) : cp(in_cp), cache_list(), mp(){};
};

class LFUCache : public Cache
{
private:
    int num_keys;
    map<int, list<Node>::iterator> freq_mp; // this will keep track of freq to node pointer

public:
    LFUCache(int capacity) : Cache(capacity),
                             num_keys(0),
                             freq_mp()
    {
    }

    void set(int key, int val) final
    {
        auto found = mp.find(key);
        if (found != mp.end())
        {
            auto erase_iter = found->second;

            Node nc(key, val, erase_iter->count + 1);
            auto insert_iter = freq_mp.find(nc.count);
            if (insert_iter != freq_mp.end())
            {
                insert_iter->second = cache_list.insert(insert_iter->second, nc);
                mp[key] = insert_iter->second;
            }
            else
            {
                auto insert_iter = freq_mp.find(erase_iter->count);
                auto iter = cache_list.insert(insert_iter->second, nc);
                freq_mp[nc.count] = iter;
                mp[key] = iter;
            }
            cache_list.erase(erase_iter);
            if (erase_iter == freq_mp[erase_iter->count])
            {
                freq_mp.erase(erase_iter->count);
            }

        }
        else
        {
            Node nc(key, val, 1);
            ++num_keys;
            auto insert_iter = freq_mp.find(nc.count);

            if (insert_iter != freq_mp.end())
            {
                insert_iter->second = cache_list.insert(insert_iter->second, nc);
                mp.emplace(key, insert_iter->second);
            }
            else
            {
                cache_list.push_back(nc);
                freq_mp[nc.count] = prev(cache_list.end());
                mp[key] = prev(cache_list.end());
            }

            if (num_keys > cp)
            {
                auto it = mp[cache_list.back().key];

                if (freq_mp.find(it->count) != freq_mp.end())
                {
                    if (it == freq_mp[it->count])
                    {
                        freq_mp.erase(it->count);
                    }
                }
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
        if (found != mp.end())
        {
            auto erase_iter = found->second;
            ret_val = erase_iter->value;
            Node nc(key, ret_val, erase_iter->count + 1);
            auto insert_iter = freq_mp.find(nc.count);
            if (insert_iter != freq_mp.end())
            {
                insert_iter->second = cache_list.insert(insert_iter->second, nc);
                mp[key] = insert_iter->second;
            }
            else
            {
                auto insert_iter = freq_mp.find(erase_iter->count);
                auto iter = cache_list.insert(insert_iter->second, nc);
                freq_mp[nc.count] = iter;
                mp[key] = iter;
            }
            cache_list.erase(erase_iter);
            if (erase_iter == freq_mp[erase_iter->count])
            {
                freq_mp.erase(erase_iter->count);
            }

        }

        return ret_val;
    }
};

int main()
{
    LFUCache ca(4);

    ca.set(1, 2);
    ca.set(2, 3);
    ca.set(3, 5);
    ca.set(1, 3);
    cout << ca.get(1) << endl;
    ca.set(10, 8);
    ca.set(2, 5);
    ca.set(3, 6);
    cout << ca.get(2) << endl;
    cout << ca.get(2) << endl;
    ca.set(11, 12);
    cout << ca.get(10) << endl;


    return 0;
}
