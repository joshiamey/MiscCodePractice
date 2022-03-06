#include <iostream>
#include <map>
#include <unordered_map>
#include <list>
#include <memory>
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
    unordered_map<int, list<Node>::iterator> mp; // map the key to the node in the linked list
    int cp;                                      // capacity
    list<Node> cache_list;                       // cache list
    virtual void set(int, int) = 0;              // set function
    virtual int get(int) = 0;                    // get function
public:
    Cache(int in_cp) : cp(in_cp), cache_list(), mp(){};
};

class LFUCache : public Cache
{
private:
    int num_keys;
    unordered_map<int, list<Node>::iterator> freq_mp; // this will keep track of freq to node pointer

    // this function will position the found node in the list with the key
    // in appropriate position with respect to its frequency
    void __update_list(unordered_map<int, list<Node>::iterator>::iterator &found)
    {
        auto curr_count = found->second->count;
        ++found->second->count; // increment the count

        // check if you have already a list element with curr_count + 1
        // this node now shall be inserted before that
        auto insert_iter = freq_mp.find(found->second->count);
        // else it will be inserted before the node that has count = curr_count;
        auto it = freq_mp.find(curr_count);
        auto lfu_iter = it->second;
        // check if the iterator node returned from that freqmap matches the
        // key we are updating , that means for the old freq count the mapped
        // list pointer needs an udpate
        if (lfu_iter->key == found->second->key)
        {
            lfu_iter++;

            if (lfu_iter == cache_list.end() || lfu_iter->count != curr_count)
            {
                // means no nodes exist with that count anymore
                // erase from frequency map
                freq_mp.erase(curr_count);
            }
            else
            {
                freq_mp[curr_count] = lfu_iter;
            }
        }

        if (insert_iter != freq_mp.end())
        {
            cache_list.splice(insert_iter->second, cache_list, found->second);
        }
        else
        {
            cache_list.splice(lfu_iter, cache_list, found->second);
        }

        freq_mp[found->second->count] = found->second;
    }

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
            found->second->value = val;
            __update_list(found);
        }
        else
        {
            Node nc(key, val, 1);
            // delete keys if num_keys greater than capacity
            if (num_keys >= cp)
            {
                --num_keys;
                auto it = mp[cache_list.back().key];

                // if the iterator is mapped to the head
                // of the list for that count, delete it from
                // freq_map
                if (it == freq_mp[it->count])
                {
                    freq_mp.erase(it->count);
                }

                mp.erase(cache_list.back().key);
                cache_list.pop_back();
            }
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
        }
    }

    int get(int key) final
    {
        int ret_val = -1;
        auto found = mp.find(key);
        if (found != mp.end())
        {
            ret_val = found->second->value;
            __update_list(found);
        }

        return ret_val;
    }
};

int main()
{
    unique_ptr<LFUCache> ca = make_unique<LFUCache>(2);
    ca->set(1, 1);
    ca->set(2, 2);
    cout << ca->get(1) << endl;
    ca->set(3, 3);
    cout << ca->get(2) << endl;
    cout << ca->get(3) << endl;
    ca->set(4, 4);
    cout << ca->get(1) << endl;
    cout << ca->get(3) << endl;
    cout << ca->get(4) << endl;
    ca->set(5, 6);
    cout << ca->get(3) << endl;

    return 0;
}
