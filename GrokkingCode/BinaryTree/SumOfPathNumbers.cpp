/* Given a binary tree and a number ‘S’, 
find if the tree has a path from root-to-leaf such that the 
sum of all the node values of that path equals ‘S’. */

#include <iostream>
#include "TreeNode.h"
using namespace std;

class SumOfPathNos
{
private:
    int dofindsumofpathnos(TreeNode *root, int currpathno)
    {
        // increment the depth
        currpathno = (currpathno * 10) + root->data;

        if (root->left == nullptr && root->right == nullptr)
        {
            // We have reached the leaf node return the current calculated pathno
            return currpathno;
        }

        auto leftpathsum = dofindsumofpathnos(root->left, currpathno);
        auto rightpathsum = dofindsumofpathnos(root->right, currpathno);

        // return the addition of path nos calulated in left and right subtrees
        return (leftpathsum + rightpathsum);
    }

public:
    int findsumofpathnos(TreeNode *root)
    {
        if (!root)
            return 0;

        return dofindsumofpathnos(root, 0);
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
    SumOfPathNos path;
    auto result = path.findsumofpathnos(root);

    cout << " Sum of pathnos: " << result << endl;
}
