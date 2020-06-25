/*Given a binary tree and a number ‘S’, 
find all paths from root-to-leaf such that 
the sum of all the node values of each path equals ‘S’. */

#include <iostream>
#include <list>
#include <algorithm>
#include "TreeNode.h"
using namespace std;

class AllPathsSum
{
private:
    void doGetPaths(TreeNode *root, int S, list<int> &curr_path, list<list<int>> &all_paths)
    {
        curr_path.push_back(root->data);

        if (root->left == nullptr && root->right == nullptr)
        {
            // This means we have encountered leaf node with value equal to Actual S - (parent nodes values)
            // There is exists a path whose sum is equal to S, append it to all_paths
            if (root->data == S)
            {
                all_paths.push_back(curr_path);
            }
        }
        else
        {
            S -= root->data;
            doGetPaths(root->left, S, curr_path, all_paths);
            doGetPaths(root->right, S, curr_path, all_paths);
        }

        // Remove the previously pushed node from curr_path, as we go back in the recursive stack
        curr_path.pop_back();

        return;
    }

public:
    list<list<int>> getAllPaths(TreeNode *root, int S)
    {
        list<list<int>> all_paths;
        list<int> curr_path;

        if (!root)
            return all_paths;

        doGetPaths(root, S, curr_path, all_paths);

        return all_paths;
    }
};

int main(int argc, char const *argv[])
{
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(7);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    // root->right->left = new TreeNode(6);
    // root->right->right = new TreeNode(7);
    // root->right->right->left = new TreeNode(8);
    // root->right->right->right = new TreeNode(9);
    AllPathsSum path;
    auto result = path.getAllPaths(root, 8);

    for (auto &res : result)
    {
        cout << "[";
        for (auto val : res)
        {
            cout << val << " ";
        }
        cout << "]" << endl;
    }
}
