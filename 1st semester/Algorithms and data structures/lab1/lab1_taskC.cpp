#include <iostream>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main(){
    long a, b;
    std::cin >> a >> b;
    std::cout << gcd(a, b);
}