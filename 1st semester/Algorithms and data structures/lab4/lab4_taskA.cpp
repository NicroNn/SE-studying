#include <iostream>

int main(){
  long n;
  bool isPyr = true;
  std::cin >> n;
  long* arr = new long[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }
  for (int i = 0; i < n; ++i) {
    if (2 * i + 1 < n && arr[i] > arr[2 * i + 1]) {
      std::cout << "NO";
      isPyr = false;
      break;
    }
    if (2 * i + 2 < n && arr[i] > arr[2 * i + 2]) {
      std::cout << "NO";
      isPyr = false;
      break;
    }
  }
  if (isPyr){
    std::cout << "YES";
  }
  delete[] arr;
}
