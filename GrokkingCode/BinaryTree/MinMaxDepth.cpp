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
    int doGetMinDepth(TreeNode *root)
    {
        auto minTreeDepth = 0;
        queue<TreeNode *> q;
        q.push(root);
        while (!q.empty())
        {
            auto levelsize = q.size();
            ++minTreeDepth; // increment mindepth as we reach new level
            for (auto i = 0; i < levelsize; ++i)
            {
                TreeNode *node = q.front();
                q.pop();

                // If the node does not have left,right that means we have
                // reached leaf node, immediately return depth calucalted so far

                if (!node->left && !node->right)
                    return minTreeDepth;

                if (node->left)
                {
                    q.push(node->left);
                }

                if (node->right)
                {
                    q.push(node->right);
                }
            }
        }
        return minTreeDepth;
    }

    int doGetMaxDepth(TreeNode *root)
    {
        auto maxTreeDepth = 0;
        queue<TreeNode *> q;
        q.push(root);
        while (!q.empty())
        {
            auto levelsize = q.size();
            ++maxTreeDepth; // increment maxdepth as we reach new level
            for (auto i = 0; i < levelsize; ++i)
            {
                TreeNode *node = q.front();
                q.pop();

                if (node->left)
                {
                    q.push(node->left);
                }

                if (node->right)
                {
                    q.push(node->right);
                }
            }
        }

        return maxTreeDepth;
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

        return doGetMinDepth(root);
    }

    int maxDepth(TreeNode *root)
    {
        if (!root->left && !root->right)
        {
            return 1;
        }

        if (!root)
            return -1;

        return doGetMaxDepth(root);
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
