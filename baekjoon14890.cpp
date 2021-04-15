#include <stdio.h>

int N, L;
int field[100][100];
int stairs[100];
int stairs_reverse[100];
bool installed[100];

bool possible()
{
    for(int a=0;a<N;a++){
        stairs_reverse[a] = stairs[N-1-a];
        installed[a] = false;
    }

    for(int a=0;a<N;a++){
        int stair_a = stairs[a];
        int count_flat = 0;
        for(int b=a+1;b<N;b++){
            int stair_b = stairs[b];
            if(stair_a - 1 == stair_b){
                count_flat ++;
                if(installed[b]){ 
                    return false; 
                }
                else{ 
                    installed[b] = true; 
                }
                if(count_flat >= L){
                    a = b;
                    break;
                }
                else if(b==N-1){
                    return false;
                }
            }
            else if(stair_a == stair_b){
                break;
            }
            else if(stair_a - 2 >= stair_b){
                return false;
            }
        }
    }

    for(int a=0;a<N;a++){
        int stair_a = stairs_reverse[a];
        int count_flat = 0;
        for(int b=a+1;b<N;b++){
            int stair_b = stairs_reverse[b];
            if(stair_a - 1 == stair_b){
                count_flat ++;
                if(installed[b]){ 
                    return false; 
                }
                else{ 
                    installed[b] = true; 
                }
                if(count_flat >= L){
                    a = b;
                    break;
                }
                else if(b==N-1){
                    return false;
                }
            }
            else if(stair_a == stair_b){
                break;
            }
            else if(stair_a - 2 >= stair_b){
                return false;
            }
        }
    }
    return true;
}

int main()
{
    int answer = 0;
    scanf("%d %d", &N, &L);
    for(int y=0;y<N;y++){
        for(int x=0;x<N;x++){
            scanf("%d", &field[y][x]);
        }
    }

    for(int y=0;y<N;y++){
        for(int x=0;x<N;x++){
            stairs[x] = field[y][x];
        }
        if(possible()){
            answer++;
        }
    }

    for(int x=0;x<N;x++){
        for(int y=0;y<N;y++){
            stairs[y] = field[y][x];
        }
        if(possible()){
            answer++;
        }
    }

    printf("%d", answer);

}
