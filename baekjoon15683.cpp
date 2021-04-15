#include <stdio.h>
#include <cstring>
#include <vector>

using namespace std;

int M, N;

inline int get_index(int x, int y){
    return y * M + x;
}

class Camera{
public:
    int type = 0;
    int x = 0;
    int y = 0;
    char field[4][64];
    int num_field = 0;
    int direction[4][2];

    Camera(){
        direction[0][0] = 0;
        direction[0][1] = -1;

        direction[1][0] = 1;
        direction[1][1] = 0;

        direction[2][0] = 0;
        direction[2][1] = 1;

        direction[3][0] = -1;
        direction[3][1] = 0;
    }

    void set_visible(int d, int d2){
        int cx = this->x;
        int cy = this->y;
        while(true){
            if(cx < 0 || cy < 0 || cx >= M || cy >= N){
                break;
            }
            if(this->field[d][get_index(cx, cy)] == '0'){
                this->field[d][get_index(cx, cy)] = '#';
            }
            else if(this->field[d][get_index(cx, cy)] == '6'){
                break;
            }
            cx += direction[d2][0];
            cy += direction[d2][1];
        }
    }

    //각 카메라가 방향별로 감시할 수 있는 지도의 상태를 만드는 함수
    void set_camera(int x, int y, char *field){
        this->x = x;
        this->y = y;
        this->type = field[get_index(x,y)] - '0';
        for(int d=0;d<4;d++){
            memcpy(this->field[d], field, M*N);

            switch(type){
                case 1:
                //카메라 1은 1방향 감시 가능
                set_visible(d, (d+0)%4);
                break;
                case 2:
                //카메라 2은 2방향 감시 가능
                set_visible(d, (d+0)%4);
                set_visible(d, (d+2)%4);
                break;
                case 3:
                //카메라 3은 2방향 감시 가능
                set_visible(d, (d+0)%4);
                set_visible(d, (d+1)%4);
                break;
                case 4:
                //카메라 4은 2방향 감시 가능
                set_visible(d, (d+0)%4);
                set_visible(d, (d+1)%4);
                set_visible(d, (d+3)%4);
                break;
                case 5:
                //카메라 5은 2방향 감시 가능
                set_visible(d, (d+0)%4);
                set_visible(d, (d+1)%4);
                set_visible(d, (d+2)%4);
                set_visible(d, (d+3)%4);
                break;
            }

            this->num_field = d + 1;

            if(type == 2 && d == 1) break;
            if(type == 5 && d == 0) break;
        }
    }
};

char field[64];
vector<Camera> cameras;
int selected[8] = {0, };

int min_count_blind = 99999;

void loop(int level)
{
    //모든 카메라의 방향이 결정 된 경우
    if(level == cameras.size()){
        for(int i=0;i<M*N;i++) {
            field[i] = '0';
        }

        //결정된 방향에 따라서 카메라의 감시 영역을 합치는 부분
        for(int n=0;n<level;n++){
            auto cam = cameras.at(n);
            for(int y=0;y<N;y++){
                for(int x=0;x<M;x++){
                    if( cam.field[selected[n]][get_index(x, y)] != '0'){
                        field[get_index(x, y)] = cam.field[selected[n]][get_index(x, y)];
                    }
                }
            }
        }

        //사각 영역('0')의 개수를 세는 부분
        int count_blind = 0;
        for(int i=0;i<M*N;i++) {
            if(field[i] == '0'){
                count_blind++;
            }
        }
        if(count_blind < min_count_blind){
            min_count_blind = count_blind;
        }
        return;
    }

    auto cam = cameras.at(level);
    for(int i=0;i<cam.num_field;i++){
        selected[level] = i;
        loop(level+1);
    }
}

int main()
{
    scanf("%d %d ", &N, &M);

    for(int y=0;y<N;y++){
        for(int x=0;x<M;x++){
            char c = 0;
            scanf("%c ", &c);
            field[get_index(x, y)] = c;
        }
    }

    int num_walls = 0;
    for(int y=0;y<N;y++){
        for(int x=0;x<M;x++){
            if( '1' <= field[get_index(x, y)] && field[get_index(x, y)] <= '5'){
                cameras.push_back(Camera());
                cameras.at(cameras.size() - 1).set_camera(x, y, field);
            }
            if( '6' == field[get_index(x, y)]){
                num_walls++;
            }
        }
    }

    if(cameras.size() > 0){
        loop(0);
    }
    //카메라가 없는 경우 벽의 개수를 빼서 출력한다
    else{
        min_count_blind = M*N-num_walls;
    }
    printf("%d", min_count_blind);
}
