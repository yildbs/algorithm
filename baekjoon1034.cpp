/******
 * 백준 1034번 램프 (https://www.acmicpc.net/problem/1034)
 * Author : yildbs
 */

#include <algorithm>
#include <stdio.h>
#include <vector>
#include <string>
#include <map>

using namespace std;

int main()
{
    int N, M;
    // 1. N, M을 입력 받는다. 
    scanf("%d %d", &N, &M);

    map<string, int> rows;
    //2. 길이가 N인 문자열을 M개 입력 받는다.
    for(int n=0;n<N;n++){
        char row_[51] = {0, };
        scanf("%s", &row_);
        auto row = std::string(row_);

        //2.1. 입력 받으며 map을 사용해 상태가 같은 문자열의 개수를 카운트한다.
        if(rows.find(row) == rows.end()){
            rows[row] = 0;
        }
        rows[row] ++;
    }

    int K=0;
    scanf("%d", &K);

    //3. map을 숫자가 큰 순서로 소팅한다. (이때 map에서 vector로 변환됨)
    vector<pair<string, int>> ordered;
    for(auto it=rows.begin();it!=rows.end();it++){
        ordered.emplace_back(pair<string, int>(it->first, it->second));
    }
    auto compare = [](pair<string, int> a, pair<string, int> b){
        return a.second > b.second;
    };
    sort(ordered.begin(), ordered.end(), compare);
    
    //4. 문자열들을 순회하며, 해당 문자열이 K번 점멸 이후 켜져있는 행이 될 수 있을지 판단한다.
    for(auto o : ordered){
        auto count1 = [](string s){
            int num = 0;
            for(auto c : s){
                if (c == '1'){
                    num++;
                }
            }
            return num;
        };

        //1의 개수를 세고, 거기에 K를 더하면 M이 무한이라고 가정할때, 켜져있는 조명의 개수가 나온다(num_light)
        //num_light가 M보다 크다면, num_light-M이 홀수인지 짝수인지에 따라서 최종 num_light가 결정된다.
        int num_light = count1(o.first) + K;
        if(num_light > M){
            num_light = M - ((num_light-M) & 0x01);
        }
        //4.1 켜져있는 행이 될 수 있다면 해당 문자열의 개수를 출력하고 프로그램을 종료한다.
        if(num_light == M){
            printf("%d\n", o.second);
            return 0;
        }
    }

    //5. 모든 문자열들이 켜져있는 행이 될 수 없다면 0을 출력하고 프로그램을 종료한다, 
    printf("0\n");
    return 0;
}
