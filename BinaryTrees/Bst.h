/* Implementation of binary search tree class */
#include <iostream>
#include <algorithm>
#include "Node.h"
namespace BstTraversal
{
    void pre_order(Node *root)
    {
        if (!root)
            return;

        std::cout << root->val << ",";
        pre_order(root->left);
        pre_order(root->right);
    }

    void in_order(Node *root)
    {
        if (!root)
            return;

        in_order(root->left);
        std::cout << root->val << ",";
        in_order(root->right);
    }

    void post_order(Node *root)
    {
        if (!root)
            return;

        post_order(root->left);
        post_order(root->right);
        std::cout << root->val << ",";
    }
}

namespace Bst
{
    Node *insert(Node *root, int val)
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

        return root;
    }

    bool search(Node *root, int target)
    {
        if (!root)
        {
            return false;
        }

        if (root->val == target)
        {
            return true;
        }
        else if (target < root->val)
        {
            return search(root->left, target);
        }
        else
        {
            return search(root->right, target);
        }
    }

    Node *findParent(Node *root, Node *target)
    {
        Node *succ = nullptr;
        while (!root)
        {
            if (target->val < root->val)
            {
                succ = root;
                root = root->left;
            }
            else
            {
                root = root->right;
            }
        }

        return root;
    }

    Node *successor(Node *root)
    {
        if (!root)
            return nullptr;

        if (root->right)
        {
            Node *curr = root->right;

            while (curr->left)
            {
                curr = curr->left;
            }

            return curr;
        }
        else
        {
            Node *p = root->parent;

            while (p && root && p->val < root->val)
            {
                root = p;
                p = p->parent;
            }
            return p;
        }
    }

    Node *invert(Node *root)
    {
        if (!root)
            return nullptr;

        Node *right = root->right;
        root->right = invert(root->left);
        root->left = invert(right);

        return root;
    }

    bool isBalanced(Node *root, int &height)
    {
        if (!root)
        {
            height = -1;
            return true;
        }

        auto lh = -1;
        auto left_balanced = isBalanced(root->left, lh);
        auto rh = -1;
        auto right_balanced = isBalanced(root->right, rh);

        auto balanced = left_balanced && right_balanced && (abs(lh - rh) <= 1);

        height = 1 + std::max(lh, rh);

        return balanced;
    }

    Node *remove(Node *root, int val)
    {
        if (!root)
            return nullptr;

        if (root->val > val)
        {
            root->left = remove(root->left, val);
        }
        else if (root->val < val)
        {
            root->right = remove(root->right, val);
        }
        else
        {
            // if leaf node
            if (!root->right && !root->left)
            {
                delete (root);
                return nullptr;
            }
            else if (!root->right && root->left)
            {
                Node *left = root->left;
                delete (root);
                return left;
            }
            else if (!root->left && root->right)
            {
                Node *right = root->right;
                delete (root);
                return right;
            }
            else
            {
                Node *succ = successor(root);
                root->val = succ->val;
                root->right = remove(root->right, succ->val);
            }
        }

        return root;
    }
}
