#include <iostream>
#include <vector>
#include <queue>
#include <stdio.h>


using namespace std;

const int INF = 0xFFFFFF;

int main()
{
    int NofVertices, NofEdges;
    cin >> NofVertices >> NofEdges;

    int start;
    cin >> start;

    vector<pair<int, int>> graph[20001];
    for(int i=0;i<NofEdges;i++){
        int u, v, w;
        cin >> u >> v >> w;

        graph[u].push_back(pair<int, int>(w, v)); // u에서 v로 w 비용
    }

    vector<int> distance(NofVertices + 1, INF);
    distance[start] = 0;

    priority_queue<pair<int, int>> pq;
    pq.push(pair<int, int>(0, start));

    while(pq.empty() == false){
        auto next = pq.top();pq.pop();
        auto next_index = next.second;
        auto next_cost = -next.first;
        if(next_cost > distance[next_index]){
            continue;
        }

        for(int i=0;i<graph[next_index].size();i++){
            auto target = graph[next_index].at(i);
            auto target_index = target.second;
            auto target_cost = target.first;
            if(distance[target_index] > distance[next_index] + target_cost){
                distance[target_index] = distance[next_index] + target_cost;
                pq.push(pair<int, int>(-distance[target_index], target_index));
            }
        }
    }

    for(int i=1;i<=NofVertices;i++){
        if(distance[i] == INF){
            // cout << "INF" << endl;
            printf("INF\n");
        }
        else{
            // cout << distance[i] << endl;
            printf("%d\n", distance[i]);
        }
    }
}

