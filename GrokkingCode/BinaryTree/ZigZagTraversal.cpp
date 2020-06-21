/* 
Given a binary tree, populate an array to represent its zigzag level order traversal. 
You should populate the values of all nodes of the first level from left to right, 
then right to left for the next level and keep alternating in the same manner 
for the following levels.
 */

#include <iostream>
#include <list>
#include <queue>
#include "TreeNode.h"
using namespace std;

class ZigZagOrder
{
public:
    list<list<int>> traverse(TreeNode *root)
    {
        list<list<int>> result;

        if (!root)
        {
            return result;
        }
        queue<TreeNode *> q;
        q.push(root);
        auto level = 1;
        while (!q.empty())
        {
            auto levelsize = q.size();

            // Get the current size of the queue that represents
            // the number of nodes at given level
            // dequeu the nodes for this level and store in currlevel list
            list<int> currlevel;
            for (auto i = 0; i < levelsize; ++i)
            {
                TreeNode *node = q.front();
                q.pop();

                // ALternate levels are traversed from left to right
                // level 1 = left to right
                // level 2 = right to left

                if (level % 2 == 0)
                {
                    // even levels , push the nodes in reverse manner
                    currlevel.push_front(node->data);
                }
                else
                {
                    // odd levels , push the nodes in normal manner
                    currlevel.push_back(node->data);
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
            result.push_back(currlevel);
            ++level;
        }

        return result;
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
    ZigZagOrder traverser;
    auto result = traverser.traverse(root);

    cout << "====TEST1====" << endl;

    for (auto &res : result)
    {
        cout << "[";
        for (auto val : res)
        {
            cout << val << " ";
        }
        cout << "]" << endl;
    }

    TreeNode *root2 = new TreeNode(12);
    root2->left = new TreeNode(7);
    root2->right = new TreeNode(1);
    root2->left->left = new TreeNode(9);
    root2->right->left = new TreeNode(10);
    root2->right->right = new TreeNode(5);
    root2->right->left->left = new TreeNode(20);
    root2->right->left->right = new TreeNode(17);

    result = traverser.traverse(root2);
    cout << "====TEST2====" << endl;

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