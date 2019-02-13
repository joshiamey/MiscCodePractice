#include <iostream>
using namespace std;
// Definition for singly-linked list.
 struct ListNode {
    int val;
    ListNode *next;
     ListNode(int x) : val(x), next(nullptr) {}
 };

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {

    	ListNode* head = nullptr;
    	ListNode* retval = nullptr;
    	auto carry  = 0;

    	while(l1 || l2 || carry)
    	{
    		auto l1val = 0;
    		auto l2val = 0;

    		if(l1)
    		{
    			l1val = l1->val;
        		l1 = l1->next;
    		}

    		if(l2)
    		{
    			l2val = l2->val;
        		l2 = l2->next;
    		}

    		auto val = l1val + l2val + carry;

    		carry = val/10;
    		val = val % 10;

    		if(head == nullptr)
    		{
    			head = new ListNode(val);
    			// use another pointer to point to head
    			retval = head;
    		}
    		else
    		{
    			head->next = new ListNode(val);
    			head = head->next;
    		}

    	}

    	return retval;
    }
};



int main(int argc, char **argv) {

	ListNode* x = new ListNode(5);
	x->next = new ListNode(0);
	x->next->next = new ListNode(5);

	ListNode* y = new ListNode(5);
	y->next = new ListNode(1);
	y->next->next = new ListNode(5);

	Solution sol;
	ListNode* res = sol.addTwoNumbers(x,y);

	while(res)
	{
		cout << res->val;
		if(res->next)
		{
			cout << "->";
		}
		res = res->next;
	}


	return 0;
}
