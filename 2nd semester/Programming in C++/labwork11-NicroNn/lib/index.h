#ifndef LABWORK11_NICRONN_LIB_INDEX_H_
#define LABWORK11_NICRONN_LIB_INDEX_H_
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <filesystem>
#include <cmath>
#include <map>
#include <regex>

namespace fs = std::filesystem;

struct File {
    std::string id;
    long length{};
    std::unordered_map<std::string, int> term_frequency;
};

std::regex wordRegex(R"([a-zA-Z_]\w*|[.-_*])");

std::vector<std::string> getTokens(const std::string& text) {
    std::vector<std::string> tokens;
    auto words_begin = std::sregex_iterator(text.begin(), text.end(), wordRegex);
    auto words_end = std::sregex_iterator();

    for (auto it = words_begin; it != words_end; ++it) {
        std::string token = it->str();
        std::transform(token.begin(), token.end(), token.begin(), ::tolower);
        tokens.push_back(token);
    }
    return tokens;
}

double getWeight(double k1, double b, long tf, long dl, double avg_dl, int n, int df) {
    double idf = log((n - df + 0.5) / (df + 0.5) + 1);
    double tf_weight = ((k1 + 1) * tf) / (k1 * ((1 - b) + b * dl / avg_dl) + tf);
    return idf * tf_weight;
}

void processFile(const fs::path& filePath, std::vector<File>& files) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filePath << std::endl;
        return;
    }

    File doc;
    doc.id = filePath.string();
    doc.length = 0;
    std::string line;

    while (std::getline(file, line)) {
        std::vector<std::string> tokens = getTokens(line);
        for (const auto& token : tokens) {
            doc.term_frequency[token]++;
            doc.length++;
        }
    }
    files.push_back(doc);
}

void calculateIndex(std::unordered_map<std::string, std::unordered_map<int, double>>& index, std::vector<File>& files) {
    double avg_doc_length = 0;
    for (const auto& doc : files) {
        avg_doc_length += doc.length;
    }
    avg_doc_length /= files.size();

    double k1 = 1.25;
    double b = 0.75;
    for (int i = 0; i < files.size(); ++i) {
        for (const auto& [term, freq] : files[i].term_frequency) {
            double weight = getWeight(k1, b, freq, files[i].length, avg_doc_length, files.size(), index[term].size());
            index[term][i] = weight;
        }
    }
}

void traverseDirectory(const fs::path& directory, std::vector<File>& files,
                       std::unordered_map<std::string, std::unordered_map<int, double>>& index) {
    for (const auto& entry : fs::recursive_directory_iterator(directory)) {
        if (entry.is_regular_file()) {
            processFile(entry.path(), files);
        }
    }
    calculateIndex(index, files);
}

void saveIndex(const std::vector<File>& files, const std::unordered_map<std::string, std::unordered_map<int, double>>& index,
               const std::string& outputFilePath) {
    std::ofstream outputFile(outputFilePath);
    if (!outputFile.is_open()) {
        std::cerr << "Unable to open output file" << std::endl;
        return;
    }

    for (const auto& doc : files) {
        outputFile << "@" << doc.id << " ";
    }
    outputFile << std::endl;

    for (const auto& [term, postings] : index) {
        outputFile << term;
        for (const auto& [docID, weight] : postings) {
            outputFile << " " << weight << " " << docID;
        }
        outputFile << std::endl;
    }
}

#endif //LABWORK11_NICRONN_LIB_INDEX_H_
