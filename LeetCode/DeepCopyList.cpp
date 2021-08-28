#include <iostream>
#include <unordered_map>
using namespace std;
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

Node *copyRandomList(Node *head)
{
    if (!head)
        return nullptr;

    unordered_map<Node*,Node*> node_map;

    Node* curr = head;

    while(curr){
        Node* n = new Node(curr->val);
        node_map[curr] = n;
        curr = curr->next;
    }

    Node* result = nullptr;

    curr = head;

    while(curr){
        result = node_map[curr];
        result->next = node_map[curr->next];
        result->random = node_map[curr->random];
        curr = curr->next;
    }

    return node_map[head];
}

int main(int argc, char const *argv[])
{
    Node* head = new Node(7);
    head->next = new Node(13);
    head->next->random = head;
    head->next->next = new Node(11);    
    head->next->next->next = new Node(10);
    head->next->next->next->random = head->next->next;
    head->next->next->next->next = new Node(1);
    head->next->next->random = head->next->next->next->next;

    Node* res = copyRandomList(head);


    return 0;
}
