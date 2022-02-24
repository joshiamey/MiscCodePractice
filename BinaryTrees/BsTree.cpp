#include <iostream>
#include "BsTree.h"

using namespace std;

shared_ptr<BsTree::Node> BsTree::_insert(shared_ptr<Node> node, int key)
{

    if (node == nullptr)
    {
        node = make_shared<Node>(key);
    }
    else if (key < node->val)
    {
        node->left = _insert(node->left, key);
    }
    else
    {
        node->right = _insert(node->right, key);
    }

    return node;
}

void BsTree::insert(int key)
{
    root = _insert(root, key);
}

shared_ptr<BsTree::Node> BsTree::_remove(shared_ptr<BsTree::Node> node, int key)
{
    if (!root)
        return nullptr;

    if (key < node->val)
    {
        node->left = _remove(node->left, key);
    }
    else if (key > node->val)
    {
        node->right = _remove(node->right, key);
    }
    else
    {
        if (!node->left && !node->right)
        {
            node.reset();
            return nullptr;
        }
        if (!node->right && node->left)
        {
            shared_ptr<Node> temp = node->left;
            node.reset();
            node = nullptr;
            return temp;
        }

        if (node->right && !node->left)
        {
            shared_ptr<Node> temp = node->right;
            node.reset();
            node = nullptr;
            return temp;
        }
        shared_ptr<Node> succ = node->right;
        while (succ->left)
        {
            succ = succ->left;
        }

        node->val = succ->val;
        node->right = _remove(node->right, succ->val);
    }

    return node;
}

void BsTree::remove(int key)
{
    _remove(root, key);
}

void BsTree::deleteTree()
{
    root.reset();
    root = nullptr;
}

bool BsTree::isPresent(int key)
{
    return _search(root, key);
}

bool BsTree::_search(shared_ptr<Node> root, int key)
{
    if (!root)
        return false;

    if (root->val == key)
    {
        return true;
    }
    else if (key < root->val)
    {
        return _search(root->left, key);
    }
    else
    {
        return _search(root->right, key);
    }

    return false;
}

int main(int argc, char const *argv[])
{
    BsTree bs_tree;

    bs_tree.insert(50);
    bs_tree.insert(30);
    bs_tree.insert(70);
    bs_tree.insert(20);
    bs_tree.insert(40);
    bs_tree.insert(60);
    bs_tree.insert(80);

    cout << bs_tree.isPresent(8) << "\n";
    cout << bs_tree.isPresent(60) << "\n";

    bs_tree.remove(20);

    cout << bs_tree.isPresent(20) << "\n";
    bs_tree.remove(30);

    cout << bs_tree.isPresent(30) << "\n";
    bs_tree.remove(50);

    cout << bs_tree.isPresent(50) << "\n";
    cout << bs_tree.isPresent(60) << "\n";
    return 0;
}
