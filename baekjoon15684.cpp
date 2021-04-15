#include <stdio.h>
#include <vector>
#include <stdlib.h>

using namespace std;

int N, M, H;
bool ladder[31][11] = {false, };

vector<pair<int, int>> candidates;

//y, x 에 새로운 가로선을 추가할 수 있는지 체크하는 함수
bool new_line_is_valid(int y, int x){
    if(0 < x-1){
        if(ladder[y][x-1] == true){
            return false; // 왼쪽에 이미 가로선이 있으므로 not valid
        }
    }
    if(x+1<N){
        if(ladder[y][x+1] == true){
            return false; // 오른쪽에 이미 가로선이 있으므로 not valid
        }
    }
    return true;
}

//특정한 인덱스에서 세로로 내리고 도착지 인덱스를 구하는 함수
int go(int index)
{
    int x = index;
    int y = 1;
    //한번 가로로 움직이면 다음 번엔 반드시 세로로 이동
    bool force_down = false;

    while(true){
        if(ladder[y][x] == true && force_down == false){
            x += 1;
            force_down = true;
        }
        else if(ladder[y][x-1] == true && force_down == false){
            x -= 1;
            force_down = true;
        }
        else{
            force_down = false;
            y += 1;
            if(y == H + 1){
                return x;
            }
        }
    }
}

void loop(int level, int target, int from){
    if(level == target){
        bool valid = true;
        for(int x=1;x<=N;x++){
            if(go(x) == x){
                continue;
            }
            else{
                valid = false;
                break;
            }
        }
        if(valid){
            printf("%d", level);
            exit(0);
        }
        return;
    }

    for(int c=from;c<candidates.size();c++){
        auto next = candidates.at(c);
        auto next_y = next.first;
        auto next_x = next.second;
        if(new_line_is_valid(next_y, next_x)){
            ladder[next_y][next_x] = true;
            loop(level+1, target, c+1);
            ladder[next_y][next_x] = false;
        }
    }
}

int main()
{
    scanf("%d %d %d", &N, &M, &H);
    for(int y=0;y<31;y++){
        for(int x=0;x<11;x++){
            ladder[y][x] = false;
        }
    }

    for(int m=0;m<M;m++){
        int a, b;
        scanf("%d %d", &a, &b);
        ladder[a][b] = true;
    }

    for(int y=1;y<=H;y++){
        for(int x=1;x<=N;x++){
            if(ladder[y][x] == false){
                candidates.push_back(pair<int, int>(y, x));
            }
        }
    }

    loop(0, 0, 0);
    loop(0, 1, 0);
    loop(0, 2, 0);
    loop(0, 3, 0);
    printf("-1");
}
