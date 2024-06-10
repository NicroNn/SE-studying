#include <iostream>

struct Card {
  std::string name = "";
  long dmg = 0;
};

void StructuresCountSort(Card* arr, long n) {
  long maxDmg = 100001;
  long count[maxDmg + 1];
  for (int i = 0; i < maxDmg + 1; ++i) {
    count[i] = 0;
  }
  for (long i = 0; i < n; ++i) {
    ++count[arr[i].dmg];
  }
  for (long i = 1; i <= maxDmg; ++i) {
    count[i] += count[i - 1];
  }
  Card* sortedArr = new Card[n];
  for (long i = n - 1; i >= 0; --i) {
    sortedArr[count[arr[i].dmg] - 1] = arr[i];
    --count[arr[i].dmg];
  }
  for (long i = 0; i < n; ++i) {
    arr[i] = sortedArr[i];
  }
  delete[] sortedArr;
}

int main() {
  long n;
  std::cin >> n;
  long* damages = new long[n];
  std::string* names = new std::string[n];
  Card* cards = new Card[n];
  Card current;
  for (long i = 0; i < n; ++i) {
    std::cin >> damages[i];
  }
  for (long i = 0; i < n; ++i) {
    std::cin >> names[i];
  }
  for (long i = 0; i < n; ++i) {
    current.dmg = damages[i];
    current.name = names[i];
    cards[i] = current;
  }

  StructuresCountSort(cards, n);

  for (long i = 0; i < n; ++i) {
    std::cout << cards[i].dmg;
    if (i < n - 1) {
      std::cout << ' ';
    } else {
      std::cout << '\n';
    }
  }
  for (long i = 0; i < n; ++i) {
    std::cout << cards[i].name;
    if (i < n - 1) {
      std::cout << ' ';
    } else {
      std::cout << '\n';
    }
  }

  long q;
  std::cin >> q;
  long l, r, result;
  std::string command;
  for (long i = 0; i < q; ++i) {
    std::cin >> command >> l >> r;
    result = 0;
    if (command == "Count") {
      for (long j = 0; j < n; ++j) {
        if (cards[j].dmg >= l && cards[j].dmg <= r) {
          ++result;
        }
      }
    }
    if (command == "Sum") {
      for (long j = 0; j < n; ++j) {
        if (cards[j].dmg >= l && cards[j].dmg <= r) {
          result += cards[j].dmg;
        }
      }
    }
    if (command == "Xor") {
      for (long j = 0; j < n; ++j) {
        if (cards[j].dmg >= l && cards[j].dmg <= r) {
          result = result xor cards[j].dmg;
        }
      }
    }
    std::cout << result << '\n';
  }

  delete[] damages;
  delete[] names;
  delete[] cards;
}
