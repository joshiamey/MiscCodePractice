/* Given a binary tree and a number ‘S’, 
find if the tree has a path from root-to-leaf such that the 
sum of all the node values of that path equals ‘S’. */

#include <iostream>
#include <queue>
#include "TreeNode.h"
using namespace std;

class BinaryTreePathSum
{
private:
    bool doHasPath(TreeNode *root, int S)
    {
        if (root == nullptr)
        {
            // This means the function was called from leaf node which will have right and left null
            // But the S value should be zero if there is path from root->leaf whose sum is S
            return (S == 0);
        }
        // increment the depth
        S -= root->data;
        auto hasleftPath = hasPath(root->left, S);
        auto hasRightPath = hasPath(root->right, S);

        return (hasRightPath || hasleftPath);
    }

public:
    bool hasPath(TreeNode *root, int S)
    {
        if (!root)
            return false;

        return doHasPath(root, S);
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
    BinaryTreePathSum path;
    auto result = path.hasPath(root, 9);

    cout << " Has Path : " << result << endl;
}
