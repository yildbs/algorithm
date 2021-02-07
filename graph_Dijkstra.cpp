#include <stdio.h>
#include <vector>
#include <queue>

using namespace std;

const int INF = 0xFFFF;

int get_closest_index(vector<int> &d, vector<bool> &v)
{
    int index = -1;
    int min_d = INF;
    for(int i=0;i<d.size();i++){
        if(v[i] == false){
            if(min_d > d[i]){
                index = i;
                min_d = d[i];
            }
        }
    }
    return index;
}

void dijkstra(int start, vector<vector<int>> dist)
{
    int N = dist.size();
    vector<int> d; d.resize(N);
    for(auto &_d : d){ _d = INF; }
    for(int i=0;i<N;i++){
        d[i] = dist[start][i];
    }
    vector<bool> v; v.resize(N);
    for(auto && _v : v) _v = false;

    for(int n=0;n<N-1;n++){
        auto closest_index = get_closest_index(d, v);
        if(closest_index == -1){
            break;
        }
        for(int i=0;i<d.size();i++){
            if(i != closest_index){
                if(d[i] > d[closest_index] + dist[closest_index][i]){
                    d[i] = d[closest_index] + dist[closest_index][i];
                }
            }
        }
        v[closest_index] = true;
    }
}

void dijkstra_practice(int start, vector<vector<int>> dist)
{
    int N = dist.size();
    vector<int> d;d.resize(N);
    for(auto &_d : d){
        _d = INF;
    }
    for(int i=0;i<N;i++){
        d[i] = dist[start][i];
    }

    vector<bool> v;v.resize(N);
    for(auto &&_v : v){
        _v = false;
    }

    for(int n=0;n<N-1;n++){
        int index = get_closest_index(d, v);
        if(index == -1){ break; }
        v[index] = true;

        for(int i=0;i<N;i++){
            if(d[i] > d[index] + dist[index][i]){
                d[i] = d[index] + dist[index][i];
            }
        }
    }

    for(int n=0;n<N-1;n++){
        printf("%d ", d[n]);
    }
}

void dijkstra_priority_queue(int start, vector<vector<int>> dist)
{
    int N = dist.size();
    priority_queue<pair<int, int>> q; // (dist * -1, index)

    vector<int> d;
    d.resize(N);
    for(auto &dd : d){
        dd = INF;
    }
    d[start] = 0;

    q.push(pair<int, int>(0, start));
    while(q.empty() == false){
        auto next = q.top();q.pop();
        auto index = next.second;
        auto distance = -next.first;

        for(int i=0;i<N;i++){
            if(d[i] > d[index] + dist[index][i]){
                d[i] = d[index] + dist[index][i];
                q.push(pair<int, int>(-d[i], i));
            }
        }
    }

    for(int n=0;n<N-1;n++){
        printf("%d ", d[n]);
    }
}


int main()
{
    int N = 10;
    vector<vector<int>> dist;
    dist.resize(N);
    for(auto &r : dist) {
        r.resize(N);
        for(auto &d : r){
            d = INF;
        }
    }

    dist[0][1] = 4;
    dist[0][2] = 2;
    dist[1][3] = 4;
    dist[1][4] = 5;
    dist[2][4] = 4;
    dist[4][5] = 2;
    dist[3][5] = 1;

    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(dist[i][j] != INF){
                dist[j][i] = dist[i][j];
            }
        }
    }
    for(int i=0;i<N;i++){
        dist[i][i] = 0;
    }

    ////////////////////////

    priority_queue<pair<int, int>> q;
    q.push(pair<int, int>(10, 10));
    q.push(pair<int, int>(9, 10));
    q.push(pair<int, int>(11, 10));
    q.push(pair<int, int>(15, 10));
    q.push(pair<int, int>(1, 10));
    q.push(pair<int, int>(6, 10));
    while(q.empty() == false){
        printf("%d\n", q.top());
        q.pop();
    }


    // dijkstra(0, dist);
    printf("Answer\n");
    dijkstra_practice(1, dist);
    printf("Test \n");
    dijkstra_priority_queue(1, dist);


}