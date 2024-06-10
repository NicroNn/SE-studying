#include <iostream>
#include <numeric>


#define module 999999893

long long modex(long long a, long long b, long long m) {
    a = a % m;
    if (b == 0) {
        return 1;
    }
    long long temp = modex(a, b / 2, m);
    temp = (temp * temp) % m;
    if (b % 2) {
        temp = (temp * a) % m;
    }
    return temp;
}

long long mod(long long a, long long b, long long m) {
    a = a % m;
    b = b % m;
    long long c = std::gcd(a, b);
    a = a / c;
    b = b / c;
    c = modex(b, m - 2, m);
    return (a * c) % m;
}

int main() {
    long long n;
    std::cin >> n;

    long long b = modex(2, n / 2, module) - 1;
    long long a;
    if (n % 2) {
        a = modex(2, n / 2 + 1, module) - 1;
    } else {
        a = modex(2, n / 2, module) - 1;
    }

    long long temp = (a + 1) * (a + 1);
    temp %= module;
    temp -= 2 * b * b;
    temp %= module;

    long long answer = mod(2 * b, temp, module);
    answer += module;
    answer %= module;

    std::cout << answer << "\n";
}