#include <iostream>
#include <cmath>

int main() {
    long a, b;
    std::cin >> a >> b;
    std::cout << a + b << std::endl;
    int power2 = 0;
    long num = 0;
    for (int l = 0; l < 1; l++){
        num += pow(2, power2);
        power2++;
    }
    for (int l = 0; l < 2; l++){
        power2++;
    }
    for (int l = 0; l < 1; l++){
        num += pow(2, power2);
        power2++;
    }
    std::cout << num;
    return 0;
}

