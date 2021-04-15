#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

int solve(int N, vector<int> &dat)
{
    if(dat[N] == -1){
        vector<int> l;
        l.push_back(solve(N-1, dat) + 1);
        if(N % 2 == 0){
            l.push_back(solve(N/2, dat) + 1);
        }
        if (N % 3 == 0){
            l.push_back(solve(N/3, dat) + 1);
        }
        dat[N] = *min_element(l.begin(), l.end());
    }
    return dat[N];
}

int main()
{
    int N;
    scanf("%d", &N);

    vector<int> dat(N+1, -1);
    dat[1] = 0;
    dat[2] = 1;
    dat[3] = 1;
    dat[4] = 2;
    dat[5] = 3;
    dat[6] = 2;

    for(int i=1;i<=N;i++){
        solve(i, dat);
        printf("%d. %d\n", i, dat[i]);
    }

    printf("%d", dat[N]);
    return 0;
}