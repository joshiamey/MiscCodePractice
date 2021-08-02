#include <iostream>

struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
};

static ListNode* reverse(ListNode* head)
{
    ListNode* curr = head;
    ListNode* prev = nullptr;
    ListNode* nxt = nullptr;
    while(curr)
    {
        ListNode* nxt = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nxt;
    }

    head = prev;

    return head;

}

static void reorderList(ListNode* head)
{
    ListNode* slow = head;
    ListNode* fast = head;

    // find the midpoint;
    while(fast->next && fast->next->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    ListNode* dummy = reverse(slow);

    ListNode* curr = head;

    while(curr && dummy)
    {
        ListNode* nxt = curr->next;
        ListNode* dummyNext = dummy->next;
        curr->next = dummy;
        dummy->next = nxt;
        curr = nxt;
        dummy = dummyNext;
    }
}

void push(struct ListNode **head, int data)
{
    struct ListNode *newNode = new ListNode(data);
    newNode->next = *head;
    *head = newNode;
}

int main(int argc, char const *argv[])
{   
    // ListNode* head = nullptr;
    // for(auto i = 7; i > 0 ; i--)
    // {
    //     push(&head,i);
    // }
    // reorderList(head);

    ListNode* head2 = nullptr;
    for(auto i = 4; i > 0 ; i--)
    {
        push(&head2,i);
    }
    reorderList(head2);
    return 0;
}


