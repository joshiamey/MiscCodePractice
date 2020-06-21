#pragma once

class TreeNode
{
private:
    /* data */
public:
    int data;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x);
    ~TreeNode();
};

TreeNode::TreeNode(int x)
{
    data = x;
    left = nullptr;
    right = nullptr;
}

TreeNode::~TreeNode()
{
    if (left != nullptr)
    {
        left = nullptr;
        delete left;
    }
    if (right != nullptr)
    {
        right = nullptr;
        delete right;
    }
}
