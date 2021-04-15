#include <stdio.h>
#include <queue>

class State{
public:
    int depth;
    int rx, ry, bx, by;
};

int directions[4][2] = {0, };
char map[10][10] = {0, };

void move_to(int d, int &x, int &y)
{
    while(true){
        bool cant_move = false;
        int nx = x + directions[d][0];
        int ny = y + directions[d][1];
        switch (map[nx][ny])
        {
        case '#':
            cant_move = true;
            break;
        case '.':
            x = nx;
            y = ny;
            break;
        case 'O':
            x = nx;
            y = ny;
            cant_move = true;
            break;
        }
        if(cant_move){
            break;
        }
    }
}

int main()
{
    int N, M;
    scanf("%d %d", &N, &M);

    int rx, ry, bx, by;
    int ox, oy;

    //오른쪽으로, x, y
    directions[0][0] = 1;
    directions[0][1] = 0;
    //위쪽으로, x, y
    directions[1][0] = 0;
    directions[1][1] = -1;
    //왼쪽으로, x, y
    directions[2][0] = -1;
    directions[2][1] = 0;
    //아래쪽으로, x, y
    directions[3][0] = 0;
    directions[3][1] = 1;

    for(int y=0;y<N;y++){
        char str[20];
        scanf("%s", str);
        for(int x=0;x<M;x++){
            auto c = str[x];
            switch (c) {
            case 'R':
                rx = x;
                ry = y;
                c = '.';
                break;
            case 'B':
                bx = x;
                by = y;
                c = '.';
                break;
            case 'O':
                ox = x;
                oy = y;
                break;
            default:break;
            }
            map[x][y] = c;
        }
    }

    bool visited[10][10][10][10] = {false, }; // rx, ry, bx, by
    std::queue<State> q;

    visited[rx][ry][bx][by] = true;
    q.push(State{0, rx, ry, bx, by});
    while(q.empty() == false){
        auto cur = q.front(); q.pop();
        if(cur.depth > 10) continue;

        for(int d=0;d<4;d++){
            rx = cur.rx;
            ry = cur.ry;
            bx = cur.bx;
            by = cur.by;

            move_to(d, rx, ry);
            move_to(d, bx, by);
            if(bx == ox && by == oy){ 
                continue;
            }
            else if(rx == ox && ry == oy){
                if(cur.depth +1 <=10){
                    printf("%d", cur.depth+1);
                    return 0;
                }
                continue;
            }

            if(rx == bx && ry == by){
                if(cur.rx < cur.bx){
                    if(d == 0){ rx--; }
                    else if (d==2){ bx++; }
                }
                else{
                    if(d == 0){ bx--; }
                    else if (d==2){ rx++; }
                }
                if(cur.ry < cur.by){
                    if(d == 3){ ry--; }
                    else if (d==1){ by++; }
                }
                else{
                    if(d == 3){ by--; }
                    else if (d==1){ ry++; }
                }
            }

            if(rx != cur.rx || ry != cur.ry || bx != cur.bx || by != cur.by) {
                if(visited[rx][ry][bx][by] == false){
                    visited[rx][ry][bx][by] = true;
                    q.push(State{cur.depth+1, rx, ry, bx, by});
                }
            }
        }
    }
    printf("-1");
}
