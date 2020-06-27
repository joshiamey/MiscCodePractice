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
    bool dofindpath(TreeNode *root, vector<int> &path)
    {
        // search if the current node is present in the given path vector
        auto found_iter = find(path.begin(), path.end(), root->data);

        if (found_iter != path.end())
        {
            // if the node is present, remove from the sequence vector to narrow down the search
            path.erase(found_iter);
        }
        else
        {
            // The node is not present in the path , return false.
            return false;
        }

        if (root->left == nullptr && root->right == nullptr)
        {
            // We have reached the leaf node by this time the path vector should be empty
            return path.empty();
        }

        auto leftpathsum = dofindpath(root->left, path);
        auto rightpathsum = dofindpath(root->right, path);

        // return the addition of path nos calulated in left and right subtrees
        return (leftpathsum || rightpathsum);
    }

public:
    bool findpath(TreeNode *root, vector<int> &path)
    {
        if (!root)
            return false;

        return dofindpath(root, path);
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
