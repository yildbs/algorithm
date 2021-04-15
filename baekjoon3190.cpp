#include <stdio.h>
#include <set>
#include <map>
#include <deque>

using namespace std;

class Point{
public:
    int x, y;
};

class Snake{
public:
    int direction;
    Point head;
    deque<Point> body;
    int lt1[4][3]; //다음 방향
    int lt2[4][2]; //다음 x, y 변화량 
    int N;
    set<pair<int, int>> apples;

    Snake(int N, set<pair<int, int>> apples){
        this->head.x = 1;
        this->head.y = 1;
        this->N = N;
        this->apples = apples;
        this->direction = 0;

        this->lt1[0][0] = 0; //오른쪽을 향할때 방향변화가 없는 경우 오른쪽으로 진행
        this->lt1[0][1] = 1; //오른쪽을 향할때 왼쪽으로 향하는 경우 위로 진행
        this->lt1[0][2] = 3; //오른쪽을 향할때 오른쪽으로 향하는 경우 아래로 진행
        this->lt1[1][0] = 1; //위쪽을 향할때 방향변화가 없는 경우 위쪽으로 진행
        this->lt1[1][1] = 2; //위쪽을 향할때 왼쪽으로 향하는 경우 왼쪽으로 진행 
        this->lt1[1][2] = 0; //위쪽을 향할때 오른쪽으로 향하는 경우 오른쪽으로 진행 
        this->lt1[2][0] = 2; 
        this->lt1[2][1] = 3; 
        this->lt1[2][2] = 1; 
        this->lt1[3][0] = 3; 
        this->lt1[3][1] = 0; 
        this->lt1[3][2] = 2; 

        this->lt2[0][0] = 1; //오른쪽으로 향할때 x변화량 1
        this->lt2[0][1] = 0; //오른쪽으로 향할때 y변화량 0
        this->lt2[1][0] = 0; //위쪽으로 향할때 x변화량 0
        this->lt2[1][1] = -1; //위쪽으로 향할때 y변화량 1
        this->lt2[2][0] = -1;
        this->lt2[2][1] = 0; 
        this->lt2[3][0] = 0; 
        this->lt2[3][1] = 1;
    }

    bool move(int d=0){
        bool can_move = true;

        //get next direction
        this->direction = this->lt1[this->direction][d];

        //extend body
        this->body.push_back(this->head);

        //move head
        this->head.x += this->lt2[this->direction][0];
        this->head.y += this->lt2[this->direction][1];

        do{
            if(this->head.x == 0 || this->head.x == this->N+1){
                can_move = false;
                break;
            }
            if(this->head.y == 0 || this->head.y == this->N+1){
                can_move = false;
                break;
            }

            //collision check with body
            for(auto it=this->body.begin();it!=this->body.end();it++){
                if(this->head.x == it->x && this->head.y == it->y){
                    can_move = false;
                    break;
                }
            }

            if(this->apples.find(pair<int, int>(this->head.x, this->head.y)) == this->apples.end()){
                this->body.pop_front();
            }
            else{
                this->apples.erase(pair<int, int>(this->head.x, this->head.y));
            }
        }while(false);

        return can_move;
    }
};

int main()
{
    int N;
    scanf("%d", &N);
    
    int K;
    scanf("%d", &K);

    set<pair<int, int>> apples;
    for(int i=0;i<K;i++){
        int x, y;
        scanf("%d %d", &y, &x);
        apples.insert(pair<int, int>(x, y));
    }

    int L;
    scanf("%d", &L);
    map<int, int> directions;
    for(int i=0;i<L;i++){
        int second;
        char d;
        scanf("%d ", &second);
        scanf("%c ", &d);
        directions[second] = d;
    }

    Snake snake(N, apples);

    for(int t=0;;t++){
        int d = 0;
        if(directions.find(t) != directions.end()){
            d = directions[t] == 'L' ? 1 : 2;
        }
        if( snake.move(d) == false ){
            printf("%d", t+1);
            return 0;
        }
    }

}