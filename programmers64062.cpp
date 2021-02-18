#include <string>
#include <vector>

using namespace std;

int solution(vector<int> stones, int k) {
    int answer = 0;
    
    while(true){
        int n_skip = 1;
        for(int i=0;i<stones.size();i++){
            if(stones[i] == 0){
                n_skip ++ ;
                if(n_skip > k){
                    return answer;
                }
            }
            else{
                n_skip = 1;
                stones[i] --;
            }
        }
        answer++;
    }
    
    return answer;
}