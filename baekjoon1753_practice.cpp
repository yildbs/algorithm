#include <iostream>
#include <vector>
#include <queue>
#include <stdio.h>


using namespace std;

const int INF = 0xFFFFFF;

int main()
{
    int V, E;
    cin >> V >> E;
    int K;
    cin >> K;

    vector<vector<pair<int, int>>> graph(V+1);

    for(int i=0;i<E;i++){
        int u, v, w;
        cin >> u >> v >> w;

        graph[u].push_back(pair<int, int>(v, w));
    }

    vector<int> dist(V+1, INF);
    dist[K] = 0;

    priority_queue<pair<int, int>> pq;
    pq.push(pair<int, int>(0, K));

    while(pq.empty() == false){
        auto next = pq.top();pq.pop();
        auto next_index = next.second;
        auto next_cost = -next.first;

        for(auto target : graph[next_index]){
            auto target_index = target.first;
            auto target_cost = target.second;

            if(dist[target_index] > dist[next_index] + target_cost){

            }
        }
    }
}

