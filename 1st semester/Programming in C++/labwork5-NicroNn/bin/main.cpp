#include <lib/ThreeDArray.h>


int main(int argc, char** argv) {
    ThreeDArray arr = ThreeDArray::make_array(2, 2, 2);
    ThreeDArray arr2 = ThreeDArray::make_array(2, 2, 2);
    //arr(1, 1, 1) = 5;
    //arr2(1, 1, 1) = 6;
    arr[1][1][1] = 6553;
    arr[0][0][0] = 7;
    std::cout << arr << '\n' << arr[0][0][0];
}
