#pragma once

class TreeNode
{
private:
    /* data */
public:
    int data;
    TreeNode *left;
    TreeNode *right;
    TreeNode *next; // this extra pointer is maintained to connect the level order sibling
    TreeNode(int x);
    ~TreeNode();
};

TreeNode::TreeNode(int x)
{
    data = x;
    left = nullptr;
    right = nullptr;
    next = nullptr;
}

TreeNode::~TreeNode()
{
    if (left != nullptr)
    {
        delete left;
        left = nullptr;
    }
    if (right != nullptr)
    {
        delete right;
        right = nullptr;
    }
    if (next != nullptr)
    {
        delete right;
        next = nullptr;
    }
}
