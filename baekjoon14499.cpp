#include <stdio.h>
#include <cstring>


char field[20][20];

class Dice{
public:
    // 주사위
    //   2
    // 4 1 3
    //   5
    //   6
    //윗면이 1
    //바닥면이 6
    int p[7]; 
    int x, y;
    int N, M;
    int lt1[5][7];
    int lt2[5][2];

    Dice(int x, int y, int N, int M){
        this->x = x;
        this->y = y;
        this->N = N;
        this->M = M;

        //주사위 초기값 세팅
        for(int i=0;i<7;i++){
            p[i] = 0;
        }

        lt1[1][1] = 3; //동쪽으로 굴리는 경우, 1에 있던 숫자는 3의 위치로 이동함
        lt1[1][2] = 2;
        lt1[1][3] = 6;
        lt1[1][4] = 1;
        lt1[1][5] = 5;
        lt1[1][6] = 4;

        lt1[2][1] = 4; //서쪽으로 굴리는 경우, 1에 있던 숫자는 4의 위치로 이동함
        lt1[2][2] = 2;
        lt1[2][3] = 1;
        lt1[2][4] = 6;
        lt1[2][5] = 5;
        lt1[2][6] = 3;

        lt1[3][1] = 2;  //북쪽으로 굴리는 경우, 1에 있던 숫자는 2의 위치로 이동함
        lt1[3][2] = 6;
        lt1[3][3] = 3;
        lt1[3][4] = 4;
        lt1[3][5] = 1;
        lt1[3][6] = 5;

        lt1[4][1] = 5; //남쪽으로 굴리는 경우, 1에 있던 숫자는 5의 위치로 이동함
        lt1[4][2] = 1;
        lt1[4][3] = 3;
        lt1[4][4] = 4;
        lt1[4][5] = 6;
        lt1[4][6] = 2;

        lt2[1][0] = 1; //동쪽으로 이동 시 x+1, y
        lt2[1][1] = 0;

        lt2[2][0] = -1; //서쪽으로 이동 시 x-1, y
        lt2[2][1] = 0;

        lt2[3][0] = 0; //북쪽으로 이동 시 x, y-1
        lt2[3][1] = -1;

        lt2[4][0] = 0; //남쪽으로 이동 시 x, y+1
        lt2[4][1] = 1;
    }

    int get_bottom(){
        return this->p[6];
    }

    int get_top(){
        return this->p[1];
    }

    //주어진 방향에 따라 주사위 굴리기
    bool move(int const d){
        //다음 x, y 좌표 계산
        int next_x = this->x + lt2[d][0];
        int next_y = this->y + lt2[d][1];

        //x, y가 칸을 벗어나지 않는 다면
        if(0<=next_x && next_x<=M-1){
            if(0<=next_y && next_y<=N-1){
                this->x = next_x;
                this->y = next_y;
                
                //주사위 이동 
                int prev[7];
                memcpy(prev, this->p, 7*sizeof(int));
                for(int i=1;i<=6;i++){
                    this->p[this->lt1[d][i]] = prev[i];
                }

                //칸에 쓰여있는 수가 0인 경우 주사위 바닥면이 칸으로 복사됨
                if(field[this->y][this->x] == 0){
                    field[this->y][this->x] = this->p[6];
                }
                //칸에 쓰여있는 수가 0이 아닌 경우 칸의 숫자가 주사위 바닥면으로 복사됨
                else{
                    this->p[6] = field[this->y][this->x];
                    field[this->y][this->x] = 0;
                }
                return true;
            }
        }
        
        //이동 좌표가 칸을 벗어난다면 false 리턴(이동 불가)
        return false;
    }
};


int main()
{
    int N, M, x, y, K;
    scanf("%d %d %d %d %d", &N, &M, &y, &x, &K);

    for(int y=0;y<N;y++){
        for(int x=0;x<M;x++){
            int v = 0;
            scanf("%d", &v);
            field[y][x] = v;
        }
    }

    Dice dice(x, y, N, M);

    for(int i=0;i<K;i++){
        int v = 0;
        scanf("%d", &v);

        if(dice.move(v)){
            //주사위가 이동할수있다면 출력함
            printf("%d\n", dice.get_top());
        }
    }
}
