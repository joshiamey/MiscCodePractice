// Build tree from inorder and preorder traversal
#include <vector>
#include <iostream>
#include "Bst.h"
using namespace std;

static Node *helperPre(vector<int> &preorder, vector<int> &inorder, int preStart, int inStart, int inEnd)
{
    if (preStart >= preorder.size() || inStart > inEnd)
        return nullptr;

    Node *root = new Node(preorder[preStart]);

    auto mid = -1;
    for (auto i = inStart; i <= inEnd; ++i)
    {
        if (inorder[i] == preorder[preStart])
        {
            mid = i;
            break;
        }
    }

    auto leftNodes = mid - inStart;

    root->left = helperPre(preorder, inorder, preStart + 1, inStart, mid - 1);
    root->right = helperPre(preorder, inorder, preStart + 1 + leftNodes, mid + 1, inEnd);

    return root;
}

static Node *helperPost(vector<int> &postorder, vector<int> &inorder, int pStart, int inStart, int inEnd)
{
    if (pStart < 0 || inStart > inEnd)
        return nullptr;

    Node *root = new Node(postorder[pStart]);

    auto mid = -1;
    for (auto i = inStart; i <= inEnd; ++i)
    {
        if (inorder[i] == postorder[pStart])
        {
            mid = i;
            break;
        }
    }

    auto rightNodes = inEnd - mid;

    root->left = helperPost(postorder, inorder, pStart - 1 - rightNodes, inStart, mid - 1);
    root->right = helperPost(postorder, inorder, pStart - 1, mid + 1, inEnd);

    return root;
}

static Node *buildTreePre(vector<int> &preorder, vector<int> &inorder)
{
    auto sz = preorder.size();

    return helperPre(preorder, inorder, 0, 0, sz - 1);
}

static Node *buildTreePost(vector<int> &postorder, vector<int> &inorder)
{
    auto sz = postorder.size();

    return helperPost(postorder, inorder, sz - 1, 0, sz - 1);
}


static void test1()
{
    vector<int> preorder = {3, 9, 20, 15, 7};
    vector<int> inorder = {9, 3, 15, 20, 7};

    Node* newRoot = buildTreePre(preorder,inorder);

    BstTraversal::in_order(newRoot);
}
static void test2()
{
    vector<int> inorder = {9, 3, 15, 20, 7};
    vector<int> postorder = {9,15,7,20,3};

    Node* newRoot = buildTreePost(postorder,inorder);

    BstTraversal::in_order(newRoot);
}
static void test3()
{
    vector<int> inorder = {2,3,4,5,6,7,8,9,10,11,12,13};
    vector<int> postorder = {2,4,3,6,7,5,9,11,10,13,12,8};

    Node* newRoot = buildTreePost(postorder,inorder);

    BstTraversal::in_order(newRoot);
    
}
int main(int argc, char const *argv[])
{
    test3();
    cout << endl;
    test1();
}
