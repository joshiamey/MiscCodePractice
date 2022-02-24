#include <iostream>

#include "Bst.h"
using namespace std;


static void test1()
{
    Node* root = new Node(6);

    root = Bst::insert(root,9);
    root = Bst::insert(root,8);
    root = Bst::insert(root,10);
    root = Bst::insert(root,4);
    root = Bst::insert(root,5);
    root = Bst::insert(root,2);

    std::cout << "Tree contains value 5 :" << Bst::search(root,5) << std::endl;
    std::cout << "Tree contains value 25 :" << Bst::search(root,25) << std::endl;

    BstTraversal::in_order(root);
}

int mindDiffinBst(Node* root,Node* prev)
{
    if(!root)
    return INT32_MAX;

    auto min_value = mindDiffinBst(root->left,root);
    if(prev){
        min_value = std::min(min_value, std::abs(root->val - prev->val));
    }
    min_value = std::min(min_value,mindDiffinBst(root->right,root));
     

    return min_value;
}

static void test2()
{
    Node* root = new Node(6);

    root = Bst::insert(root,9);
    root = Bst::insert(root,8);
    root = Bst::insert(root,10);
    root = Bst::insert(root,4);
    root = Bst::insert(root,5);
    root = Bst::insert(root,2);
    BstTraversal::in_order(root);
    std::cout << std::endl;
    Node* newroot = Bst::invert(root);
    BstTraversal::in_order(root);

}

static void test3()
{
    Node* root = new Node(6);

    root = Bst::insert(root,9);
    root = Bst::insert(root,8);
    root = Bst::insert(root,10);
    root = Bst::insert(root,4);
    root = Bst::insert(root,5);
    root = Bst::insert(root,2);

    auto min_diff = mindDiffinBst(root,nullptr);

}

static void test4()
{
    Node* root = new Node(6);

    root = Bst::insert(root,9);
    root = Bst::insert(root,8);
    root = Bst::insert(root,10);
    root = Bst::insert(root,4);
    root = Bst::insert(root,5);
    root = Bst::insert(root,2);

    auto height = 0;
    auto balanced = Bst::isBalanced(root,height);

    cout << balanced << "," << height << endl;

}

static void test5()
{
    Node* root = new Node(8);

    root = Bst::insert(root,5);
    root = Bst::insert(root,12);
    root = Bst::insert(root,10);
    root = Bst::insert(root,9);
    root = Bst::insert(root,11);
    root = Bst::insert(root,13);
    root = Bst::insert(root,3);
    root = Bst::insert(root,7);
    root = Bst::insert(root,6);
    root = Bst::insert(root,4);
    root = Bst::insert(root,2);

    BstTraversal::in_order(root);
    cout << endl;
    BstTraversal::post_order(root);
    cout << endl;
    BstTraversal::pre_order(root);

}

static void test6()
{
    Node* root = new Node(6);

    root = Bst::insert(root,9);
    root = Bst::insert(root,7);
    root = Bst::insert(root,10);
    root = Bst::insert(root,2);
    root = Bst::insert(root,5);
    root = Bst::insert(root,4);
    root = Bst::insert(root,1);
    root = Bst::insert(root,3);


    root = Bst::remove(root,10);
    root = Bst::remove(root,2);
    root = Bst::remove(root,6);

    cout << Bst::search(root,8) << endl;
    cout << Bst::search(root,10) << endl;

}

int main(int argc, char const *argv[])
{

    test6();
    return 0;
}
