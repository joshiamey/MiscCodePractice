/* Given a binary tree and a node, find the level order successor of the given node in the tree.
 The level order successor is the node 
that appears right after the given node in the level order traversal. */

#include <iostream>
#include <queue>
#include "TreeNode.h"
using namespace std;

class LevelOrderSuccessor
{
private:
    /* data */
public:
    TreeNode *levelOrderSuccessor(TreeNode *root, int key)
    {
        if (!root)
            return nullptr;

        if (!root->left && !root->right)
            return nullptr;

        queue<TreeNode *> q;
        q.push(root);
        auto levelOrderSuccessor = false;
        auto foundKeyNodeLevel = false;

        while (!q.empty())
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

            if (node->data == key)
            {
                // Found the level on which the node key is present
                // break;
                break;
            }
        }

        // Return the node currently in the front of the queue
        return q.front();
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
    LevelOrderSuccessor successor;
    auto result = successor.levelOrderSuccessor(root, 3);

    cout << " Successor of node 3 is : " << result->data << endl;
}
