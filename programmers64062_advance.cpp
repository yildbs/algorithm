#include <string>
#include <vector>
#include <set>
#include <queue>

using namespace std;

typedef pair<int, int> pi;

bool is_end(set<int> indices, int k){
    int streak = 1;
    auto it = indices.begin();
    int previous = *it; it++;
    for(;it!=indices.end();it++){
        if(*it == previous+1){
            streak ++;
            if(streak >= k){
                return true;
            }
        }
        else{
            streak = 1;
        }
        previous = *it;
    }
    return false;
}

int solution(vector<int> stones, int k) {
    
    priority_queue<pi, vector<pi>, greater<pi>> pq;
    for(int i=0;i<stones.size();i++){
        pq.push(pi(stones[i], i));
    }
    
    int answer = 0;
    set<int> indices;
    while(true){
        auto top = pq.top();
        int max_stone = pq.top().first;
        while(pq.empty() == false){
            if(pq.top().first == top.first){
                indices.insert(pq.top().second);
                pq.pop();
            }
            else{
                break;
            }
        }
        answer ++;
        if(is_end(indices, k)){
            return max_stone+1;
        }
    }
    
    return answer;
}

int main()
{
    //vector<int> stones {2, 4, 5, 3, 2, 1, 4, 2, 5, 1};
    vector<int> stones {4, 4, 4, 2, 2, 1, 4, 4, 4, 4, 4};

    solution(stones, 3);


}