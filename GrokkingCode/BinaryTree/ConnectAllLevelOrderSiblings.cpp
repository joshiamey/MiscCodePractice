/*
Given a binary tree, connect each node with its level order successor. 
The last node of each level should point to a null node.
*/
#include <iostream>
#include <list>
#include <queue>
#include "TreeNode.h"
using namespace std;

class ConnectLevelOrderSiblings
{
public:
    void connect(TreeNode *root)
    {
        if (!root)
        {
            return;
        }
        queue<TreeNode *> q;
        q.push(root);
        while (!q.empty())
        {
            auto levelsize = q.size();

            // Get the current size of the queue that represents
            // the number of nodes at given level
            // dequeu the nodes for this level and store in currlevel list
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

                // Connect the current node with his level order sibling
                // this time we are connecting all siblings instead siblings
                // on same level
                node->next = q.front();
            }
        }
        return;
    }

    // print level order traversal using next pointer
    void printLevelOrderTraversal(TreeNode *root)
    {
        while (root != nullptr)
        {
            cout << root->data << " ";
            root = root->next;
        }
        cout << endl;
    }
};

int main(int argc, char const *argv[])
{
    TreeNode *root = new TreeNode(12);
    root->left = new TreeNode(7);
    root->right = new TreeNode(1);
    root->left->left = new TreeNode(9);
    root->right->right = new TreeNode(5);
    root->right->left = new TreeNode(10);
    ConnectLevelOrderSiblings connector;
    connector.connect(root);
    connector.printLevelOrderTraversal(root);

    return 0;
}