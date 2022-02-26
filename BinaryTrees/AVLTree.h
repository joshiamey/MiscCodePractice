#include "Node.h"
#include <algorithm>
class AVLTree
{
private:
    /* data */
    void update(Node *n); // update height and balance factor
    Node *balance(Node *n);
    Node *doLeftRotation(Node *n);
    Node *doRightRotation(Node *n);

public:
    AVLTree(/* args */);
    Node *insert(Node *root, int val);
    ~AVLTree();
};

AVLTree::AVLTree(/* args */)
{
}

AVLTree::~AVLTree()
{
}

Node *AVLTree::doLeftRotation(Node *n)
{
    Node *tmp = n->right;
    n->right = tmp->left;
    tmp->left = n;
    //update the height and balance factor
    update(n);
    update(tmp);
    return tmp;
}

Node *AVLTree::doRightRotation(Node *n)
{
    Node *tmp = n->left;
    n->left = tmp->right;
    tmp->right = n;

    //update the height and balance factor
    update(n);
    update(tmp);
    return tmp;
}

void AVLTree::update(Node *n)
{

    auto lh = -1;
    auto rh = -1;

    if (n->left)
        lh = n->left->height;

    if (n->right)
        rh = n->right->height;

    n->height = 1 + std::max(lh, rh);

    n->bf = (lh - rh);
}

Node* AVLTree::balance(Node* root)
{
    if (root->bf >= 2)
    {
        // left heavy
        if (root->left->bf >= 0)
        {
            // leftleft case , do right rotate
            root = doRightRotation(root);
        }
        else
        {
            // left right case
            root->left = doLeftRotation(root->left);
            root = doRightRotation(root);
        }
    }
    else if (root->bf <= -2)
    {
        if (root->right->bf <= 0)
        {
            // Rightright case , do right rotate
            root = doLeftRotation(root);
        }
        else
        {
            // Right left case
            root->right = doRightRotation(root->right);
            root = doLeftRotation(root);
        }
    }

    return root;
}

Node *AVLTree::insert(Node *root, int val)
{
    if (root == nullptr)
    {
        root = new Node(val);
        return root;
    }

    if (val < root->val)
    {
        root->left = insert(root->left, val);
        if (!root->left->parent)
        {
            root->left->parent = root;
        }
    }
    else
    {
        root->right = insert(root->right, val);
        if (!root->right->parent)
        {
            root->right->parent = root;
        }
    }

    //update the Node height and balance factor
    update(root);

    return balance(root);
}