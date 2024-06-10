#include <iostream>
#include <vector>
#include <stack>

bool isInorderSorted(const std::vector<int>& inorder) {
    for (int i = 1; i < inorder.size(); i++) {
        if (inorder[i-1] > inorder[i]) {
            return false;
        }
    }
    return true;
}

bool isPreOrderOfBST(const std::vector<int>& preorder, const std::vector<int>& inorder) {
    std::stack<int> st;
    int j = 0;

    for (int value : preorder) {
        st.push(value);
        while (!st.empty() && st.top() == inorder[j]) {
            st.pop();
            j++;
        }
    }

    return j == inorder.size();
}

bool isPostOrderOfBST(const std::vector<int>& postorder, const std::vector<int>& inorder) {
    std::stack<int> st;
    int j = inorder.size() - 1;

    for (int i = postorder.size() - 1; i >= 0; i--) {
        st.push(postorder[i]);
        while (!st.empty() && st.top() == inorder[j]) {
            st.pop();
            j--;
        }
    }

    return j == -1;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    int n;
    std::cin >> n;

    std::vector<int> preorder(n), inorder(n), postorder(n);

    for (int i = 0; i < n; i++) {
        std::cin >> preorder[i];
    }
    for (int i = 0; i < n; i++) {
        std::cin >> inorder[i];
    }
    for (int i = 0; i < n; i++) {
        std::cin >> postorder[i];
    }

    if (isInorderSorted(inorder) && isPreOrderOfBST(preorder, inorder) && isPostOrderOfBST(postorder, inorder)){
        std::cout << "YES";
    } else {
        std::cout << "NO";
    }
}
