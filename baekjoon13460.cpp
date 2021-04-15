#include <stdio.h>
#include <algorithm>
#include <queue>
using namespace std;

typedef struct balls{
    int depth;
    int rx; int ry; int bx; int by;
};

int map[10][10];
int N, M;
char str[11];

bool visited[10][10][10][10];

int answer = -1;

//right, up, left, down
int dir[4][2] = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};

void move(int &x, int &y, int d)
{
    while(true){
        x += dir[d][0];
        y += dir[d][1];
        if(map[y][x] == 1){
            x -= dir[d][0];
            y -= dir[d][1];
            return;
        }
        if(map[y][x] == 2){
            return;
        }
    }
}

int main()
{
    scanf("%d %d", &N, &M);

    balls cur;cur.depth = 0;

    for(int a=0;a<10;a++){
        for(int b=0;b<10;b++){
            for(int c=0;c<10;c++){
                for(int d=0;d<10;d++){
                    visited[a][b][c][d] = false;
                }
            }
        }
    }

    for(int i=0;i<N;i++){
        scanf("%s", str);
        for(int j=0;j<M;j++){
            switch(str[j]){
                case '#': map[i][j] = 1; break;
                case '.': map[i][j] = 0; break;
                case 'R': cur.rx = j; cur.ry = i; break;
                case 'B': cur.bx = j; cur.by = i; break;
                case 'O': map[i][j] = 2; break;
            }
        }
    }

    queue<balls> q;
    q.push(cur);
    visited[cur.rx][cur.ry][cur.bx][cur.by] = true;

    while(q.empty() == false){
        auto cur = q.front();q.pop();

        if(cur.depth > 10){
            break;
        }

        if(map[cur.ry][cur.rx] == 2){
            answer = cur.depth;
            break;
        }

        for(int i=0;i<4;i++){
            auto rx = cur.rx; auto ry = cur.ry;
            auto bx = cur.bx; auto by = cur.by;

            move(rx, ry, i); move(bx, by, i);

            //겹침 문제를 해결하기 이전에 blue가 홀에 있으면 나가리
            if(map[by][bx] == 2){
                continue;
            }

            //겹침 문제 해결
            if(rx == bx && ry == by){
                switch(i){
                    case 0: cur.rx < cur.bx ? rx-- : bx--; break;
                    case 1: cur.ry > cur.by ? ry++ : by++; break;
                    case 2: cur.rx > cur.bx ? rx++ : bx++; break;
                    case 3: cur.ry < cur.by ? ry-- : by--; break;
                }
            }

            if(visited[rx][ry][bx][by]){
                continue;
            }
            visited[rx][ry][bx][by] = true;

            q.push({cur.depth+1, rx, ry, bx, by});
        }
    }

    printf("%d", answer);
    return 0;
}

