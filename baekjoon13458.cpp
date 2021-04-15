#include <stdio.h>
#include <math.h>

int main()
{
    int N;
    scanf("%d", &N);

    int A[1000000];
    for(int i=0;i<N;i++){
        scanf("%d", &A[i]);
    }

    int B, C;
    scanf("%d %d", &B, &C);

    long long answer = 0;
    for(int i=0;i<N;i++){
        answer ++;
        if(A[i] > B){
            answer += (A[i] - B) % C == 0 ? (A[i] - B) / C : (A[i] - B) / C + 1;
        }
    }

    printf("%lld", answer);
}
