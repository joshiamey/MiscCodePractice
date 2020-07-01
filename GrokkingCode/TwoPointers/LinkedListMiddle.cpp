/* Given the head of a Singly LinkedList, write a method to return the middle node of the LinkedList.

If the total number of nodes in the LinkedList is even, return the second middle node. */

#include <iostream>
using namespace std;

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
};

class LinkedListMiddle
{
private:
    /* data */
public:
    static ListNode *findMiddle(ListNode *head)
    {
        ListNode *slow = head;
        ListNode *fast = head;

        while (fast && fast->next)
        {
            fast = fast->next->next;
            slow = slow->next;
        }

        // incase of even length linked list the slow will point to middle->next node
        // incase of odd length linkedlist the slow will point to middle node
        return slow;
    }
};

int main()
{
    ListNode *head = new ListNode(1);
    ListNode *curr = head;

    for (auto i = 2; i < 7; ++i)
    {
        curr->next = new ListNode(i);
        curr = curr->next;
    }

    auto middle = LinkedListMiddle::findMiddle(head);

    std::cout << "Linked List Middle node is: " << middle->val << endl;
}
