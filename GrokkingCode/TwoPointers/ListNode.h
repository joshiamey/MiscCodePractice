#pragma once

#include <iostream>
#include <string>

class ListNode
{
public:
    int val;
    ListNode *next;
    ListNode(int x)
        : val(x),
          next(nullptr)
    {
    }

    static void print(ListNode *node)
    {
        if (node == nullptr)
        {
            std::cout << "[]";
        }

        std::string result;
        while (node)
        {
            result += std::to_string(node->val) + "->";
            node = node->next;
        }
        std::cout << ("[" + result.substr(0, result.length() - 2) + "]") << std::endl;
    }
};
