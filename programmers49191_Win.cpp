#include <stdio.h>
#include <vector>
#include <iostream>

using namespace std;


int solution(int n, vector<vector<int>> results) 
{
    vector<vector<int>> graph(n+1, vector<int>(n+1, 0));

    for(auto r : results){
        graph[r[0]][r[1]] = 1;
    }

    for(int i=1;i<=n;i++){ // b
        for(int j=1;j<=n;j++){ // a
            for(int k=1;k<=n;k++){ // c
                if(graph[j][i] == 1 && graph[i][k] == 1){
                    graph[j][k] = 1;
                }
            }
        }
    }

    int answer = 0;

    for(int i=1;i<=n;i++){
        int count_1 = 0;
        for(int j=1;j<=n;j++){
            if(graph[j][i] == 1){
                count_1 ++;
            }
        }
        for(int j=1;j<=n;j++){
            if(graph[i][j] == 1){
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