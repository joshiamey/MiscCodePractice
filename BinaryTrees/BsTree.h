#pragma once
#include <memory>
#include <iostream>
/*
    Implementation of binary search trees including smart pointers
*/
class BsTree
{
    struct Node
    {
        int val;
        std::shared_ptr<Node> right;
        std::shared_ptr<Node> left;
        // Node *parent;
        // int height;
        // int bf; // balance factor
        Node(int in_val):val(in_val),right(nullptr),left(nullptr){};
        ~Node()
        {
            std::cout << "destructor called for Node: " << val << "\n";
        }
    };

private:
    std::shared_ptr<Node> root;
    std::shared_ptr<Node> _insert(std::shared_ptr<Node> node,int key);
    std::shared_ptr<Node> _remove(std::shared_ptr<Node> node, int key);
    bool _search(std::shared_ptr<Node> node, int key);
public:
    BsTree(/* args */);
    ~BsTree();
    void insert(int key);
    void remove(int key);
    bool isPresent(int key);
    void deleteTree();

};

BsTree::BsTree(/* args */)
{
}

BsTree::~BsTree()
{
}
