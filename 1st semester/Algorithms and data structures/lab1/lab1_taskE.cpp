#include <iostream>

int main(){
    long n, left, right;
    int err = 0;
    left = 0;
    std::cin >> n;
    right = n - 1;

    char word[n];

    for (int i = 0; i < n; i++) {
        std::cin >> word[i];
    }

    while (left < n / 2 + 1 && right > n / 2 - 1){
        if (word[left] == word[right]){
            left++;
            right--;
        } else {
            if (err == 0) {
                err++;
                if (word[left + 1] == word[right]){
                    left++;
                }
                if (word[left] == word[right - 1]){
                    right--;
                }
            } else {
            std::cout << "NO";
            err++;
            break;
            }
        }
    }
    if (err <= 1){std::cout << "YES";}
}
