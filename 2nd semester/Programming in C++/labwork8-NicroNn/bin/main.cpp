#include "lib/bst.h"

int main() {
    BstContainer<int, std::less<int>, std::allocator<int>, TraversalOrder::PostOrder> bst, bst1;
    bst.insert(8);
    bst.insert(3);
    bst.insert(1);
    bst.insert(6);
    bst.insert(4);
    bst.insert(7);
    bst.insert(10);
    bst.insert(14);
    bst.insert(13);
    std::cout << *bst.lower_bound(4);
    BstContainer<std::string> a;
    a.insert("asd");
    a.insert("qweqwe");
    a.insert("zxc");
    a.insert("as");

    std::cout << "IntTree\n";
    std::cout << "Iterator\n";
    for (auto it = bst.begin(); it != bst.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\nReverseIterator\n";
    for (auto it = bst.rbegin(); it != bst.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\nConstIterator\n";
    for (auto it = bst.cbegin(); it != bst.cend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\nConstReverseIterator\n";
    for (auto it = bst.crbegin(); it != bst.crend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\nStringTree\n";
    for (auto it = a.begin(); it != a.end(); ++it)
        std::cout << *it << " ";
}
