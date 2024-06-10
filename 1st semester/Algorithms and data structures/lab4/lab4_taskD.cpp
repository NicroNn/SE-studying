#include <iostream>
#include <vector>

struct City{
  long code;
  long rating;
  long fee;
};

void siftDownRating(std::vector<City>& heap, long i) {
  while (2 * i + 1 < heap.size()) {
    long l = 2 * i + 1;
    long r = 2 * i + 2;
    long j = l;

    if (r < heap.size() &&
        (heap[r].rating > heap[l].rating || (heap[r].rating == heap[l].rating && heap[r].code > heap[l].code))) {
      j = r;
    }

    if (heap[i].rating > heap[j].rating || (heap[i].rating == heap[j].rating && heap[i].code >= heap[j].code)) {
      break;
    }

    std::swap(heap[i], heap[j]);
    i = j;
  }
}

void extractMaxRating(std::vector<City>& heap) {
  if (heap.size() == 0){
    return;
  }
  City min = heap[0];
  heap[0] = heap.back();
  heap.pop_back();
  siftDownRating(heap, 0);
}

void heapifyRating(std::vector<City>& heap){
  for (int i = heap.size() / 2; i >= 0; --i) {
    siftDownRating(heap, i);
  }
}

void siftDownFee(std::vector<City>& heap, long i) {
  while (2 * i + 1 < heap.size()) {
    long l = 2 * i + 1;
    long r = 2 * i + 2;
    long j = l;

    if (r < heap.size() &&
        (heap[r].fee > heap[l].fee || (heap[r].fee == heap[l].fee && heap[r].code > heap[l].code))) {
      j = r;
    }

    if (heap[i].fee > heap[j].fee || (heap[i].fee == heap[j].fee && heap[i].code >= heap[j].code)) {
      break;
    }

    std::swap(heap[i], heap[j]);
    i = j;
  }
}


void extractMaxFee(std::vector<City>& heap) {
  if (heap.size() == 0){
    return;
  }
  City min = heap[0];
  heap[0] = heap.back();
  heap.pop_back();
  siftDownFee(heap, 0);
}

void heapifyFee(std::vector<City>& heap){
  for (int i = heap.size() / 2; i >= 0; --i) {
    siftDownFee(heap, i);
  }
}

int main(){
  long n;
  std::cin >> n;
  std::vector<City> citiesRatingHeap, citiesFeeHeap;
  std::vector<long> tour, askFeeIncrease;
  for (int i = 0; i < n; ++i) {
    City newCity{};
    std::cin >> newCity.code >> newCity.rating >> newCity.fee;
    citiesRatingHeap.push_back(newCity);
    citiesFeeHeap.push_back(newCity);
  }
  heapifyRating(citiesRatingHeap);
  heapifyFee(citiesFeeHeap);
  long m;
  std::cin >> m;
  int* answers = new int[m]{};
  for (int i = 0; i < m; ++i) {
    std::string answer;
    std::cin >> answer;
    if (answer == "YES"){
      answers[i] = 1;
    }
    if (answer == "NO"){
      answers[i] = 0;
    }
  }
  long curAnswerIndex = 0;
  while (!citiesRatingHeap.empty()){
    if (citiesRatingHeap[0].code == citiesFeeHeap[0].code){
      tour.push_back(citiesRatingHeap[0].code);
      extractMaxRating(citiesRatingHeap);
      extractMaxFee(citiesFeeHeap);
    } else {
      if (curAnswerIndex < m){
        askFeeIncrease.push_back(citiesRatingHeap[0].code);
        if (answers[curAnswerIndex]){
          tour.push_back(citiesRatingHeap[0].code);
        }
      }
      extractMaxRating(citiesRatingHeap);
      ++curAnswerIndex;
    }
  }
  for (long i : askFeeIncrease) {
    std::cout << i << ' ';
  }
  if (!askFeeIncrease.empty()){
    std::cout << '\n';
  }
  for (long i : tour) {
    std::cout << i << ' ';
  }
  delete[] answers;
}
