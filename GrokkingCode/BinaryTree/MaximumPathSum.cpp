/*Find the path with the maximum sum in a given binary tree. 
Write a function that returns the maximum sum. 
A path can be defined as a sequence of nodes between any 
two nodes and doesn’t necessarily pass through the root.*/

#include <iostream>
#include "TreeNode.h"
using namespace std;

class MaximumPathSum
{
private:
    int doFindPathWithMaxSum(TreeNode *root, int &maxPathSum)
    {

        if (!root)
            return 0;

        auto leftsubtreemaxsum = doFindPathWithMaxSum(root->left, maxPathSum);
        auto rightsubtreemaxsum = doFindPathWithMaxSum(root->right, maxPathSum);

        // the max sum at current node will be current node data + (left and right subtree max sum)
        auto currPathMaxSum = root->data + leftsubtreemaxsum + rightsubtreemaxsum;

        // update the maxPathSum
        if (currPathMaxSum > maxPathSum)
        {
            maxPathSum = currPathMaxSum;
        }

        // Max sum of any path from current node will be current node value plus
        // max of left and right subtree sum

        if (leftsubtreemaxsum > rightsubtreemaxsum)
        {
            return leftsubtreemaxsum + root->data;
        }

        return rightsubtreemaxsum + root->data;
    }

public:
    int findPathWithMaxSum(TreeNode *root)
    {

        if (!root)
            return 0;

        int pathMaxSum = 0;

        doFindPathWithMaxSum(root, pathMaxSum);

        return pathMaxSum;
    }
};

int main(int argc, char const *argv[])
{
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->right->left = new TreeNode(5);
    root->right->right = new TreeNode(6);
    // root->right->left = new TreeNode(6);
    // root->right->right = new TreeNode(7);
    // root->right->right->left = new TreeNode(8);
    // root->right->right->right = new TreeNode(9);
    MaximumPathSum path;
    auto result = path.findPathWithMaxSum(root);
    cout << result << endl;

    TreeNode *node = new TreeNode(1);
    node->left = new TreeNode(2);
    node->right = new TreeNode(3);
    node->left->left = new TreeNode(1);
    node->left->right = new TreeNode(3);
    node->right->left = new TreeNode(5);
    node->right->right = new TreeNode(6);
    node->right->left->left = new TreeNode(7);
    node->right->left->right = new TreeNode(8);
    node->right->right->right = new TreeNode(9);

    result = path.findPathWithMaxSum(node);
    cout << result << endl;
}
