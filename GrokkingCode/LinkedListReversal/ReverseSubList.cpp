/*Given the head of a LinkedList and two positions ‘p’ and ‘q’, 
* reverse the LinkedList from position ‘p’ to ‘q’.
*  head->1->2->3->4->5->null
*           (p)   (q)
*  head->1->4->3->2->5->null
*/
#include <iostream>
#include <string>
using namespace std;
class ListNode
{
public:
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class ReverseSubList
{
public:
    ListNode *reverseSubList(ListNode *head, int p, int q)
    {
        ListNode *prev = nullptr;
        ListNode *curr = head;
        ListNode *start = nullptr; // To keep track of node before 'p'

        // Traverse the linked list until you find the node at position 'p'
        // Store the value of node at 'p - 1' in start
        // Based upon example list in header: at the end
        // prev=2 curr=3 and start=1
        for (auto i = 0; i < (p - 1); ++i)
        {
            prev = curr;
            curr = curr->next;
        }

        // prev will point towards the node p - 1
        // curr will point towards the node p
        start = prev;         // store the p-1 node in start
        ListNode *end = curr; // store the eventual tailend of the reversed list in end

        for (auto i = 0; curr && i <= (q - p); ++i)
        {
            ListNode *next = curr->next; // store the next pointer
            curr->next = prev;           // Reverse the connection between 2 nodes ( a->b => a<-b)
            prev = curr;                 // increment or point prev towards current
            curr = next;                 // increment curr or point curr towards next
        }

        if (start != nullptr)
        {
            start->next = prev; // connect the node p - 1 to the head of the reversed linked list
        }
        else
        {
            head = prev;
        }

        // Connect the previously store tailend of reversed list to the new curr pointer to
        // connecting the list
        end->next = curr;

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

    ReverseSubList listReverse;

    for (auto i = 2; i < 6; ++i)
    {
        curr->next = new ListNode(i);
        curr = curr->next;
    }

    cout << listReverse.listNodeToString(head) << endl;

    head = listReverse.reverseSubList(head, 1, 5);

    cout << listReverse.listNodeToString(head) << endl;

    return 0;
}