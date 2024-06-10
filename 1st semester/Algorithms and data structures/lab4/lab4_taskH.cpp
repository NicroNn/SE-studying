#include <iostream>
#include <cstring>

void sum(char num1[], char num2[]) {
  int len = strlen(num2);
  for (int i = 0; i < len; ++i) {
    int digit = (num2[len - 1 - i] - '0') + num1[i];
    num1[i + 1] += digit / 10;
    num1[i] = digit % 10;
  }
  for (int i = len; i < 1201; ++i) {
    num1[i + 1] += num1[i] / 10;
    num1[i] = num1[i] % 10;
    if (num1[i + 1] <= 9) {
      break;
    }
  }
}

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  int n;
  std::cin >> n;
  char res[1201]{};
  for (int i = 0; i < n; ++i) {
    char curNum[1201]{};
    std::cin >> curNum;
    sum(res, curNum);
  }
  bool numBegun = false;
  for (int i = 1200; i >= 0; --i) {
    if (res[i] != 0){
      numBegun = true;
    }
    if (numBegun){
      std::cout << unsigned (res[i]);
    }
  }
}
