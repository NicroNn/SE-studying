#include <iostream>

int main(){
    long n, left, right, target;
    std::cin >> n;
    long days[n];
    for (int i = 0; i < n; i++){
        std::cin >> days[i];
    }

    left = 0;
    right = 0;
    for (int i = 1; i < n; i++){
        right += days[i];
    }
    target = 0;
    while (left != right && target < n){
        target++;
        left += days[target - 1];
        right -= days[target];
    }
    if (left == right) {
        std::cout << target;
    } else {
        std::cout << "-1";
    }
}
