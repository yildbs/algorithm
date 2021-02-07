/******
 * 백준 1753번 최단경로 (https://www.acmicpc.net/problem/1753)
 * Author : yildbs
 */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 0xFFFFFF;

int main()
{
    int num_of_vertex, num_of_edges, start;
    scanf("%d %d", &num_of_vertex, &num_of_edges);
    scanf("%d", &start);

    //각 노드에서 특정 노드로의 비용이 담긴 리스트
    vector<pair<int, int>> graph[20001];

    for(int i=0;i<num_of_edges;i++){
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph[u].push_back(pair<int, int>(v, w));
    }

    //num_of_vertex+1을 해주어 비어있는 0번 배열 대응
    vector<int> dist(num_of_vertex+1, INF);

    //갱신된 노드들이 들어오는 큐로 기본적으로 맥스힙이기 때문에 
    priority_queue<pair<int, int>> pq; // pair ( cost * -1, index )
    pq.push(pair<int, int>(0, start));
    dist[start] = 0;

    while(pq.empty()==false){
        auto next = pq.top(); pq.pop();
        auto next_index = next.second;
        auto next_cost = -next.first;

        for(auto target : graph[next_index]){
            auto target_index = target.first;
            auto target_cost = target.second;

            if(dist[target_index] > dist[next_index] + target_cost){
                dist[target_index] = dist[next_index] + target_cost;
                pq.push(pair<int, int>(-dist[target_index], target_index));
            }
        }
    }

    for(int i=1;i<=num_of_vertex;i++){
        if(dist[i] == INF){
            printf("INF\n");
        }
        else{
            printf("%d\n", dist[i]);
        }
    }
}