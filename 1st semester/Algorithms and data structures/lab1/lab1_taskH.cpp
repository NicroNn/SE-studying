#include <iostream>

long countBlocks(long rooms[], long n, long st) {
    long blocks = 0;
    long s = rooms[st];
    long curr = st + 1;
    long firBl = -1;
    int loop = 0;
    while ((curr < n && loop < 1) || ((curr <= firBl) && (loop == 1))){
        if (curr >= n){curr = curr % n;}
        if ((s & rooms[curr]) == 0){s |= rooms[curr];}
        else {
            if (curr != firBl){blocks++; }
            if (firBl == -1){firBl = curr;}
            s = rooms[curr];
        }
        curr++;
        if (curr + 1 > n) {
            curr = 0;
            loop++;
        }
    }
    return blocks;
}


int main(){
    long n, blocks;
    std::cin >> n;
    long rooms[n];
    blocks = 0;
    for (int i = 0; i < n; i++){
        std::cin >> rooms[i];
    }
    blocks = countBlocks(rooms, n, 0);
    for (int i = 1; i < 31; i++){
        if (n / 2 < i + 1) { break;}
        if (blocks > countBlocks(rooms, n, i)) {
            blocks = countBlocks(rooms, n, i);
        }
    }
    if (blocks == 0) {blocks = 1;}
    std::cout << blocks;
}
