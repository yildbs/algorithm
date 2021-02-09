#include <stdio.h>
#include <vector>
#include <iostream>

using namespace std;



int solution(int n, vector<vector<int>> results) 
{
    vector<vector<int>> graph(n+1, vector<int>(n+1, 0));

    //A가 B에게 이긴 경우 1로 표시
    //B가 A에게 진 경우 -1로 표시
    for(auto r : results){
        graph[r[0]][r[1]] = 1; //win
        graph[r[1]][r[0]] = -1; //lost
    }


    //플루이드 워셜 알고리즘
    for(int i=1;i<=n;i++){ // b
        for(int j=1;j<=n;j++){ // a
            for(int k=1;k<=n;k++){ // c
                //j가 i를 이기고, i가 k를 이기는 경우
                //j가 k를 이긴다
                if(graph[j][i] == 1 && graph[i][k] == 1){
                    graph[j][k] = 1;
                }
                //j가 i에게 지고, i가 k에게 지는 경우
                //j는 k에게 진다
                if(graph[j][i] == -1 && graph[i][k] == -1){
                    graph[j][k] = -1;
                }
            }
        }
    }

    int answer = 0;
    //i를 기준으로
    for(int i=1;i<=n;i++){
        int count_1 = 0;
        //i가 j에게 이이거나 지는 경우
        for(int j=1;j<=n;j++){
            if(graph[i][j] == 1 || graph[i][j] == -1){
                count_1 ++;
            }
        }
        if(count_1 == n-1){
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