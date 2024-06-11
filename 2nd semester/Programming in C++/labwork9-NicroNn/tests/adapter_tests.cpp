#include <gtest/gtest.h>
#include "lib/adapters.h"

TEST(SoloAdapterSuit, TransformAdapter) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    auto result = v | transform(v, [](int x) { return x * x; });
    std::vector<int> expected = {1, 4, 9, 16, 25};
    ASSERT_EQ(result, expected);
}

TEST(SoloAdapterSuit, FilterAdapter) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    auto result = v | filter(v, [](int x) { return x % 2 == 0; });
    std::vector<int> expected = {2, 4};
    ASSERT_EQ(result, expected);
}

TEST(SoloAdapterSuit, TakeAdapter) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    auto result = v | take(v, 3);
    std::vector<int> expected = {1, 2, 3};
    ASSERT_EQ(result, expected);
}

TEST(SoloAdapterSuit, DropAdapter) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    auto result = v | drop(v, 2);
    std::vector<int> expected = {3, 4, 5};
    ASSERT_EQ(result, expected);
}

TEST(SoloAdapterSuit, ReverseAdapter) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    auto result = v | reverse(v);
    std::vector<int> expected = {5, 4, 3, 2, 1};
    ASSERT_EQ(result, expected);
}

TEST(SoloAdapterSuit, KeysAdapter) {
    std::map<int, std::string> m = {{1, "one"}, {2, "two"}, {3, "three"}};
    auto result = m | keys(m);
    std::vector<int> expected = {1, 2, 3};
    ASSERT_EQ(result, expected);
}

TEST(SoloAdapterSuit, ValuesAdapter) {
    std::map<int, std::string> m = {{1, "one"}, {2, "two"}, {3, "three"}};
    auto result = m | values(m);
    std::vector<std::string> expected = {"one", "two", "three"};
    ASSERT_EQ(result, expected);
}

TEST(DuoAdapterSuit, FilterAndTransform) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    auto result = v | filter(v, [](int x) { return x % 2 == 0; }) | transform(v, [](int x) { return x * x; });
    std::vector<int> expected = {4, 16};
    ASSERT_EQ(result, expected);
}

TEST(DuoAdapterSuit, TakeAndReverse) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    auto result = v | take(v, 3) | reverse(v);
    std::vector<int> expected = {3, 2, 1};
    ASSERT_EQ(result, expected);
}

TEST(DuoAdapterSuit, KeysAndValues) {
    std::map<int, std::string> m = {{1, "one"}, {2, "two"}, {3, "three"}};
    auto keysResult = m | keys(m);
    auto valuesResult = m | values(m);
    std::vector<int> expectedKeys = {1, 2, 3};
    std::vector<std::string> expectedValues = {"one", "two", "three"};
    ASSERT_EQ(keysResult, expectedKeys);
    ASSERT_EQ(valuesResult, expectedValues);
}

TEST(KillFicha, DeadlyTest) {
    std::vector<int> v = {1, 2, 3, 4, 5, 6};

    for (auto i : v | transform([](int i){ return i * i; }) | reverse(v) | filter([](int i){ return i % 2;})) {
        std::cout << i << ' ';
    }

    auto result = v | transform([](int i){ return i * i; }) | reverse(v) | filter([](int i){ return i % 2;});
    for (auto el : result) {
        std::cout << el << ' ';
    }

    ASSERT_EQ(result.size, 3);

}
