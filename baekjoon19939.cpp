#include <stdio.h>
#include <vector>
#include <iostream>

using namespace std;

int main()
{
    int N, K;

    scanf("%d %d", &N, &K);

    int num_min = (K+1)*K / 2;
    if(N < num_min){
        printf("-1");
    }
    else if ((N-num_min)%K == 0){
        printf("%d", K-1);
    }
    else{
        printf("%d", K);
    }
}