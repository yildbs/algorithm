#include <stdio.h>
#include <queue>

using namespace std;

// x, y를 입력하면 index를 구하는 함수
inline int get_index(int M, int y, int x)
{
    return y * M + x;
}

// index를 입력하면 x, y를 구하는 함수 
inline pair<int, int> get_x_y(int M, int index)
{
    return pair<int, int>(index/M, index%M); // return y, x
}

// 해당 영역이 아무것도 없는 영역인지 확인하는 함수 
bool is_safe(int N, int M, int y, int x, vector<int> &field)
{
    if(0<=x && x<=M-1 && 0<=y && y<=N-1 && field[get_index(M, y, x)] == 0){
        return true;
    }
    return false;
}

// 바이러스를 전파시켜 최종 형태의 지도에서 안전한 영역의 넓이를 구하는 함수 
int get_safe_area(int N, int M, vector<int> field, queue<pair<int, int>> virus)
{
    while(virus.empty() == false){
        auto v = virus.front(); virus.pop();
        auto y = v.first;
        auto x = v.second;

        //바이러스 좌표를 기준으로 상하좌우를 탐색해서 안전 영역이라면 바이러스를 퍼뜨림
        if(is_safe(N, M, y-1, x, field)){
            auto index = get_index(M, y-1, x);
            field[index] = 2;
            virus.push(get_x_y(M, index));
        }
        if(is_safe(N, M, y+1, x, field)){
            auto index = get_index(M, y+1, x);
            field[index] = 2;
            virus.push(get_x_y(M, index));
        }
        if(is_safe(N, M, y, x-1, field)){
            auto index = get_index(M, y, x-1);
            field[index] = 2;
            virus.push(get_x_y(M, index));
        }
        if(is_safe(N, M, y, x+1, field)){
            auto index = get_index(M, y, x+1);
            field[index] = 2;
            virus.push(get_x_y(M, index));
        }
    }
    int area = 0;
    for(auto f : field){
        if(f==0){
            area ++;
        }
    }
    return area;
}

int main()
{
    auto N = 0;
    auto M = 0;
    scanf("%d %d", &N, &M);

    vector<int> field(M*N, 0);
    queue<pair<int, int>> virus;
    for(auto y=0;y<N;y++){
        for(auto x=0;x<M;x++){
            int v=0;
            scanf("%d", &v);
            field[get_index(M, y, x)] = v;
            if(v == 2){
                virus.push(pair<int, int>(y, x));
            }
        }
    }

    int max_area = 0;
    for(int a=0;a<M*N;a++){
        //벽을 설치할 수 없다면 continue
        auto ap = get_x_y(M, a);
        if(is_safe(N, M, ap.first, ap.second, field)==false){ continue; }

        //벽 설치
        field[a] = 1;
        for(int b=a+1;b<M*N;b++){
            //벽을 설치할 수 없다면 continue
            auto bp = get_x_y(M, b);
            if(is_safe(N, M, bp.first, bp.second, field) == false){ continue; }

            //벽 설치
            field[b] = 1;
            for(int c=b+1;c<M*N;c++){
                //벽을 설치할 수 없다면 continue
                auto cp = get_x_y(M, c);
                if(is_safe(N, M, cp.first, cp.second, field) == false){ continue; }

                //벽 설치
                field[c] = 1;
                //새로 벽이 설치된 지도에서 바이러스 전파 후 넓이 구하기
                auto area = get_safe_area(N, M, field, virus);
                if(area > max_area){
                    max_area = area;
                }
                //벽 해제
                field[c] = 0;
            }
            //벽 해제
            field[b] = 0;
        }
        //벽 해제
        field[a] = 0;
    }
    printf("%d", max_area);
}
