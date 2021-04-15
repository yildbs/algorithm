#include <stdio.h>

//-10억, 10억으로 초기화 
int max_value = -1000000000;
int min_value = 1000000000;

void traverse(int level, int N, int numbers[11], int ops[11], int *num_ops)
{
    if(level == N-1){
        int result = numbers[0];
        for(int i=0;i<N-1;i++){
            switch(ops[i]){
                case 0:
                result += numbers[i+1];
                break;
                case 1:
                result -= numbers[i+1];
                break;
                case 2:
                result *= numbers[i+1];
                break;
                case 3:
                if(result > 0){
                    result /= numbers[i+1];
                }
                else{
                    result = -((-result)/numbers[i+1]);
                }
                break;
            }
        }
        if(result > max_value){
            max_value = result;
        }
        if(result < min_value){
            min_value = result;
        }
    }

    for(int i=0;i<4;i++){
        if(num_ops[i] > 0){
            num_ops[i]--;
            ops[level] = i;
            traverse(level+1, N, numbers, ops, num_ops);
            num_ops[i]++;
        }
    }
}

int main()
{
    int N;
    int numbers[11];
    int ops[11];

    scanf("%d", &N);
    for(int i=0;i<N;i++){
        int v;
        scanf("%d", &v);
        numbers[i] = v;
    }

    int num_ops[4] = { 0,  };
    scanf("%d %d %d %d", &num_ops[0], &num_ops[1], &num_ops[2], &num_ops[3]);

    traverse(0, N, numbers, ops, num_ops);

    printf("%d\n", max_value);
    printf("%d\n", min_value);
}
