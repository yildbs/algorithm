#include <stdio.h>
#include <vector>

using namespace std;

int solve(int N, int d, pair<int, int> days[16])
{
    if(d <= N){
        //오늘 일해서 퇴사하기 전까지 일을 끝낼 수 있는 경우에
        if(days[d].first + d <= N+1){
            //오늘 일을 하는 경우
            int a = days[d].second + solve(N, d+days[d].first, days);
            //오늘 일을 하지 않고 내일 일하는 경우 
            int b = solve(N, d+1, days);
            return a>b?a:b;
        }
        //그렇지 못한 경우
        else{
            return solve(N, d+1, days);
        }
    }
    return 0;
}

int main()
{
    int N;
    scanf("%d", &N);

    pair<int, int> days[16];
    for(int i=1;i<=N;i++){
        int day, cost;
        scanf("%d %d", &day, &cost);
        days[i] = pair<int, int>(day, cost);
    }

    printf("%d", solve(N, 1, days));
}