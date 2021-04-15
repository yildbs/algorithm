#include <stdio.h>

int field[50][50] = {0, };
int M, N;

class Cleaner{
public:
    int x;
    int y;
    int d; // 0: 북, 1: 동, 2: 남, 3: 서

    int score;

    //좌회전 시 다음 방향 정하는 변수
    char next_d[4];
    //좌회전 하는 경우 다음 x, y를 정하기 위한 변수
    char left_x_y[4][2];
    //직진 하는 경우 다음 x, y를 정하기 위한 변수
    char straight_x_y[4][2];
    //후진 하는 경우 다음 x, y를 정하기 위한 변수
    char back_x_y[4][2];

    Cleaner(int y, int x, int d){
        this->x = x;
        this->y = y;
        this->d = d;

        this->score = 0;
        
        this->next_d[0] = 3;
        this->next_d[1] = 0;
        this->next_d[2] = 1;
        this->next_d[3] = 2;
        
        this->left_x_y[0][0] = -1;
        this->left_x_y[0][1] = 0;

        this->left_x_y[1][0] = 0;
        this->left_x_y[1][1] = -1;

        this->left_x_y[2][0] = 1;
        this->left_x_y[2][1] = 0;

        this->left_x_y[3][0] = 0;
        this->left_x_y[3][1] = 1;

        this->straight_x_y[0][0] = 0;
        this->straight_x_y[0][1] = -1;

        this->straight_x_y[1][0] = +1;
        this->straight_x_y[1][1] = 0;

        this->straight_x_y[2][0] = 0;
        this->straight_x_y[2][1] = +1;

        this->straight_x_y[3][0] = -1;
        this->straight_x_y[3][1] = 0;

        this->back_x_y[0][0] = 0;
        this->back_x_y[0][1] = 1;

        this->back_x_y[1][0] = -1;
        this->back_x_y[1][1] = 0;

        this->back_x_y[2][0] = 0;
        this->back_x_y[2][1] = -1;

        this->back_x_y[3][0] = +1;
        this->back_x_y[3][1] = 0;
    }
    void turn_left(){
        this->d = this->next_d[this->d];
    }
    bool left_is_cleanable(){
        int next_x = this->x+this->left_x_y[this->d][0];
        int next_y = this->y+this->left_x_y[this->d][1];
        if(0<=next_x && next_x <M && 0<=next_y && next_y <N){
            if(field[next_y][next_x] == 0){
                return true;
            }
        }
        return false;
    }
    bool movable_to_back(){
        int next_x = this->x+this->back_x_y[this->d][0];
        int next_y = this->y+this->back_x_y[this->d][1];
        if(0<=next_x && next_x <M && 0<=next_y && next_y <N){
            if(field[next_y][next_x] == 0 || field[next_y][next_x] == 2){
                return true;
            }
        }
        return false;
    }
    void go_straight(){
        this->x += this->straight_x_y[this->d][0];
        this->y += this->straight_x_y[this->d][1];
    }
    void go_back(){
        this->x += this->back_x_y[this->d][0];
        this->y += this->back_x_y[this->d][1];
    }
    void clean(){
        field[this->y][this->x] = 2;
        this->score++;
    }
    auto get_score(){
        return this->score;
    }
};

int main()
{
    scanf("%d %d", &N, &M);

    int r, c, d;
    scanf("%d %d %d", &r, &c, &d);

    for(int y=0;y<N;y++){
        for(int x=0;x<M;x++){
            int v =0;
            scanf("%d ", &v);
            field[y][x] = v;
        }
    }

    Cleaner cleaner(r, c, d);

    while(true){
        cleaner.clean();

#if 0
        printf("\n");
        for(int y=0;y<N;y++){
            for(int x=0;x<M;x++){
                if(y==cleaner.y && x ==cleaner.x){
                    char dd[4];
                    dd[0] = 'A';
                    dd[1] = '>';
                    dd[2] = 'V';
                    dd[3] = '<';
                    printf("%3c ", dd[cleaner.d]);
                }
                else{
                    printf("%3d ", field[y][x]);
                }
            }
            printf("\n");
        }
#endif

        int count_turn = 0;
        while(true){
            //1번 조건 : 왼쪽 방향으로 청소 할 수 있는 경우
            if(cleaner.left_is_cleanable()){
                //왼쪽 턴
                cleaner.turn_left();
                //직진
                cleaner.go_straight();
                //다시 1번 조건으로
                break;
            }
            //왼쪽 방향으로 청소 불가능한 경우
            else{
                //왼쪽턴
                cleaner.turn_left();
                //턴 카운트 
                count_turn++;
            }

            //4번 회전했다면 (제자리로 돌아왔다면)
            if(count_turn==4){
                //뒤가 벽이 아닌 경우
                if(cleaner.movable_to_back()){
                    //뒤로 간다
                    cleaner.go_back();
                    count_turn = 0;
                }
                //뒤가 벽인 경우
                else{
                    //출력하고 종료 
                    printf("%d", cleaner.get_score());
                    return 0;
                }
            }

        }
    }
}

