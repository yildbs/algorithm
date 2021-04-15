#include <stdio.h>
#include <vector>

int N, M;
int field[500][500];

using namespace std;

class Tetromino{
public:
    int w;
    int h;
    int mat[4][4];

public:
    //도형을 입력 받아서 도형에 맞게 초기화 한다
    Tetromino(int mat[4][4]){
        this->w=0;
        this->h=0;
        for(int y=0;y<4;y++){
            for(int x=0;x<4;x++){
                this->mat[y][x] = mat[y][x];
                if(mat[y][x] == 1){
                    if(this->w < x+1){
                        this->w = x + 1;
                    }
                    if(this->h < y+1){
                        this->h = y + 1;
                    }
                }
            }
        }
    }

    //테트로미노와 field를 비교하면서, 현재 도형이 낼 수 있는 가장 큰 점수를 구한다
    int get_max_score(){
        int max_score = 0;
        for(int y=0;y<N+1-this->h;y++){
            for(int x=0;x<M+1-this->w;x++){
                int score = 0;
                for(int yy=0;yy<this->h;yy++){
                    for(int xx=0;xx<this->w;xx++){
                        score += this->mat[yy][xx] * field[y+yy][x+xx];
                    }
                }
                if(score > max_score){
                    max_score = score;
                }
            }
        }
        return max_score;
    }
};

int tet1[4][4] = {
    {1, 1, 1, 1}, 
    {0, 0, 0, 0}, 
    {0, 0, 0, 0}, 
    {0, 0, 0, 0}
};
int tet2[4][4] = {
    {1, 0, 0, 0}, 
    {1, 0, 0, 0}, 
    {1, 0, 0, 0}, 
    {1, 0, 0, 0}
};
int tet3[4][4] = {
    {1, 1, 0, 0}, 
    {1, 1, 0, 0}, 
    {0, 0, 0, 0}, 
    {0, 0, 0, 0}
};
int tet4[4][4] = {
    {1, 0, 0, 0}, 
    {1, 0, 0, 0}, 
    {1, 1, 0, 0}, 
    {0, 0, 0, 0}
};
int tet5[4][4] = {
    {1, 1, 1, 0}, 
    {1, 0, 0, 0}, 
    {0, 0, 0, 0}, 
    {0, 0, 0, 0}
};
int tet6[4][4] = {
    {1, 1, 0, 0}, 
    {0, 1, 0, 0}, 
    {0, 1, 0, 0}, 
    {0, 0, 0, 0}
};
int tet7[4][4] = {
    {0, 0, 1, 0}, 
    {1, 1, 1, 0}, 
    {0, 0, 0, 0}, 
    {0, 0, 0, 0}
};
int tet8[4][4] = {
    {0, 1, 0, 0}, 
    {0, 1, 0, 0}, 
    {1, 1, 0, 0}, 
    {0, 0, 0, 0}
};
int tet9[4][4] = {
    {1, 1, 1, 0}, 
    {0, 0, 1, 0}, 
    {0, 0, 0, 0}, 
    {0, 0, 0, 0}
};
int tet10[4][4] = {
    {1, 1, 0, 0}, 
    {1, 0, 0, 0}, 
    {1, 0, 0, 0}, 
    {0, 0, 0, 0}
};
int tet11[4][4] = {
    {1, 0, 0, 0}, 
    {1, 1, 1, 0}, 
    {0, 0, 0, 0}, 
    {0, 0, 0, 0}
};


int tet12[4][4] = {
    {0, 1, 1, 0}, 
    {1, 1, 0, 0}, 
    {0, 0, 0, 0}, 
    {0, 0, 0, 0}
};
int tet13[4][4] = {
    {1, 0, 0, 0}, 
    {1, 1, 0, 0}, 
    {0, 1, 0, 0}, 
    {0, 0, 0, 0}
};
int tet14[4][4] = {
    {1, 1, 0, 0}, 
    {0, 1, 1, 0}, 
    {0, 0, 0, 0}, 
    {0, 0, 0, 0}
};
int tet15[4][4] = {
    {0, 1, 0, 0}, 
    {1, 1, 0, 0}, 
    {1, 0, 0, 0}, 
    {0, 0, 0, 0}
};

int tet16[4][4] = {
    {0, 1, 0, 0}, 
    {1, 1, 0, 0}, 
    {0, 1, 0, 0}, 
    {0, 0, 0, 0}
};
int tet17[4][4] = {
    {0, 1, 0, 0}, 
    {1, 1, 1, 0}, 
    {0, 0, 0, 0}, 
    {0, 0, 0, 0}
};
int tet18[4][4] = {
    {1, 0, 0, 0}, 
    {1, 1, 0, 0}, 
    {1, 0, 0, 0}, 
    {0, 0, 0, 0}
};
int tet19[4][4] = {
    {1, 1, 1, 0}, 
    {0, 1, 0, 0}, 
    {0, 0, 0, 0}, 
    {0, 0, 0, 0}
};

int main()
{
    scanf("%d %d", &N, &M);

    for(int y=0;y<N;y++){
        for(int x=0;x<M;x++){
            int v = 0;
            scanf("%d ", &v);
            field[y][x] = v;
        }
    }

    vector<Tetromino> ts;
    ts.push_back(Tetromino(tet1));
    ts.push_back(Tetromino(tet2));
    ts.push_back(Tetromino(tet3));
    ts.push_back(Tetromino(tet4));
    ts.push_back(Tetromino(tet5));
    ts.push_back(Tetromino(tet6));
    ts.push_back(Tetromino(tet7));
    ts.push_back(Tetromino(tet8));
    ts.push_back(Tetromino(tet9));
    ts.push_back(Tetromino(tet10));
    ts.push_back(Tetromino(tet11));
    ts.push_back(Tetromino(tet12));
    ts.push_back(Tetromino(tet13));
    ts.push_back(Tetromino(tet14));
    ts.push_back(Tetromino(tet15));
    ts.push_back(Tetromino(tet16));
    ts.push_back(Tetromino(tet17));
    ts.push_back(Tetromino(tet18));
    ts.push_back(Tetromino(tet19));

    int max_score = 0;
    for(auto t : ts){
        auto score = t.get_max_score(); 
        if(max_score < score){
            max_score = score;
        }
    }
    printf("%d", max_score);
}
