/******
 * 백준 1092번 배 (https://www.acmicpc.net/problem/1092)
 * Author : yildbs
 */
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <map>
#include <list>

using namespace std;

int main()
{
    int N_num_of_cranes;
    int M_num_of_boxes;

    vector<int> cranes;
    list<int> boxes;

    scanf("%d", &N_num_of_cranes);
    cranes.reserve(N_num_of_cranes);
    for(int n=0;n<N_num_of_cranes;n++){
        int c = 0;
        scanf("%d", &c);
        cranes.push_back(c);
    }

    scanf("%d", &M_num_of_boxes);
    for(int m=0;m<M_num_of_boxes;m++){
        int c = 0;
        scanf("%d", &c);
        boxes.push_back(c);
    }


    //1. 크레인 입력 받아서 내림차순으로 정렬
    //2. 박스 입력 받아서 내림차순으로 정렬
    sort(cranes.begin(), cranes.end(), [](int a, int b){return a > b;});
    boxes.sort([](int a, int b){return a > b;});

    //3. 최대 무게 크레인이 처리할 수 없는 박스 있는지 체크
    if(cranes.front() < boxes.front() ){
        printf("-1");
        return 0;
    }

    int count_move = 0;

    auto crane = cranes.begin();
    auto box = boxes.begin();
    //4. 박스와 크레인 루프 돌리면서 박스 하나씩 제거하기
    while(true){
        //5. 박스 개수가 0이 되면 출력하고 종료
        if(boxes.size() == 0){
            printf("%d", count_move);
            return 0;
        }
        //4.1. 특정 박스를 처리하지 못하는 크레인이 있다면 다음 가벼운 박스로
        //4.2. 박스나 크레인의 끝에 도달한다면 횟수 증가
        if(*crane >= *box){
            box = boxes.erase(box);
            if(box == boxes.end()){
                count_move++;
                box = boxes.begin();
                crane = cranes.begin();
                continue;
            }

            crane++;
            if(crane == cranes.end()){
                count_move++;
                box = boxes.begin();
                crane = cranes.begin();
                continue;
            }
        }
        else{
            box++;
            if(box == boxes.end()){
                count_move++;
                box = boxes.begin();
                crane = cranes.begin();
                continue;
            }
        }
    }
    return 0;
}