/******
 * 백준 1089번 스타트링크 타워(https://www.acmicpc.net/problem/1089)
 * Author : yildbs
 */

#include <stdio.h>
#include <string>
#include <memory>
#include <cstring>
#include <vector>
#include <math.h>

using namespace std;

//미리 각 difit에 맞는 문자열 생성 
// char* digit0 = "###    ==> 이걸 펼처둔것
//                 #.#
//                 #.#
//                 #.#
//                 ###";
char* digit0 = "####.##.##.####";
char* digit1 = "..#..#..#..#..#";
char* digit2 = "###..#####..###";
char* digit3 = "###..####..####";
char* digit4 = "#.##.####..#..#";
char* digit5 = "####..###..####";
char* digit6 = "####..####.####";
char* digit7 = "###..#..#..#..#";
char* digit8 = "####.#####.####";
char* digit9 = "####.####..####";

//고장난 전구의 배열이 특정한 숫자를 의미할 수 있는지 체크함
//normal : digitN (정상 배열)
//disordered : 고장난 배열 (키보드 입력 받는 값들)
bool is_possible(char* normal, char* disordered)
{
    for(int i=0;i<15;i++){
        if(disordered[i] == '#'){
            if(normal[i] == '.'){
                return false;
            }
        }
    }
    return true;
}

//순회하며 모든 가능성 탐색하는 함수
// --> 결국 시간 초과로 이 함수 사용 불가능
//candidate_digits : 각 자리별로 올수 있는 숫자들
//N : 자릿수
//answer : 가능한 모든 숫자들의 합을 저장하는 변수 
//count_num : 가능한 모든 숫자들의 개수
//level : 현재 자릿수 (0 ~ N까지)
void iterate(vector<int> candidate_digits[], int N, long long &answer, int &count_num, string &current, int level)
{
    if(level == N){
        auto num = stoll(current);
        answer += num;
        count_num ++;
        return;
    }

    for(auto i : candidate_digits[level]){
        current += to_string(i);
        iterate(candidate_digits, N, answer, count_num, current, level + 1);
        current.pop_back();
    }
}

int main()
{
    char digits[10][15];
    memcpy(digits[0], digit0, 15);
    memcpy(digits[1], digit1, 15);
    memcpy(digits[2], digit2, 15);
    memcpy(digits[3], digit3, 15);
    memcpy(digits[4], digit4, 15);
    memcpy(digits[5], digit5, 15);
    memcpy(digits[6], digit6, 15);
    memcpy(digits[7], digit7, 15);
    memcpy(digits[8], digit8, 15);
    memcpy(digits[9], digit9, 15);

    int N = 0;
    scanf("%d", &N);
    int W = 4 * N - 1;
    int H = 5;
    auto data = shared_ptr<char>(new char[W * H]);
    for(int i=0;i<H;i++){
        char line[50];
        scanf("%s", line);
        memcpy(&data.get()[W*i], line, W * sizeof(char));
    }

    //입력 받은 문자열에서 한글자씩 분리해서 길이가 15인 문자열로 만드는 과정
    char digits_input[10][16];
    for(int i=0;i<N;i++){
        int x = i * 4;
        for(int h=0;h<H;h++){
            memcpy(&digits_input[i][h*3], &data.get()[h*W+x], 3);
        }
    }

    //각 자리수에 대해서 가능한 후보 숫자들을 체크하는 과정
    vector<int> candidate_digits[9];
    for(int i=0;i<N;i++){
        for(int j=0;j<10;j++){
            if(is_possible(digits[j], digits_input[i])){
                candidate_digits[i].push_back(j);
            }
        }
        //특정한 자리수에서 만족할 수 있는 숫자가 없다면 -1 출력
        if(candidate_digits[i].size() == 0){
            printf("-1");
            return 0;
        }
    }

#if 0 //brute force 방법으로 시간초과 
    int count_num = 0;
    long long sum = 0;
    string current = "";
    iterate(candidate_digits, N, sum, count_num, current, 0);

    double answer = (double) sum / (double)count_num;
    printf("%lf", answer);
    return 0;
#else // 각 자릿수별로 평균을 구하는 과정
    // 1의 자리, 10의 자리, 100의 자리.... 각 자리수 별로 평균을 구해서 더한다
    double sum = 0.;
    for(int i=0;i<N;i++){
        double partial_sum = 0.;
        for(auto digit : candidate_digits[i]){
            partial_sum += digit * pow(10, N - i - 1);
        }
        partial_sum /= candidate_digits[i].size();
        sum += partial_sum;
    }
    printf("%lf", sum);
    return 0;
#endif
}
