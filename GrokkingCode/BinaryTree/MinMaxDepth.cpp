/* Find the minimum depth of a binary tree. 
The minimum depth is the number of nodes along the shortest path
from the root node to the nearest leaf node. */

#include <iostream>
#include <list>
#include <queue>
#include "TreeNode.h"
using namespace std;

class MinMaxDepth
{
private:
    int doGetMinDepth(TreeNode *root, int depth)
    {
        if (root == nullptr)
        {
            // We have reached the leaf node return the calculated depth
            return depth;
        }
        // increment the depth
        ++depth;
        auto leftTreeDepth = doGetMinDepth(root->left, depth);
        auto rightTreeDepth = doGetMinDepth(root->right, depth);

        if (leftTreeDepth < rightTreeDepth)
        {
            return leftTreeDepth;
        }
        else
        {
            return rightTreeDepth;
        }
    }

    int doGetMaxDepth(TreeNode *root, int depth)
    {
        if (root == nullptr)
        {
            // We have reached the leaf node return the calculated depth
            return depth;
        }
        // increment the depth
        ++depth;
        auto leftTreeDepth = doGetMinDepth(root->left, depth);
        auto rightTreeDepth = doGetMinDepth(root->right, depth);

        if (leftTreeDepth > rightTreeDepth)
        {
            return leftTreeDepth;
        }
        else
        {
            return rightTreeDepth;
        }
    }

public:
    int minDepth(TreeNode *root)
    {
        if (!root->left && !root->right)
        {
            return 1;
        }

        if (!root)
            return -1;

        return doGetMinDepth(root, 0);
    }

    int maxDepth(TreeNode *root)
    {
        if (!root->left && !root->right)
        {
            return 1;
        }

        if (!root)
            return -1;

        return doGetMaxDepth(root, 0);
    }
};

int main(int argc, char const *argv[])
{
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    // root->right->left = new TreeNode(6);
    // root->right->right = new TreeNode(7);
    // root->right->right->left = new TreeNode(8);
    // root->right->right->right = new TreeNode(9);
    MinMaxDepth depthGetter;
    auto result = depthGetter.minDepth(root);

    cout << " Minimum depth of the tree is: " << result << endl;
    cout << " Max depth of the tree is: " << depthGetter.maxDepth(root) << endl;
}
