/******
 * 백준 1753번 최단경로 (https://www.acmicpc.net/problem/1753)
 * Author : yildbs
 */

#include <stdio.h>
#include <vector>
#include <queue>
#include <map>

using namespace std;

const int INF = 0xFFFFFF;

int main()
{
    int V, E;
    scanf("%d %d", &V, &E);
    V += 1;
    
    int start = 0;
    scanf("%d", &start);

#if 0 // 메모리 초과
    vector<vector<int>> graph;
    graph.resize(V);
    for(auto &g : graph){
        g.resize(V);
        for(auto &gg : g){
            gg = INF;
        }
    }
    for(int v=0;v<V;v++){
        graph[v][v] = 0;
    }

    for(int e=0;e<E;e++){
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = w;
    }
#endif
    map<pair<int, int>, int> graph2;
    for(int e=0;e<E;e++){
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph2[pair<int, int>(u, v)] = w;
    }

    ////////////////////////

    vector<int> dist;
    dist.resize(V);
    for(int v=0;v<V;v++){
        dist[v] = INF;
    }
    dist[start] = 0;
    priority_queue<pair<int, int>> q;// (-cost, index)
    q.push(pair<int, int>(0, start));

    while(q.empty()==false){
        auto next = q.top();q.pop();
        auto next_index = next.second;
        auto distance = -next.first;

        if(distance > dist[next_index]){
            continue;
        }

        for(int i=0;i<V;i++){
#if 0
            if(dist[i] > dist[next_index] + graph[next_index][i]){
                dist[i] = dist[next_index] + graph[next_index][i];
                q.push(pair<int, int>(-dist[i], i));
            }
#endif
            if(graph2.find(pair<int, int>(next_index, i)) != graph2.end()){
                auto n_to_i = graph2[pair<int, int>(next_index, i)];
                if(dist[i] > dist[next_index] + n_to_i){
                    dist[i] = dist[next_index] + n_to_i;
                    q.push(pair<int, int>(-dist[i], i));
                }
            }
        }
    }

    for(int i=1;i<V;i++){
        if(dist[i] == INF){
            printf("INF\n");
        }
        else{
            printf("%d\n", dist[i]);
        }
    }

}