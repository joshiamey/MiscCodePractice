/* 
Given a binary tree, return the level order traversal of its nodes' 
values. (ie, from left to right, level by level).

For example:
Given binary tree [3,9,20,null,null,15,7],

    3
   / \
  9  20
    /  \
   15   7

return its level order traversal as:

[
  [3],
  [9,20],
  [15,7]
]

Also add an API to print reverse Level order traversal

[
  [15,7],
  [9,20],
  [3]
]
 */

#include <iostream>
#include <list>
#include <queue>
#include "TreeNode.h"
using namespace std;

class LevelOrder
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
                currlevel.push_back(node->data);

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
        }

        return result;
    }

    list<list<int>> traverseReverse(TreeNode *root)
    {
        list<list<int>> result;

        if (!root)
        {
            return result;
        }
        queue<TreeNode *> q;
        q.push(root);
        while (!q.empty())
        {
            auto levelsize = q.size();
            list<int> currlevel;
            for (auto i = 0; i < levelsize; ++i)
            {
                TreeNode *node = q.front();
                q.pop();
                currlevel.push_back(node->data);

                if (node->left)
                {
                    q.push(node->left);
                }

                if (node->right)
                {
                    q.push(node->right);
                }
            }

            // Required to traverse/print in reverse that is leaf nodes
            // at the beginning, root node at the end
            // hence push the current level to the front.
            result.push_front(currlevel);
        }

        return result;
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
    LevelOrder traverser;
    auto result = traverser.traverse(root);

    for (auto &res : result)
    {
        cout << "[";
        for (auto val : res)
        {
            cout << val << " ";
        }
        cout << "]" << endl;
    }

    cout << "Level order traversal in reverse." << endl;
    result = traverser.traverseReverse(root);

    for (auto &res : result)
    {
        cout << "[";
        for (auto val : res)
        {
            cout << val << " ";
        }
        cout << "]" << endl;
    }

    return 0;
}
