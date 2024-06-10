#include <iostream>
#include <vector>

struct TreeNode {
    int key;
    TreeNode *left, *right;
    TreeNode(int x) : key(x), left(nullptr), right(nullptr) {}
};

TreeNode* sortedArrayToBST(std::vector<int>& nums, int start, int end) {
    if (start > end) return nullptr;

    int mid = start + (end - start) / 2;
    TreeNode* node = new TreeNode(nums[mid]);
    node->left = sortedArrayToBST(nums, start, mid - 1);
    node->right = sortedArrayToBST(nums, mid + 1, end);
    return node;
}

void preorderTraversal(TreeNode* node) {
    if (node == nullptr) return;
    std::cout << node->key << " ";
    preorderTraversal(node->left);
    preorderTraversal(node->right);
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> nums[i];
    }

    TreeNode *root = sortedArrayToBST(nums, 0, n - 1);

    preorderTraversal(root);
}
