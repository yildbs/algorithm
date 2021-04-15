#include <stdio.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <map>

using namespace std;

int main()
{
    int K, H;
    scanf("%d ", &K);

    int left = 0;
    int right = pow(2, K);
    int top = 0;
    int bot = pow(2, K);

    //H, 가로 길이 차이 홀짝, 세로 길이 차이 홀짝
    //예를 들어, 종이를 접고 접어서 (x, y)라는 칸이 움직이지 않은 칸이고, H라는 위치에 구멍을 뚫었고,
    // 어떤 (a, b)라는 칸의 홀의 위치를 계산하는 경우
    // [H][(a-x)%2][(b-y)%2] 가 (a, b)의 구멍의 위치
    int lt[4][2][2];
    lt[0][0][0] = 0;
    lt[0][0][1] = 2;
    lt[0][1][0] = 1;
    lt[0][1][1] = 3;

    lt[1][0][0] = 1;
    lt[1][0][1] = 3;
    lt[1][1][0] = 0;
    lt[1][1][1] = 2;

    lt[2][0][0] = 2;
    lt[2][0][1] = 0;
    lt[2][1][0] = 3;
    lt[2][1][1] = 1;

    lt[3][0][0] = 3;
    lt[3][0][1] = 1;
    lt[3][1][0] = 2;
    lt[3][1][1] = 0;

    for(int k=0;k<2*K;k++){
        char c;
        scanf("%c ", &c);

        //입력된 값에 따라서 반씩 접어주며 최종적으로 움직이지 않는 칸을 찾는다
        switch(c){
            case 'D': top = (top+bot)/2; break;
            case 'U': bot = (top+bot)/2; break;
            case 'R': left = (left+right)/2; break;
            case 'L': right = (left+right)/2; break;
        }
    }

    scanf("%d", &H);

    for(int y=0;y<pow(2, K);y++){
        for(int x=0;x<pow(2, K);x++){
            printf("%d%s", lt[H][abs(left-x)%2][abs(top-y)%2], x==pow(2,K)-1?"":" ");
        }
        if(y == pow(2, K) - 1) break;
        printf("\n");
    }
}