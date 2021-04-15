#include <stdio.h>
#include <vector>
#include <iostream>
#include <string.h>

using namespace std;

int S[20][20] = {0, };
int N = 0;
bool team[20] = {false, };
auto min_diff_score = 999999999;

void loop(int level, int from)
{
    if(level == N/2){
        int score1 = 0;
        int score2 = 0;
        for(int a=0;a<N;a++){
            for(int b=a+1;b<N;b++){
                if(a==b)continue;
                if(team[a] && team[b]){
                    score1 += S[a][b];
                    score1 += S[b][a];
                }
                else if(team[a]==false && team[b] == false){
                    score2 += S[a][b];
                    score2 += S[b][a];
                }
            }
        }
        auto diff = abs(score1 - score2);
        if(diff < min_diff_score){
            min_diff_score = diff;
        }
        return;
    }
    for(int i=from;i<N;i++){
        team[i] = true;
        loop(level+1, i+1);
        team[i] = false;
    }
}

int main()
{
    scanf("%d", &N);

    for(int y=0;y<N;y++){
        for(int x=0;x<N;x++){
            scanf("%d", &S[y][x]);
        }
    }

    //0번 사람의 팀을 뽑는 다고 생각하면 편하다. 
    //이것만으로도 경우의 수를 절반으로 줄일수 있다. 
    team[0] = true;
    loop(1, 1);

    printf("%d", min_diff_score);
}
