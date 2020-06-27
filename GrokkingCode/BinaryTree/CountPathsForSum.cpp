/* Given a binary tree and a number ‘S’, find all paths in the tree such that 
the sum of all the node values of each path equals ‘S’.
Please note that the paths can start or end at any node but 
all paths must follow direction from parent to child (top to bottom). */

#include <iostream>
#include <vector>
#include <algorithm>
#include "TreeNode.h"
using namespace std;

class CountPaths
{
private:
    int doCountPathSum(TreeNode *root, vector<int> &path, int S)
    {
        if (!root)
            return 0;

        auto pathCount = 0;
        auto sum = 0;
        path.push_back(root->data);

        for (int i = path.size() - 1; i >= 0; --i)
        {
            // Traverse the path list in reverse manner
            // if a subpath whose sum is S , increase the path count
            sum += path[i];
            if (sum == S)
            {
                pathCount++;
            }
        }

        pathCount += doCountPathSum(root->left, path, S);
        pathCount += doCountPathSum(root->right, path, S);

        // As we traverse back in recursive call stack
        // pop back the currently pushed back node
        // so that next call to doCountPathSum is passed correct parent node
        path.pop_back();

        return pathCount;
    }

public:
    int countPathsForSum(TreeNode *root, int S)
    {
        vector<int> paths;
        if (!root)
            return false;

        return doCountPathSum(root, paths, S);
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
    CountPaths pathCounter;
    auto result = pathCounter.countPathsForSum(root, 11);

    cout << " Noof paths for given sum 10 are ==> " << (result) << endl;
}