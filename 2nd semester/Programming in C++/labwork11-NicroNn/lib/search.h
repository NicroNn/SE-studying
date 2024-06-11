#ifndef LABWORK11_NICRONN_LIB_SEARCH_H_
#define LABWORK11_NICRONN_LIB_SEARCH_H_
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
#include <cctype>
#include <algorithm>
#include <queue>
#include <set>
#include <stack>

std::vector<std::string> readTokens(const std::string& text) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream token_stream(text);
    while (token_stream >> token) {
        transform(token.begin(), token.end(), token.begin(), ::tolower);
        token.erase(remove_if(token.begin(), token.end(), ::ispunct), token.end());
        tokens.push_back(token);
    }
    return tokens;
}

bool validateQuery(const std::string& query) {
    std::istringstream iss(query);
    std::string token;
    bool lastWasOperator = true;
    int parensBalance = 0;

    while (iss >> token) {
        if (token == "AND" || token == "OR") {
            if (lastWasOperator) return false;
            lastWasOperator = true;
        } else if (token == "(") {
            parensBalance++;
            lastWasOperator = true;
        } else if (token == ")") {
            parensBalance--;
            if (parensBalance < 0) return false;
            lastWasOperator = false;
        } else {
            lastWasOperator = false;
        }
    }
    return parensBalance == 0 && !lastWasOperator;
}

std::unordered_map<int, double> getFiles(const std::vector<std::string>& query,
                                         const std::unordered_map<std::string,
                                                                  std::vector<std::pair<double, int>>>& index,
                                         int start, int end) {
    std::unordered_map<int, double> relevance;
    std::set<int> found_docs;

    std::stack<std::unordered_map<int, double>> operands;
    std::stack<char> operators;

    if (start > end) {
        return {};
    }
    for (int i = start; i <= end; ++i) {
        if (query[i] == "(") {
            int j = i + 1;
            int brackets = 1;
            while (brackets != 0 && j <= end) {
                if (query[j] == "(") brackets++;
                else if (query[j] == ")") brackets--;
                j++;
            }
            std::unordered_map<int, double> sub_result = getFiles(query, index, i + 1, j - 2);
            operands.push(sub_result);
            i = j - 1;
        } else if (query[i] == "and" || query[i] == "or") {
            operators.push(query[i][0]);
        } else {
            auto it = index.find(query[i]);
            if (it != index.end()) {
                std::unordered_map<int, double> term_result;
                for (const auto& [weight, docID] : it->second) {
                    term_result[docID] += weight;
                    if (i == start) {
                        found_docs.insert(docID);
                    }
                }
                operands.push(term_result);
            }
        }
    }

    while (!operators.empty()) {
        char op = operators.top();
        operators.pop();

        std::unordered_map<int, double> right_operand = operands.top();
        operands.pop();
        std::unordered_map<int, double> left_operand = operands.top();
        operands.pop();

        std::unordered_map<int, double> result;
        if (op == 'a') {
            for (const auto& [docID, score] : left_operand) {
                auto it = right_operand.find(docID);
                if (it != right_operand.end()) {
                    result[docID] = score * it->second;
                }
            }
        } else {
            result = left_operand;
            for (const auto& [docID, score] : right_operand) {
                result[docID] += score;
            }
        }

        operands.push(result);
    }

    std::unordered_map<int, double> final_result;
    if (!found_docs.empty()) {
        for (const auto& [docID, score] : operands.top()) {
            if (found_docs.find(docID) != found_docs.end()) {
                final_result[docID] = score;
            }
        }
    } else {
        final_result = operands.top();
    }

    return final_result;
}

void parseIndexFile(const std::string& indexFilePath, std::vector<std::string>& documents,
                    std::unordered_map<std::string, std::vector<std::pair<double, int>>>& index) {
    std::string line;
    std::ifstream file(indexFilePath);

    if (file.is_open()) {
        while (getline(file, line)) {
            line.erase(remove(line.begin(), line.end(), '@'), line.end());
            std::istringstream iss(line);
            std::string doc;
            while (iss >> doc) {
                documents.push_back(doc);
            }
            break;
        }
        while (getline(file, line)) {
            std::istringstream iss(line);
            std::string term;
            iss >> term;
            std::vector<std::pair<double, int>> postings;
            double weight;
            int docID;
            while (iss >> weight >> docID) {
                postings.emplace_back(weight, docID);
            }
            index[term] = postings;
        }
        file.close();
    } else {
        throw std::runtime_error("Index file not present.");
    }
}

std::vector<std::pair<std::string, std::string>> search(const std::string& indexFilePath, std::vector<std::string>& documents,
                  std::unordered_map<std::string, std::vector<std::pair<double, int>>>& index, std::string& query) {
    std::vector<std::pair<std::string, std::string>> res;
    parseIndexFile(indexFilePath, documents, index);
    transform(query.begin(), query.end(), query.begin(), ::tolower);
    std::vector<std::string> query_tokens = readTokens(query);

    std::unordered_map<int, double> result = getFiles(query_tokens, index, 0, query_tokens.size() - 1);
    std::priority_queue<std::pair<double, int>> ranked_results;

    if (result.empty()) {
        std::cout << "No results found!\n";
    } else {
        for (const auto& [docID, score] : result) {
            ranked_results.push({score, docID});
        }

        int resultsCount = std::min(50, static_cast<int>(ranked_results.size()));
        for (int i = 0; i < resultsCount; ++i) {
            res.push_back({documents[ranked_results.top().second], std::to_string(ranked_results.top().first)});
            std::cout << documents[ranked_results.top().second] << " " << ranked_results.top().first << std::endl;
            ranked_results.pop();
        }
    }

    return res;
}

#endif //LABWORK11_NICRONN_LIB_SEARCH_H_
