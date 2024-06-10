#include <iostream>

int main(){
    long t, n, num, higher, lower;
    char s, tr;
    std::cin >> t;
    for (int i = 0; i < t; i++){
        std::cin >> n;
        lower = 15;
        higher = 30;
        for (int j = 0 ; j < n; j++){
            std::cin >> s >> tr >> num;
            if (s == '>' && num > lower){
                lower = num;
            }
            if (s == '<' && num < higher){
                higher = num;
            }
            if (lower <= higher){
                std::cout << lower << "\n";
            } else {
                std::cout << -1 << "\n";
            }
        }
    }
}

