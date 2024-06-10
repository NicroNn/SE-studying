#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>
#include <climits>

struct Participant {
    int team_;
    int isu_;
    int score_;
};

int hashing(int k, int n) {
    return (k * 17) % n;
}

int main() {

    std::unordered_map<int, std::vector<Participant>> participants;
    int size, queries;
    std::cin >> size >> queries;

    char op;
    std::vector<int> result;
    int team, id, score;

    for (int i = 0; i < queries; ++i) {
        std::cin >> op;
        if (op == 'a') {
            std::cin >> team;
            int total_score = 0;
            int count = 0;

            for (const auto& p : participants[hashing(team, size)]) {
                if (p.team_ == team) {
                    total_score += p.score_;
                    count++;
                }
            }

            result.push_back(count == 0 ? 0 : total_score / count);
        }

        if (op == '-') {
            std::cin >> team >> id;
            for (auto& p : participants[hashing(team, size)]) {
                if (p.isu_ == id) {
                    p = {};
                    break;
                }
            }
        }

        if (op == '+') {
            std::cin >> team >> id >> score;
            participants[hashing(team, size)].push_back({team, id, score });
        }

        if (op == 'm') {
            std::cin >> team;
            int max_score = INT_MIN;
            for (const auto& p : participants[hashing(team, size)]) {
                if (p.team_ == team && p.score_ > max_score) {
                    max_score = p.score_;
                }
            }
            result.push_back(max_score);
        }
    }

    for (int x : result) {
        std::cout << x << '\n';
    }
}
