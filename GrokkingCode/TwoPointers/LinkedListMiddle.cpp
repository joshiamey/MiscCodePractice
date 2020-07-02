/* Given the head of a Singly LinkedList, write a method to return the middle node of the LinkedList.
If the total number of nodes in the LinkedList is even, return the second middle node. */

#include "ListNode.h"
using namespace std;

class LinkedListMiddle
{
private:
    static ListNode *reverse(ListNode *head)
    {
        // Reverse the linked list from middle->next to null
        ListNode *prev = nullptr;
        while (head != nullptr)
        {
            auto next = head->next;
            head->next = prev;
            prev = head;
            head = next;
        }

        return prev;
    }

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

    /* Palindrome LinkedList (medium) 
    Given the head of a Singly LinkedList, write a method to check if the LinkedList is a palindrome or not.
    Your algorithm should use constant space and the input LinkedList should be in the original 
    form once the algorithm is finished. The algorithm should have O(N)O(N)O(N) time complexity  
    where ‘N’ is the number of nodes in the LinkedList.*/

    static bool isPalinDrome(ListNode *head)
    {
        auto isPalindrome = true;
        if (head == nullptr)
        {
            return false;
        }
        // Find the middle of the linked list
        auto middle = findMiddle(head);

        if (middle->next == nullptr)
        {
            return (head->val == middle->val);
        }

        // Reverse the linked list from middle->next to null
        middle->next = reverse(middle->next);

        // if the linked list is a palindrome then node values from head-->middle
        // and middle-->>null will be same of reversed linked list
        // in case of even length linked list node before middle should be same as middle
        auto ptr1 = head;
        auto ptr2 = middle->next;
        while (ptr2 != nullptr)
        {
            // if the node values are different the linked list is not a palindrome
            if (ptr1->val != ptr2->val)
            {
                isPalindrome = false;
                break;
            }
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }

        // at the end of the above while loop the ptr1 should point to middle
        // if it is odd length linked list or if its even length linked list
        // then ptr1->next should be equal to middle
        if (ptr1 && ptr1->next == middle)
        {
            // if even length list then ptr1->next is middle in that case
            // ptr1->val should be equal to middle->value
            // as in case of even length the middle value returned is
            // (N/2) + 1
            isPalindrome &= (ptr1->val == middle->val);
        }
        else
        {
            isPalindrome &= (ptr1 == middle);
        }

        //Reverse the linked list after middle to restore the original list
        middle->next = reverse(middle->next);

        return isPalindrome;
    }
    /* 
    Given the head of a Singly LinkedList, write a method to modify the LinkedList 
    such that the nodes from the second half of the LinkedList are inserted alternately 
    to the nodes from the first half in reverse order. 
    So if the LinkedList has nodes 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> null, your method should 
    return 1 -> 6 -> 2 -> 5 -> 3 -> 4 -> null.
    Your algorithm should not use any extra space and the input LinkedList should be modified in-place. */

    static ListNode *rearrange(ListNode *head)
    {
        if (head == nullptr)
        {
            return nullptr;
        }

        // Find the middle of the linked list
        auto middle = findMiddle(head);

        if (middle->next == nullptr)
        {
            return head;
        }

        middle->next = reverse(middle->next);

        auto curr = head;
        auto middleHead = middle->next;

        while (curr && middleHead)
        {
            auto next = curr->next;
            auto middleheadnext = middleHead->next;
            curr->next = middleHead;
            curr->next->next = next;
            curr = next;
            middleHead = middleheadnext;
        }

        middle->next = nullptr;

        return head;
    }
};

int main()
{
    ListNode *head = new ListNode(1);
    ListNode *curr = head;

    for (auto i = 2; i < 8; ++i)
    {
        curr->next = new ListNode(i);
        curr = curr->next;
    }

    auto middle = LinkedListMiddle::findMiddle(head);

    std::cout << "Linked List Middle node is: " << middle->val << endl;

    ListNode *head2 = new ListNode(2);
    head2->next = new ListNode(4);
    head2->next->next = new ListNode(6);
    head2->next->next->next = new ListNode(6);
    head2->next->next->next->next = new ListNode(4);
    head2->next->next->next->next->next = new ListNode(2);

    std::cout << "Linked List is Palindrome? " << (LinkedListMiddle::isPalinDrome(head2) ? "TRUE" : "FALSE") << endl;

    ListNode::print(head);
    cout << "==== After rearranging ===" << endl;
    head = LinkedListMiddle::rearrange(head);
    ListNode::print(head);
}
