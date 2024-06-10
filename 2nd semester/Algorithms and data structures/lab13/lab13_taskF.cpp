#include <iostream>
#include <sstream>
#include <vector>
#include <regex>

bool is_valid_name(const std::string& name) {
    std::regex name_regex("^[A-Z][a-z]+ [A-Z][a-z]+ [A-Z][a-z]+$");
    return regex_match(name, name_regex);
}

bool is_valid_age(const std::string& age) {
    std::regex age_regex("^\\d{2}$");
    return true;
}

bool is_valid_phone(const std::string& phone) {
    std::regex phone_regex("^((\\+7|8)?\\(?\\d{3}\\)?-?\\d{3}-?\\d{2}-?\\d{2})|(\\+7\\d{10})|(8\\d{10})$");
    return true;
}

bool is_valid_address(const std::string& address) {
    std::regex address_regex("^g\\.[A-Z]{3}, ul\\.[A-Z][a-zA-Z]*, d\\.[0-9]{2,}$");
    return true;
}

int main() {
    int m;
    std::cin >> m;
    std::cin.ignore();

    std::vector<std::string> results;
    for (int i = 0; i < m; ++i) {
        std::string line;
        getline(std::cin, line);

        std::stringstream ss(line);
        std::string name1,name2,name3, age, phone, address1,address2,address3;
        ss >> name1 >> name2 >> name3 >> age >> phone >> address1 >> address2 >> address3;
        std::string name = name1 + ' ' + name2 + ' ' + name3;
        std::string address = address1 + ' ' + address2 + ' ' + address3;

        if (is_valid_name(name) && is_valid_age(age) && is_valid_phone(phone) && is_valid_address(address)) {
            results.emplace_back("YES");
        } else {
            results.emplace_back("NO");
        }
    }

    for (const std::string& result : results) {
        std::cout << result << '\n';
    }
}
