#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
#include <fstream>
using namespace std;

struct Node
{
    Node *next;
    Node *prev;
    int value;
    int key;
    Node(Node *p, Node *n, int k, int val) : prev(p), next(n), key(k), value(val){};
    Node(int k, int val) : prev(NULL), next(NULL), key(k), value(val){};
};

class Cache
{

protected:
    map<int, Node *> mp;            // map the key to the node in the linked list
    int cp;                         // capacity
    Node *tail;                     // double linked list tail pointer
    Node *head;                     // double linked list head pointer
    virtual void set(int, int) = 0; // set function
    virtual int get(int) = 0;       // get function
};

class LRUCache : public Cache
{
private:
    int num_keys;

public:
    LRUCache(int capacity) : num_keys(0)
    {
        cp = capacity;
        head = nullptr;
        tail = nullptr;
    }

    void set(int key, int val) final
    {
        auto found = mp.find(key);
        if (found != mp.end())
        {
            found->second->value = val;
            return;
        }

        ++num_keys;
        if (!head)
        {
            head = new Node(key, val);
            tail = head;
        }
        else
        {
            Node *n = new Node(key, val);

            n->next = head;
            head->prev = n;
            head = n;
        }

        mp.emplace(key, head);

        if (num_keys > cp)
        {
            // remove last key
            mp.erase(tail->key);
            tail = tail->prev;
            delete tail->next;
            tail->next = nullptr;
        }
    }

    int get(int key) final
    {
        auto found = mp.find(key);
        if (found != mp.end())
        {
            Node *found_node = found->second;
            auto ret_val = found_node->value;
            Node *prev = found_node->prev;
            Node *next = found_node->next;
            // if the node is in the middle
            if (prev)
            {
                found_node->next = head;
                found_node->prev = nullptr;
                head = found_node;
                head->next->prev = head;

                // i.e found node is tail pointer
                if (next == nullptr)
                {
                    tail = prev;
                    tail->next = nullptr;
                }
                else
                {
                    next->prev = prev;
                    prev->next = next;
                }
            }

            return ret_val;
        }

        return -1;
    }
};

int main()
{
    int n, capacity, i;
    string test_file = "/home/ameya/MiscCodePractice/HackerRank/testcase/testcase1.txt";
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
    }
    return 0;
}
