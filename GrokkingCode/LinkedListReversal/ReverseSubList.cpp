/*Given the head of a LinkedList and two positions ‘p’ and ‘q’, 
* reverse the LinkedList from position ‘p’ to ‘q’.
*  head->1->2->3->4->5->null
*           (p)   (q)
*  head->1->4->3->2->5->null
*/
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;
class ListNode
{
public:
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class RevereSubList
{
public:
    ListNode *reverseSubList(ListNode *head, int p, int q)
    {
        ListNode *prev = head;
        ListNode *curr = head->next;
        ListNode *start = nullptr; // To keep track of node before 'p'

        // Traverse the linked list until you find the node 'p'
        // Store the value of node before 'p' in start
        // Based upon example list in header: at the end
        // prev=2 curr=3 and start=1
        while (prev->val != p)
        {
            start = prev;
            prev = curr;
            curr = curr->next;
        }

        // prev points towards node 'p'
        // Reverse the sublist until node 'q' by traversing until
        // prev reaches node 'q'

        while (prev && prev->val != q)
        {
            ListNode *next = curr->next; // store the next pointer
            curr->next = prev;           // Reverse the connection between 2 nodes ( a->b => a<-b)
            prev = curr;                 // increment or point prev towards current
            curr = next;                 // increment curr or point curr towards next
        }

        // Once the loop exits, curr will point towards a dangling node which
        // previously was curr->next, and prev will point towards node 'q'
        // To complete the list

        ListNode *startNext = start->next; // Store the current next pointer of start ( 1->2<-3) 2 in this case
        start->next = prev;                // complete the reversal on start end by point start->next to prev i.e (q)
        startNext->next = curr;            // Complete the list at the tail by pointing the startNext next pointer to dangling curr.

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
    ListNode head(0);
    ListNode *curr = &head;

    RevereSubList listReverse;

    for (auto i = 1; i < 6; ++i)
    {
        curr->next = new ListNode(i);
        curr = curr->next;
    }

    cout << listReverse.listNodeToString(&head) << endl;

    listReverse.reverseSubList(&head, 2, 4);

    cout << listReverse.listNodeToString(&head) << endl;

    return 0;
}