/******
 * 백준 1753번 최단경로 (https://www.acmicpc.net/problem/1753)
 * Author : yildbs
 */

#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

const int INF = 0xFFFFFF;

int main()
{
    int V, E;
    int start;
    cin >> V >> E >> start;
    V += 1;

    vector<pair<int, int>> graph[20001];

    for(int i=0;i<E;i++){
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back(pair<int, int>(v, w));
    }

    priority_queue<pair<int, int>> pq; // -cost, index

    vector<int> dist(V, INF);
    dist[start] = 0;

    pq.push(pair<int, int>(0, start));

    while(pq.empty() == false){
        auto next = pq.top();pq.pop();
        auto next_index = next.second;
        auto next_cost = -next.first;

        for(auto t : graph[next_index]){
            auto target_index = t.first;
            auto target_cost = t.second;

            if(dist[target_index] > dist[next_index] + target_cost){
                dist[target_index] = dist[next_index] + target_cost;
                pq.push(pair<int, int>(-dist[target_index], target_index));
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