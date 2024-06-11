#include "../lib/bst.h"
#include <gtest/gtest.h>

TEST(InOrderTestSuit, Iterator) {
    BstContainer<int, std::less<>, std::allocator<int>, TraversalOrder::InOrder> bst;
    bst.insert(8);
    bst.insert(3);
    bst.insert(1);
    bst.insert(6);
    bst.insert(4);
    bst.insert(7);
    bst.insert(10);
    bst.insert(14);
    bst.insert(13);

    std::ostringstream stream;

    for (auto it = bst.begin(); it != bst.end(); ++it) {
        stream << *it << " ";
    }

    ASSERT_EQ(stream.str(), "1 3 4 6 7 8 10 13 14 ");
}

TEST(InOrderTestSuit, ReverseIterator) {
    BstContainer<int, std::less<>, std::allocator<int>, TraversalOrder::InOrder> bst;
    bst.insert(8);
    bst.insert(3);
    bst.insert(1);
    bst.insert(6);
    bst.insert(4);
    bst.insert(7);
    bst.insert(10);
    bst.insert(14);
    bst.insert(13);

    std::ostringstream stream;

    for (auto it = bst.rbegin(); it != bst.rend(); ++it) {
        stream << *it << " ";
    }

    ASSERT_EQ(stream.str(), "14 13 10 8 7 6 4 3 1 ");
}

TEST(InOrderTestSuit, ConstIterator) {
    BstContainer<int, std::less<>, std::allocator<int>, TraversalOrder::InOrder> bst;
    bst.insert(8);
    bst.insert(3);
    bst.insert(1);
    bst.insert(6);
    bst.insert(4);
    bst.insert(7);
    bst.insert(10);
    bst.insert(14);
    bst.insert(13);

    std::ostringstream stream;

    for (auto it = bst.cbegin(); it != bst.cend(); ++it) {
        stream << *it << " ";
    }

    ASSERT_EQ(stream.str(), "1 3 4 6 7 8 10 13 14 ");
}

TEST(InOrderTestSuit, ConstReverseIterator) {
    BstContainer<int, std::less<>, std::allocator<int>, TraversalOrder::InOrder> bst;
    bst.insert(8);
    bst.insert(3);
    bst.insert(1);
    bst.insert(6);
    bst.insert(4);
    bst.insert(7);
    bst.insert(10);
    bst.insert(14);
    bst.insert(13);

    std::ostringstream stream;

    for (auto it = bst.crbegin(); it != bst.crend(); ++it) {
        stream << *it << " ";
    }

    ASSERT_EQ(stream.str(), "14 13 10 8 7 6 4 3 1 ");
}

TEST(PreOrderTestSuit, Iterator) {
    BstContainer<int, std::less<>, std::allocator<int>, TraversalOrder::PreOrder> bst;
    bst.insert(8);
    bst.insert(3);
    bst.insert(1);
    bst.insert(6);
    bst.insert(4);
    bst.insert(7);
    bst.insert(10);
    bst.insert(14);
    bst.insert(13);

    std::ostringstream stream;

    for (auto it = bst.begin(); it != bst.end(); ++it) {
        stream << *it << " ";
    }

    ASSERT_EQ(stream.str(), "8 3 1 6 4 7 10 14 13 ");
}

TEST(PreOrderTestSuit, ReverseIterator) {
    BstContainer<int, std::less<>, std::allocator<int>, TraversalOrder::PreOrder> bst;
    bst.insert(8);
    bst.insert(3);
    bst.insert(1);
    bst.insert(6);
    bst.insert(4);
    bst.insert(7);
    bst.insert(10);
    bst.insert(14);
    bst.insert(13);

    std::ostringstream stream;

    for (auto it = bst.rbegin(); it != bst.rend(); ++it) {
        stream << *it << " ";
    }

    ASSERT_EQ(stream.str(), "13 14 10 7 4 6 1 3 8 ");
}

TEST(PreOrderTestSuit, ConstIterator) {
    BstContainer<int, std::less<>, std::allocator<int>, TraversalOrder::PreOrder> bst;
    bst.insert(8);
    bst.insert(3);
    bst.insert(1);
    bst.insert(6);
    bst.insert(4);
    bst.insert(7);
    bst.insert(10);
    bst.insert(14);
    bst.insert(13);

    std::ostringstream stream;

    for (auto it = bst.cbegin(); it != bst.cend(); ++it) {
        stream << *it << " ";
    }

    ASSERT_EQ(stream.str(), "8 3 1 6 4 7 10 14 13 ");
}

TEST(PreOrderTestSuit, ConstReverseIterator) {
    BstContainer<int, std::less<>, std::allocator<int>, TraversalOrder::PreOrder> bst;
    bst.insert(8);
    bst.insert(3);
    bst.insert(1);
    bst.insert(6);
    bst.insert(4);
    bst.insert(7);
    bst.insert(10);
    bst.insert(14);
    bst.insert(13);

    std::ostringstream stream;

    for (auto it = bst.crbegin(); it != bst.crend(); ++it) {
        stream << *it << " ";
    }

    ASSERT_EQ(stream.str(), "13 14 10 7 4 6 1 3 8 ");
}

TEST(PostOrderTestSuit, Iterator) {
    BstContainer<int, std::less<>, std::allocator<int>, TraversalOrder::PostOrder> bst;
    bst.insert(8);
    bst.insert(3);
    bst.insert(1);
    bst.insert(6);
    bst.insert(4);
    bst.insert(7);
    bst.insert(10);
    bst.insert(14);
    bst.insert(13);

    std::ostringstream stream;

    for (auto it = bst.begin(); it != bst.end(); ++it) {
        stream << *it << " ";
    }

    ASSERT_EQ(stream.str(), "1 4 7 6 3 13 14 10 8 ");
}

TEST(PostOrderTestSuit, ReverseIterator) {
    BstContainer<int, std::less<>, std::allocator<int>, TraversalOrder::PostOrder> bst;
    bst.insert(8);
    bst.insert(3);
    bst.insert(1);
    bst.insert(6);
    bst.insert(4);
    bst.insert(7);
    bst.insert(10);
    bst.insert(14);
    bst.insert(13);

    std::ostringstream stream;

    for (auto it = bst.rbegin(); it != bst.rend(); ++it) {
        stream << *it << " ";
    }

    ASSERT_EQ(stream.str(), "8 10 14 13 3 6 7 4 1 ");
}

TEST(PostOrderTestSuit, ConstIterator) {
    BstContainer<int, std::less<>, std::allocator<int>, TraversalOrder::PostOrder> bst;
    bst.insert(8);
    bst.insert(3);
    bst.insert(1);
    bst.insert(6);
    bst.insert(4);
    bst.insert(7);
    bst.insert(10);
    bst.insert(14);
    bst.insert(13);

    std::ostringstream stream;

    for (auto it = bst.cbegin(); it != bst.cend(); ++it) {
        stream << *it << " ";
    }

    ASSERT_EQ(stream.str(), "1 4 7 6 3 13 14 10 8 ");
}

TEST(PostOrderTestSuit, ConstReverseIterator) {
    BstContainer<int, std::less<>, std::allocator<int>, TraversalOrder::PostOrder> bst;
    bst.insert(8);
    bst.insert(3);
    bst.insert(1);
    bst.insert(6);
    bst.insert(4);
    bst.insert(7);
    bst.insert(10);
    bst.insert(14);
    bst.insert(13);

    std::ostringstream stream;

    for (auto it = bst.crbegin(); it != bst.crend(); ++it) {
        stream << *it << " ";
    }

    ASSERT_EQ(stream.str(), "8 10 14 13 3 6 7 4 1 ");
}

TEST(BstTestSuit, Insert) {
    BstContainer<int> bst;
    bst.insert(5);
    ASSERT_EQ(bst.size(), 1);
    ASSERT_FALSE(bst.empty());
}

TEST(BstTestSuit, CopyConstructor) {
    BstContainer<int> bst;
    bst.insert(5);
    bst.insert(10);
    BstContainer<int> copy_bst(bst);
    ASSERT_EQ(copy_bst.size(), bst.size());
    ASSERT_EQ(copy_bst.count(5), 1);
    ASSERT_EQ(copy_bst.count(10), 1);
}

TEST(BstTestSuit, MoveConstructor) {
    BstContainer<int> bst;
    bst.insert(5);
    bst.insert(10);
    BstContainer<int> moved_bst(std::move(bst));
    ASSERT_EQ(moved_bst.size(), 2);
    ASSERT_EQ(bst.size(), 0);
}

TEST(BstTestSuit, CopyAssignmentOperator) {
    BstContainer<int> bst;
    bst.insert(5);
    bst.insert(10);
    BstContainer<int> another_bst;
    another_bst = bst;
    ASSERT_EQ(another_bst.size(), bst.size());
    ASSERT_EQ(another_bst.count(5), 1);
    ASSERT_EQ(another_bst.count(10), 1);
}

TEST(BstTestSuit, MoveAssignmentOperator) {
    BstContainer<int> bst;
    bst.insert(5);
    bst.insert(10);
    BstContainer<int> another_bst;
    another_bst = std::move(bst);
    ASSERT_EQ(another_bst.size(), 2);
    ASSERT_EQ(bst.size(), 0);
}

TEST(BstTestSuit, Find) {
    BstContainer<int> bst;
    bst.insert(5);
    bst.insert(10);
    ASSERT_EQ(bst.find(5), bst.begin());
}

TEST(BstTestSuit, LowerBound) {
    BstContainer<int> bst;
    bst.insert(8);
    bst.insert(3);
    bst.insert(1);
    bst.insert(6);
    bst.insert(4);
    bst.insert(7);
    bst.insert(10);
    bst.insert(14);
    bst.insert(13);
    ASSERT_EQ(*bst.lower_bound(4), 4);
}

TEST(BstTestSuit, UpperBound) {
    BstContainer<int> bst;
    bst.insert(8);
    bst.insert(3);
    bst.insert(1);
    bst.insert(6);
    bst.insert(4);
    bst.insert(7);
    bst.insert(10);
    bst.insert(14);
    bst.insert(13);
    ASSERT_EQ(*bst.upper_bound(6), 7);
}

TEST(BstTestSuit, Erase) {
    BstContainer<int> bst;
    bst.insert(8);
    bst.insert(3);
    bst.insert(1);
    bst.insert(6);
    bst.insert(4);
    bst.insert(7);
    bst.insert(10);
    bst.insert(14);
    bst.insert(13);

    bst.erase(6);

    ASSERT_EQ(bst.count(6), 0);
}

TEST(BstTestSuit, InsertUnique) {
    BstContainer<int> bst;
    bst.insert_unique(8);
    bst.insert_unique(3);
    bst.insert_unique(1);
    bst.insert_unique(6);
    bst.insert_unique(4);
    bst.insert_unique(7);
    bst.insert_unique(10);
    bst.insert_unique(14);
    bst.insert_unique(13);

    bool result = bst.insert_unique(6);

    ASSERT_FALSE(result);
}

TEST(BstTestSuit, EqualRange) {
    BstContainer<int> bst;
    bst.insert(8);
    bst.insert(3);
    bst.insert(1);
    bst.insert(6);
    bst.insert(4);
    bst.insert(7);
    bst.insert(10);
    bst.insert(14);
    bst.insert(13);

    auto range = bst.equal_range(6);

    ASSERT_EQ(*range.first, 6);
    ASSERT_EQ(*range.second, 7);
}

TEST(BstTestSuit, Swap) {
    BstContainer<int> bst1;
    bst1.insert(8);
    bst1.insert(3);
    bst1.insert(1);

    BstContainer<int> bst2;
    bst2.insert(10);
    bst2.insert(14);
    bst2.insert(13);

    std::vector<int> expected_bst1 = {1, 3, 8};
    std::vector<int> expected_bst2 = {10, 13, 14};

    bst1.swap(bst2);

    std::vector<int> bst1_content;
    std::vector<int> bst2_content;

    for (auto& elem : bst1)
        bst1_content.push_back(elem);

    for (auto& elem : bst2)
        bst2_content.push_back(elem);

    ASSERT_EQ(bst1_content, expected_bst2);
    ASSERT_EQ(bst2_content, expected_bst1);
}

TEST(BstTestSuit, Merge) {
    BstContainer<int> bst1;
    bst1.insert(8);
    bst1.insert(3);
    bst1.insert(1);

    BstContainer<int> bst2;
    bst2.insert(10);
    bst2.insert(14);
    bst2.insert(13);

    std::ostringstream stream;

    bst1.merge(std::move(bst2));
    for (auto it = bst1.begin(); it != bst1.end(); ++it) {
        stream << *it << " ";
    }

    ASSERT_EQ(stream.str(), "1 3 8 10 13 14 ");
}