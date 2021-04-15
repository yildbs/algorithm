#include <stdio.h>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int N, K;

    scanf("%d %d", &N, &K);

    vector<int> numbers;

    for(int i=0;i<N;i++){
        int number = 0;
        scanf("%d", &number);
        numbers.push_back(number);
    }

    sort(numbers.begin(), numbers.end(), [](int a, int b){return a>b;});

    int sum=0;
    for(int i=0;i<K;i++){
        sum += numbers[i];
    }

    printf("%d", sum - (K*(K-1))/2);
}
