#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main()
{
    int N;
    scanf("%d", &N);

    vector<vector<int>> matrix;
    matrix.resize(N);
    for(auto &row : matrix){
        row.resize(N);
    }

    for(int y=0;y<N;y++){
        for(int x=0;x<N;x++){
            int v;
            scanf("%d", &v);
            matrix[y][x] = v;
        }
    }

    vector<vector<int>> label;
    label.resize(N);
    for(auto &row : label){
        row.resize(N);
        for(auto &v : row){
            v = -1;
        }
    }

    vector<int> areas;
    queue<pair<int, int>> q;
    int label_index = 0;
    while(true){

        for(int y=0;y<N;y++){
            for(int x=0;x<N;x++){
                if(matrix[y][x] == 1){
                    if(label[y][x] == -1){ // not visited
                        q.push(pair<int, int>(x, y));
                        break;
                    }
                }
            }
            if(q.size() > 0){
                break;
            }
        }

        if(q.size() == 0){
            break;
        }

        int area = 0;
        while(q.size() > 0){
            auto p = q.front(); q.pop();
            auto x = p.first;
            auto y = p.second;

            if(label[y][x] == -1){
                label[y][x] = label_index;
                area++;
            }

            auto next_x = x;
            auto next_y = y-1;
            if(next_y >=0){
                if(label[next_y][next_x] == -1){
                    if(matrix[next_y][next_x] == 1){
                        q.push(pair<int, int>(next_x, next_y));
                    }
                }
            }

            next_x = x-1;
            next_y = y;
            if(next_x >=0){
                if(label[next_y][next_x] == -1){
                    if(matrix[next_y][next_x] == 1){
                        q.push(pair<int, int>(next_x, next_y));
                    }
                }
            }

            next_x = x;
            next_y = y+1;
            if(next_y < N){
                if(label[next_y][next_x] == -1){
                    if(matrix[next_y][next_x] == 1){
                        q.push(pair<int, int>(next_x, next_y));
                    }
                }
            }

            next_x = x+1;
            next_y = y;
            if(next_x < N){
                if(label[next_y][next_x] == -1){
                    if(matrix[next_y][next_x] == 1){
                        q.push(pair<int, int>(next_x, next_y));
                    }
                }
            }
        }
        areas.push_back(area);
    }

    if(areas.size() == 0) {
        printf("0");
    } 
    else{
        sort(areas.begin(), areas.end(), [](int a, int b){return a<b;});

        printf("%d\n", areas.size());
        for(int i=0;i<areas.size()-1;i++){
            printf("%d ", areas[i]);
        }
        printf("%d", areas.back());
    }
    return 0;
}
