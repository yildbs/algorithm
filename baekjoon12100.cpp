#include <stdio.h>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;


int N = 0;
class Blocks{
public:
    int depth;
    int blocks[20][20] = {0, };

    //현재 클래스의 blocks을 세팅하기 위한 함수
    void copy_from(int blocks[20][20]){
        memcpy(this->blocks, blocks, 20*20*sizeof(int));
    }

    //숫자 열을 입력 받고, 인덱스가 0이 되는 방향으로 압축하는 해서 리스트를 다시 리턴하는 함수
    vector<int> squeeze(vector<int> buf){
        vector<int> buf2;
        for(int i=0;i<buf.size();i++){
            //중간에 2 0 2 등 중간에 들어있는 0 제거 위함
            if(buf.at(i) != 0){
                buf2.push_back(buf.at(i));
            }
        }
        vector<int> squeezed;
        for(int i=0;i<buf2.size();i++){
            //현재 숫자와 다음 숫자가 같으면 압축
            //그리고 인덱스를 넘겨버리기 때문에 (i++) 중복으로 압축되는 일은 없음
            if(buf2[i] == buf2[i+1] && i != buf2.size()-1 && buf2[i] != 0){
                squeezed.push_back(buf2[i] * 2);
                i++;
            }
            //압축되지 못하는 경우라면 그냥 삽입
            else if(buf2[i] != 0){
                squeezed.push_back(buf2[i]);
            }
        }
        return squeezed;
    }

    //디버깅용 함수
    void print(char c){
        for(int i=0;i<10;i++) printf("%c", c); printf("\n");
        for(int y=0;y<N;y++){
            for(int x=0;x<N;x++){
                printf("%3d ", this->blocks[y][x]);
            }
            printf("\n");
        }
    }

    //가장 큰 block값을 찾기 위함
    int get_max_block() {
        int max_block = 0;
        for(int y=0;y<N;y++){
            for(int x=0;x<N;x++){
                if(max_block < this->blocks[y][x]){
                    max_block = this->blocks[y][x];
                }
            }
        }
        return max_block;
    }

    //direction을 입력 받고, 해당 방향으로 움직여서 움직였다면 True를 리턴함
    bool move(int d){
        int blocks_prev[20][20] = {0, };
        memcpy(blocks_prev, this->blocks, 20*20*sizeof(int));
        switch(d){
            case 0: this->move_to_right(); break;
            case 1: this->move_to_up(); break;
            case 2: this->move_to_left(); break;
            case 3: this->move_to_down(); break;
        }

        //움직였는지 비교하는 함수
        bool changed = false;
        for(int y=0;y<N;y++){
            for(int x=0;x<N;x++){
                if(this->blocks[y][x] != blocks_prev[y][x]){
                    changed = true;
                    break;
                }
            }
        }
        return changed;
    }

    //오른쪽으로 미는 함수 
    void move_to_right(){
        for(int y=0;y<N;y++){
            vector<int> buf;
            for(int x=N-1;x>=0;x--){
                buf.push_back(this->blocks[y][x]);
            }
            auto squeezed = this->squeeze(buf);
            for(int n=0;n<N;n++){
                if(n<squeezed.size()){
                    this->blocks[y][N-1-n] = squeezed.at(n);
                }
                else{
                    this->blocks[y][N-1-n] = 0;
                }
            }
        }
    }
    //위로 미는 함수 
    void move_to_up(){
        for(int x=0;x<N;x++){
            vector<int> buf;
            for(int y=0;y<N;y++){
                buf.push_back(this->blocks[y][x]);
            }
            auto squeezed = this->squeeze(buf);
            for(int n=0;n<N;n++){
                if(n<squeezed.size()){
                    this->blocks[n][x] = squeezed.at(n);
                }
                else{
                    this->blocks[n][x] = 0;
                }
            }
        }
    }
    //왼쪽으로 미는 함수 
    void move_to_left(){
        for(int y=0;y<N;y++){
            vector<int> buf;
            for(int x=0;x<N;x++){
                buf.push_back(this->blocks[y][x]);
            }
            auto squeezed = this->squeeze(buf);
            for(int n=0;n<N;n++){
                if(n<squeezed.size()){
                    this->blocks[y][n] = squeezed.at(n);
                }
                else{
                    this->blocks[y][n] = 0;
                }
            }
        }
    }
    //아래로 미는 함수 
    void move_to_down(){
        for(int x=0;x<N;x++){
            vector<int> buf;
            for(int y=N-1;y>=0;y--){
                buf.push_back(this->blocks[y][x]);
            }
            auto squeezed = this->squeeze(buf);
            for(int n=0;n<N;n++){
                if(n<squeezed.size()){
                    this->blocks[N-1-n][x] = squeezed.at(n);
                }
                else{
                    this->blocks[N-1-n][x] = 0;
                }
            }
        }
    }
};

int main()
{
    scanf("%d", &N);

    int blocks[20][20] = {0, };
    for(int y=0;y<N;y++){
        for(int x=0;x<N;x++){
            scanf("%d", &blocks[y][x]);
        }
    }

    queue<Blocks> q;
    Blocks tmp;
    tmp.depth = 0;
    tmp.copy_from(blocks);
    q.push(tmp);

    int max_block = 0;

    while(q.empty() == false){
        auto cur = q.front(); q.pop();
        auto cur_max = cur.get_max_block();

        // cur.print('@');
        if(max_block < cur_max){
            max_block = cur_max;
        }
        //depth가 5라면 더 이상 진행하지 않음
        if(cur.depth == 5){
            continue;
        }
        for(int d=0;d<4;d++){
            Blocks next;
            next.copy_from(cur.blocks);
            if(next.move(d)){
                // next.print('-');
                Blocks tmp;
                tmp.depth = cur.depth+1;
                tmp.copy_from(next.blocks);
                q.push(tmp);
            }
        }
    }
    printf("%d", max_block);
}