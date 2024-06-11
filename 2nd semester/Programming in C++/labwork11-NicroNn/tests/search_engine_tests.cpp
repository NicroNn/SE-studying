#include <vector>
#include <gtest/gtest.h>
#include "lib/search.h"
std::string path_to_index = "../../index.txt";

TEST(SearchTestSuit, Test1) {
    std::vector<std::string> files;
    std::unordered_map<std::string, std::vector<std::pair<double, int>>> index;
    std::string query = "habr";
    std::vector<std::pair<std::string, std::string>> correctRes = {{"../../README.md", "10.289600"}};

    ASSERT_EQ(search(path_to_index, files, index, query), correctRes);
}

TEST(SearchTestSuit, Test2) {
    std::vector<std::string> files;
    std::unordered_map<std::string, std::vector<std::pair<double, int>>> index;
    std::string query = "classroom";
    std::vector<std::pair<std::string, std::string>> correctRes = {{"../../README.md", "12.241400"}};

    ASSERT_EQ(search(path_to_index, files, index, query), correctRes);
}

TEST(SearchTestSuit, Test3) {
    std::vector<std::string> files;
    std::unordered_map<std::string, std::vector<std::pair<double, int>>> index;
    std::string query = "wordinfo";
    std::vector<std::pair<std::string, std::string>> correctRes = {{"../../lib\\search.h", "13.053100"}};

    ASSERT_EQ(search(path_to_index, files, index, query), correctRes);
}
