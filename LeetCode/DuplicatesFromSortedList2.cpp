#include <iostream>
#include "ListNode.h"


ListNode* deleteDuplicates1(ListNode* A)
{
    ListNode* currA = A;

    while(currA){
        // check for deleteDuplicates
        while(currA->next && currA->val == currA->next->val){
            currA->next = currA->next->next;
        }

        currA = currA->next;
    }

    return A;
}

ListNode* deleteDuplicates2(ListNode* A)
{
    ListNode* currA = A;
    ListNode* prev = nullptr;
    bool dup = false;

    while(currA){
        // check for deleteDuplicates
        while(currA->next && currA->val == currA->next->val){
            currA = currA->next;
            dup = true;
        }

        if(dup){
            if(prev){
                prev->next = currA->next;
            }else{
                A = currA->next;
            }

            dup = false;
        }else{
            // only record the previous pointer if the duplicates are not found
            prev = currA;
        }

        currA = currA->next;
    }

    return A;
}

int main(int argc, char const *argv[])
{
    ListNode* head = new ListNode(5);
    push(&head,3);
    push(&head,3);
    push(&head,3);
    push(&head,2);
    push(&head,2);
    push(&head,1);

    head = deleteDuplicates1(head);
    return 0;
}
