#include <stdio.h>
#include <math.h>
int main()
{
    int A, B, C;
    scanf("%d %d %d", &A, &B, &C);
    
    if(B >= C){
        printf("-1");
    }else{
        printf("%d", (int)floor((float)A/(float)(C-B)) + 1);    
    }
    
    return 0;
}