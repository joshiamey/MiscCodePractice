/* Given a binary tree and a number sequence, 
find if the sequence is present as a root-to-leaf path in the given tree. */

#include <iostream>
#include <vector>
#include <algorithm>
#include "TreeNode.h"
using namespace std;

class FindPath
{
private:
    bool dofindpath(TreeNode *root, vector<int> &path, int pathIndex)
    {
        if (root->data != path[pathIndex])
        {
            // the given node is not present at the given path index
            return false;
        }

        if (root->left == nullptr && root->right == nullptr)
        {
            // We have reached the leaf node by this time the path index should be equal
            // to the last index of the path vector
            return pathIndex == (path.size() - 1);
        }

        // post increment the path index
        pathIndex++;

        auto leftpathsum = dofindpath(root->left, path, pathIndex);
        auto rightpathsum = dofindpath(root->right, path, pathIndex);

        // return true if path is present in left or right subtree
        return (leftpathsum || rightpathsum);
    }

public:
    bool findpath(TreeNode *root, vector<int> &path)
    {
        if (!root)
            return false;

        return dofindpath(root, path, 0);
    }
};

int main(int argc, char const *argv[])
{
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);
    root->right->right->left = new TreeNode(8);
    root->right->right->right = new TreeNode(9);
    vector<int> seq = {1, 3, 7, 8};
    FindPath pathfinder;
    auto result = pathfinder.findpath(root, seq);

    cout << " Sequence present in given tree ==> " << (result ? "TRUE" : "FALSE") << endl;
}
