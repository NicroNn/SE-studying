#include <iostream>
#include <string>

bool compareRLE(const std::string& rle1, const std::string& rle2, int maxDiff) {
    int i = 0, j = 0;
    int diff = 0;
    int count1 = 0, count2 = 0;
    char currentChar1 = 0, currentChar2 = 0;

    while (i < rle1.size() && j < rle2.size() && diff <= maxDiff) {
        if (count1 == 0) {
            currentChar1 = rle1[i++];
            while (i < rle1.size() && isdigit(rle1[i])) {
                count1 = count1 * 10 + (rle1[i++] - '0');
            }
        }

        if (count2 == 0) {
            currentChar2 = rle2[j++];
            while (j < rle2.size() && isdigit(rle2[j])) {
                count2 = count2 * 10 + (rle2[j++] - '0');
            }
        }

        int minCount = std::min(count1, count2);
        count1 -= minCount;
        count2 -= minCount;

        if (currentChar1 != currentChar2) {
            diff += minCount;
        }
    }

    while (i < rle1.size()) {
        if (!isdigit(rle1[i])) {
            diff += rle1[i + 1] - '0';
        }
        i += 2;
    }

    while (j < rle2.size()) {
        if (!isdigit(rle2[j])) {
            diff += rle2[j + 1] - '0';
        }
        j += 2;
    }

    return diff <= maxDiff;
}

int main() {
    int len1, len2, maxDiff;
    std::cin >> len1 >> len2 >> maxDiff;

    std::string rle1, rle2;
    std::cin >> rle1 >> rle2;

    if (compareRLE(rle1, rle2, maxDiff)) {
        std::cout << "Yes";
    } else {
        std::cout << "No";
    }
}
