/*Given a binary tree, find the length of its diameter. 
The diameter of a tree is the number of nodes on the longest path between any two leaf nodes. 
The diameter of a tree may or may not pass through the root.
Note: You can always assume that there are at least two leaf nodes in the given tree.*/

#include <iostream>
#include "TreeNode.h"
using namespace std;

class FindDiameter
{
private:
    int doFindDiameter(TreeNode *root, int &max)
    {

        if (!root)
            return 0;

        auto leftsubtreeheight = doFindDiameter(root->left, max);
        auto rightsubtreeheight = doFindDiameter(root->right, max);

        // diameter of the tree will be current node + (left and right subtree heights)
        auto diameter = 1 + leftsubtreeheight + rightsubtreeheight;

        if (diameter > max)
        {
            max = diameter;
        }

        // Return the max between left and right subtree height plus current node

        if (leftsubtreeheight > rightsubtreeheight)
        {
            return leftsubtreeheight + 1;
        }

        return rightsubtreeheight + 1;
    }

public:
    int findDiameter(TreeNode *root)
    {

        if (!root)
            return 0;

        int diameter = 0;

        doFindDiameter(root, diameter);

        return diameter;
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
    FindDiameter path;
    auto result = path.findDiameter(root);
    cout << result << endl;
}
