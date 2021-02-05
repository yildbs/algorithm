/******
 * 백준 1038번 감소하는 수 (https://www.acmicpc.net/problem/1038)
 * Author : yildbs
 */

#include <stdio.h>
#include <string>
#include <math.h>

using namespace std;

//감소하는 수인지 판단하는 함수
bool is_reducing(string n)
{
    //문자열 하나하나 비교하여 판단
    for(long long i=0;i<n.length()-1;i++){
        if(n.at(i) <= n.at(i+1)){
            return false;
        }
    }
    return true;
}

//다음 감소하는 수 찾는 함
long long next_number(string str)
{
    long long n = stol(str);

    while(true){
        bool reducing = true;
        str = to_string(n);
        for(long long i=0;i<str.length()-1;i++){
            if(str.at(i) <= str.at(i+1)){
                long long p = str.length() - i - 1;
                n += pow(10, p);
                n -= pow(10, p-1) * (str.at(i+1) - '0');
                reducing = false;
                break;
            }
        }
        if(reducing){
            break;
        }
    }

    return n;
}


int main()
{
#if 0 //테스트용 코
    long long ccc=0;
    long long aa=0;
    while(true){
        if(is_reducing(to_string(aa))){
            printf("%d : %d\n", ccc++, aa);
            aa++;
        }
        else{
            aa = next_number(to_string(aa));
        }
    }
    return 0;
#endif

    int N;
    scanf("%d", &N);

    int n = 0;
    for(long long i=0;;){
        if(is_reducing(to_string(i))){
            if(n++ == N){
                printf("%lld", i); 
                return 0;
            }
            i++;
        }
        else{
            i = next_number(to_string(i));
        }
        //감소하는 수 중에서 제일 큰 수 
        if(i>9876543210ll){
            break;
        }
    }
    printf("-1"); 
    return 0;
}
