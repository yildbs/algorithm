#include <stdio.h>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


int main()
{
    int T, N;
#if 0
    scanf("%d", &T);
    for(int t=0;t<T;t++){
        scanf("%d", &N);
#else
    for(int N=0;N<=60;N++){
        printf("%d ", N);
#endif

        int addh = N / 60;
        int addt = (N % 60) / 10;
        int mint = 0;
        int addo = (N % 10);
        int mino = 0;

        if(N % 10 > 5){
            addt += 1;
            mino = 10 - addo;
            addo = 0;
        }
        if(N % 60 >= 36){
            addh += 1;
            mint = 6 - addt;
            addt = 0;
        }
        if(N % 60 == 45){
            addt = 0;
            mint = 1;
            addo = 0;
            mino = 5;
        }
        if(N % 60 == 55){
            addt = 0;
            mint = 0;
            addo = 0;
            mino = 5;
        }

        printf("%d %d %d %d %d\n", addh, addt, mint, addo, mino);
    }
}