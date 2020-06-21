/* 
Given a linked list, rotate the list to the right by k places, where k is non-negative.

Example 1:

Input: 1->2->3->4->5->NULL, k = 2
Output: 4->5->1->2->3->NULL
Explanation:
rotate 1 steps to the right: 5->1->2->3->4->NULL
rotate 2 steps to the right: 4->5->1->2->3->NULL

Example 2:

Input: 0->1->2->NULL, k = 4
Output: 2->0->1->NULL
Explanation:
rotate 1 steps to the right: 2->0->1->NULL
rotate 2 steps to the right: 1->2->0->NULL
rotate 3 steps to the right: 0->1->2->NULL
rotate 4 steps to the right: 2->0->1->NULL 
*/
#include <iostream>
#include <string>
#include <chrono>
using namespace std;
using namespace std::chrono;

class ListNode
{
public:
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class RotateList
{
public:
    ListNode *rotate(ListNode *head, int k)
    {
        ListNode *prev = nullptr;
        ListNode *curr = head;

        for (auto i = 0; i < k; ++i)
        {
            while (curr->next != nullptr)
            {
                prev = curr;
                curr = curr->next;
            }

            curr->next = head;
            head = curr;
            prev->next = nullptr;
            curr = head;
        }

        return head;
    }

    string listNodeToString(ListNode *node)
    {
        if (node == nullptr)
        {
            return "[]";
        }

        string result;
        while (node)
        {
            result += to_string(node->val) + "->";
            node = node->next;
        }
        return "[" + result.substr(0, result.length() - 2) + "]";
    }
};

int main()
{
    ListNode *head = new ListNode(1);
    ListNode *curr = head;

    RotateList rotator;

    for (auto i = 2; i < 6; ++i)
    {
        curr->next = new ListNode(i);
        curr = curr->next;
    }

    auto start = high_resolution_clock::now();

    cout << rotator.listNodeToString(head) << endl;

    head = rotator.rotate(head, 8);

    auto end = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end - start);

    cout << rotator.listNodeToString(head) << endl;

    cout << "Time spent = " << duration.count() << endl;

    return 0;
}
