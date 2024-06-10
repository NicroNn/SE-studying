#include <iostream>
#include <cmath>

double findX(double c) {
    double left = 0, right = c, mid, precision = 1e-7;
    while (right - left > precision) {
        mid = left + (right - left) / 2;
        double value = mid * mid + sqrt(mid);

        if (value < c) {
            left = mid;
        } else {
            right = mid;
        }
    }
    return mid;
}

int main() {
    double c;
    std::cin >> c;
    std::cout.precision(7);
    std::cout << std::fixed << findX(c);
}
