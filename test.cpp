#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

int main()
{
    string line;
    getline(cin, line);

    int count = 0;
    for(auto c : line){
        if(c == ' '){
            count++;
        }
    }

    count -= line.front() == ' ' ? 1 : 0;
    count -= line.back() == ' ' ? 1 : 0;

    printf("%d", count+1);

}