#include <stdio.h>

#if 1
int main()
{
    int N;
    scanf("%d", &N);

    int n3 = 0, n5 = 0;

    n5 = N / 5;
    N = N % 5;

    while(N != 0){
        if(N % 3 == 0){
            n3 = N / 3;
            break;
        }
        else{
            N += 5;
            n5 -= 1;
            if(n5 < 0){
                printf("-1");
                return 0;
            }
        }
    }

    printf("%d", n3 + n5);
}
#else

int solve (int N)
{
    int n3 = 0, n5 = 0;

    n5 = N / 5;
    N = N % 5;

    while(N != 0){
        if(N % 3 == 0){
            n3 = N / 3;
            break;
        }
        else{
            N += 5;
            n5 -= 1;
            if(n5 < 0){
                return -1;
            }
        }
    }
    return n3 + n5;
}

int main()
{
    for(int i=1;i<5000;i++){
        printf("%d. %d\n", i, solve(i));
    }

}

#endif
