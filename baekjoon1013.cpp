#include <regex>
#include <stdio.h>

int main()
{
    int T;
    scanf("%d", &T);

    std::regex re("(100+1+|01)+");

    char str[201];
    for(int i=0;i<T;i++){
        scanf("%s", str);

        if(std::regex_match(str, re)){
            printf("YES\n");
        }
        else{
            printf("NO\n");
        }
    }
} 


// 코드 참고
// https://modoocode.com/303