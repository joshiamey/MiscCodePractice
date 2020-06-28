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

                // if the iterator i is less than (levelsize - 1) , as we are interested only in connecting
                // nodes on current level which will be equal to levelsize
                // The next node in the queue is the
                // level order sibling of current node use the next pointer of tree node to connect
                // current node to the sibling
                if (i < (levelsize - 1))
                {
                    node->next = q.front();
                }

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
        return;
    }

    // print level order traversal using next pointer
    void printLevelOrderTraversal(TreeNode *root)
    {
        auto nextLevelRoot = root;

        while (nextLevelRoot != nullptr)
        {
            auto curr = nextLevelRoot;
            nextLevelRoot = nullptr;
            while (curr != nullptr)
            {
                cout << curr->data << " ";
                if (nextLevelRoot == nullptr)
                {
                    if (curr->left)
                    {
                        nextLevelRoot = curr->left;
                    }
                    else if (curr->right)
                    {
                        nextLevelRoot = curr->right;
                    }
                }

                curr = curr->next;
            }
            cout << endl;
        }
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