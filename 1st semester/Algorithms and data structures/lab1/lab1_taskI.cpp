#include <iostream>
#include <cmath>

int main(){
    long x, y, kol;
    kol = 0;
    std::cin >> x >> y;
    for (int i = 1; i < 61; i++){
        for (int j = 1; j < 61; j++){
            for (int k = 1; k < 61; k++){
                int power2 = 0;
                double num = 0;
                for (int l = 0; l < k; l++){
                    num += pow(2, power2);
                    power2++;
                }
                for (int l = 0; l < j; l++){
                    power2++;
                }
                for (int l = 0; l < i; l++){
                    num += pow(2, power2);
                    power2++;
                }
                if ((x <= num) && (num <= y)) {kol++;}
            }
        }
    }
    std::cout << kol;
}
