#include <iostream>

int main() {
    long n, k, temp;
    std::cin >> n >> k;
    long nums[n];
    if (abs(k) > n){k %= n;}
    if (k < 0){k = n + k;}

    for (int i = 0; i < n; i++) {
        std::cin >> nums[i];
    }

    for (int i = 0; i < k; ++i) {
        temp = nums[n - 1];
        for (int j = n - 2; j >= 0; j--) {
            nums[j + 1] = nums[j];
        }
        nums[0] = temp;
    }

    for (int i = 0; i < n; i++) {
        std::cout << nums[i] << " ";
    }
}

