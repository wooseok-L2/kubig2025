#include <memory>
#include <iostream>
#include <vector>

using namespace std;

struct TreeNode{
    int value;
    vector<shared_ptr<TreeNode>> children;
    TreeNode(int val) : value(val) {}
};

void printTree(const shared_ptr<TreeNode>& node, int depth=0)
{
    if (!node) return;

    cout << std::string(depth * 2, ' ') << node->value << endl;

    for (const auto& child : node->children){
        printTree(child, depth + 1);
    }
}

int main()
{
    auto root = make_shared<TreeNode>(1);
    root->children.push_back(make_shared<TreeNode>(2));
    root->children.push_back(make_shared<TreeNode>(3));
    root->children.push_back(make_shared<TreeNode>(4));
    root->children[0]->children.push_back(make_shared<TreeNode>(5));

    printTree(root);


    return 0;
}