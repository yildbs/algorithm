#include <stdio.h>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int main()
{
    int N, L, H;
    scanf("%d", &N);
    
    int maxL = 0;
    int maxH = 0;
    
    vector<pair<int, int>> columns;
    
    for(int i=0;i<N;i++){
        scanf("%d %d", &L, &H);
        if(maxL < L) maxL = L;
        if(maxH < H) maxH = H;
        columns.emplace_back(pair<int, int>(L, H));
    }
  
    vector<int> heights;
    heights.resize(maxL+1);
    for(auto &h : heights){
        h = 0;
    }
    for(auto c : columns){
        heights[c.first] = c.second;
    }
    
    int prev_h = 0;
    int left=0, right=0;
    for(int i=0;i<=maxL;i++){
        if(heights[i] == 0){
            heights[i] = prev_h;
        }
        else if(heights[i] > prev_h){
            prev_h = heights[i];
        }
        else if(heights[i] < prev_h){
            heights[i] = prev_h;
        }
        if(prev_h == maxH){
            left = i;
            break;
        }
    }
    
    prev_h = 0;
    for(int i=maxL;i>=0;i--){
        if(heights[i] == 0){
            heights[i] = prev_h;
        }
        else if(heights[i] > prev_h){
            prev_h = heights[i];
        }
        else if(heights[i] < prev_h){
            heights[i] = prev_h;
        }
        if(prev_h == maxH){
            right = i;
            break;
        }
    }
    
    for(int i=left;i<=right;i++){
        heights[i] = maxH;
    }

    int sum = 0;
    for(int i=0;i<=maxL;i++){
        sum += heights[i];
    }
    
    printf("%d", sum);
    return 0;
}
