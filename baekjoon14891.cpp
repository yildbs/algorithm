#include <stdio.h>
#include <cstring>

class Wheel{
public:
    bool turned;
    int cogs[8];
    
    Wheel* left;
    Wheel* right;
public:
    Wheel(){
        this->turned = false;
        this->left = nullptr;
        this->right = nullptr;
    }

    //시계방향으로 회전시키기
    void turn_clockwise(){
        this->turned = true;

        //왼쪽에 톱니바퀴가 있으면
        if(this->left != nullptr){
            //회전이 안된 상태라면(1번만 회전 시키기 위함)
            if(this->left->turned==false){
                //극이 반대라면
                if(this->left->cogs[2] != this->cogs[6]){
                    this->left->turn_counter_clockwise();
                }
            }
        }
        //오른쪽에 톱니바퀴가 있으면
        if(this->right != nullptr){
            //회전이 안된 상태라면(1번만 회전 시키기 위함)
            if(this->right->turned==false){
                //극이 반대라면
                if(this->right->cogs[6] != this->cogs[2]){
                    this->right->turn_counter_clockwise();
                }
            }
        }

        int cogs_bak[8];
        memcpy(cogs_bak, cogs, sizeof(int)*8);
        this->cogs[0] = cogs_bak[7];
        this->cogs[1] = cogs_bak[0];
        this->cogs[2] = cogs_bak[1];
        this->cogs[3] = cogs_bak[2];
        this->cogs[4] = cogs_bak[3];
        this->cogs[5] = cogs_bak[4];
        this->cogs[6] = cogs_bak[5];
        this->cogs[7] = cogs_bak[6];
    }
    void turn_counter_clockwise(){
        this->turned = true;
        if(this->left != nullptr){
            if(this->left->turned==false){
                if(this->left->cogs[2] != this->cogs[6]){
                    this->left->turn_clockwise();
                }
            }
        }
        if(this->right != nullptr){
            if(this->right->turned==false){
                if(this->right->cogs[6] != this->cogs[2]){
                    this->right->turn_clockwise();
                }
            }
        }

        int cogs_bak[8];
        memcpy(cogs_bak, cogs, sizeof(int)*8);
        this->cogs[0] = cogs_bak[1];
        this->cogs[1] = cogs_bak[2];
        this->cogs[2] = cogs_bak[3];
        this->cogs[3] = cogs_bak[4];
        this->cogs[4] = cogs_bak[5];
        this->cogs[5] = cogs_bak[6];
        this->cogs[6] = cogs_bak[7];
        this->cogs[7] = cogs_bak[0];
    }
};

int main()
{
    char input[9];
    Wheel wheels[4];
    for(int i=0;i<4;i++){
        scanf("%s", input);
        for(int j=0;j<8;j++){
            wheels[i].cogs[j] = input[j] == '1' ? 1 : 0;
        }
    }

    //바퀴 서로서로 연결하기
    wheels[0].right = &wheels[1];
    wheels[1].left = &wheels[0];
    wheels[1].right = &wheels[2];
    wheels[2].left = &wheels[1];
    wheels[2].right = &wheels[3];
    wheels[3].left = &wheels[2];

    int K = 0;
    scanf("%d", &K);
    for(int k=0;k<K;k++){
        for(int i=0;i<4;i++){ wheels[i].turned = false; }
        int a=0, b=0;
        scanf("%d %d", &a, &b);

        //1이면 시계방향으로 회전
        if(b==1){
            wheels[a-1].turn_clockwise();
        }
        //0이면 반시계방향으로 회전
        else{
            wheels[a-1].turn_counter_clockwise();
        }
    }

    int score = 0;
    score += wheels[0].cogs[0] * 1;
    score += wheels[1].cogs[0] * 2;
    score += wheels[2].cogs[0] * 4;
    score += wheels[3].cogs[0] * 8;

    printf("%d", score);
}
