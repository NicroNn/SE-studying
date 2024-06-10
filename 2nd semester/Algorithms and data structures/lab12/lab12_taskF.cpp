#include<iostream>
#include<string>
#include<vector>

const int mod = 998244353;

int hash1(const std::string& s, int n) {
    int str = 0;
    for (auto i : s) {
        str += str * 137 + i;
    }
    return str % int(1e6 + 1);
}

int hash2(const std::string& s, int n) {
    int str = 0;
    for (auto i : s) {
        str += str * 137 + i;
    }
    return (str + 191) % int(1e6 + 1);
}

void insert(std::vector<std::string>& arr, std::string& str, int n) {
    int first_hash = hash1(str, n);
    int second_hash = hash2(str, n);

    if (arr[first_hash].empty()) {
        arr[first_hash] = str;
    } else if (arr[second_hash].empty()) {
        arr[second_hash] = str;
    } else {
        arr[first_hash] = str;
        while (!arr[first_hash].empty() && arr[first_hash] != str) {
            if (hash1(arr[first_hash], n) == first_hash) {
                swap(arr[hash2(arr[first_hash], n)], arr[first_hash]);
            } else {
                swap(arr[hash1(arr[first_hash], n)], arr[first_hash]);
            }
        }

        arr[second_hash] = str;
        while (!arr[second_hash].empty() && arr[second_hash] != str) {
            if (hash1(arr[second_hash], n) == first_hash) {
                swap(arr[hash2(arr[second_hash], n)], arr[second_hash]);
            } else {
                swap(arr[hash1(arr[second_hash], n)], arr[second_hash]);
            }
        }
    }
}

bool is_correct(std::vector<std::string>& a, const std::string& str, int n) {
    return (a[hash1(str, n)] == str) || (a[hash2(str, n)] == str);
}

int main() {
    int n;
    std::string s;
    std::cin >> n;

    std::vector<std::string> first_table(1e6 + 1);
    std::vector<std::string> second_table(1e6 + 1);
    std::vector<std::string> third_table(1e6 + 1);
    std::vector<std::string> first;
    std::vector<std::string> second;
    std::vector<std::string> third;
    std::vector<int> ans = {0, 0, 0};

    for (int i = 0; i < n; ++i) {
        std::cin >> s;
        insert(first_table, s, n);
        first.push_back(s);
    }

    for (int i = 0; i < n; ++i) {
        std::cin >> s;
        insert(second_table, s, n);
        second.push_back(s);
    }

    for (int i = 0; i < n; ++i) {
        std::cin >> s;
        insert(third_table, s, n);
        third.push_back(s);
    }

    std::string cur;
    for (int i = 0; i < n; ++i) {
        cur = first[i];
        if (!is_correct(second_table, cur, n) && !is_correct(third_table, cur, n)) {
            ans[0] += 3;
        } else if (is_correct(second_table, cur, n) && is_correct(third_table, cur, n)) {
            ans[0] += 0;
        } else ans[0] += 1;
    }

    for (int i = 0; i < n; ++i) {
        cur = second[i];
        if (!is_correct(first_table, cur, n) && !is_correct(third_table, cur, n)) {
            ans[1] += 3;
        } else if (is_correct(first_table, cur, n) && is_correct(third_table, cur, n)) {
            ans[1] += 0;
        } else ans[1] += 1;
    }

    for (int i = 0; i < n; ++i) {
        cur = third[i];
        if (!is_correct(first_table, cur, n) && !is_correct(second_table, cur, n)) {
            ans[2] += 3;
        } else if (is_correct(first_table, cur, n) && is_correct(second_table, cur, n)) {
            ans[2] += 0;
        } else ans[2] += 1;
    }

    std::cout << ans[0] << ' ' << ans[1] << ' ' << ans[2];
}