#include <stdio.h>
#include <vector>
#include <iostream>
#include <set>
#include <queue>

using namespace std;

//플레이어
class Player{
public:
    //이 플레이어가 이기는 녀석들 
    set<int> to_win;
    //이 플레이어가 지는 녀석들 
    set<int> to_lose;
};

int solution(int n, vector<vector<int>> results) 
{
    vector<Player> players(n+1);
    for(auto r : results){
        //r[0]은 r[1]에게 이긴다
        players[r[0]].to_win.insert(r[1]);
        //r[1]은 r[0]에게 진다
        players[r[1]].to_lose.insert(r[0]);
    }

    //이긴 녀석들 BFS로 루프 돌기
    for(int i=1;i<=n;i++){
        queue<int> q;
        for(auto j : players[i].to_win){
            q.push(j);
        }

        //방문 변수 
        vector<int> visited(n+1, false);
        while(q.empty() == false){
            auto current = q.front();q.pop();
            //이기는 녀석들이 이기는 녀석들은 다 순회하기
            for(auto j : players[current].to_win){
                players[i].to_win.insert(j);
                if(visited[j] == false){
                    q.push(j);
                    visited[j] = true;
                }
            }
        }
    }

    //진 녀석들 BFS로 루프 돌기
    for(int i=1;i<=n;i++){
        queue<int> q;
        for(auto j : players[i].to_lose){
            q.push(j);
        }
        vector<int> visited(n+1, false);
        while(q.empty() == false){
            auto current = q.front();q.pop();
            for(auto j : players[current].to_lose){
                players[i].to_lose.insert(j);
                if(visited[j] == false){
                    q.push(j);
                    visited[j] = true;
                }
            }
        }
    }

    //진녀석 + 이긴녀석 의 수가 N-1이면 결과 정해지는 것
    int answer = 0;
    for(int i=1;i<=n;i++){
        if(players[i].to_win.size() + players[i].to_lose.size() == n-1){
            answer++;
        }
    }

    return answer;
}

int main(){
    int n = 5;
    vector<vector<int>> results;

    results.push_back(vector<int>{4, 3});
    results.push_back(vector<int>{4, 2});
    results.push_back(vector<int>{3, 2});
    results.push_back(vector<int>{1, 2});
    results.push_back(vector<int>{2, 5});

    solution(n, results);

}