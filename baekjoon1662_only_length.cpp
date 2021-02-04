#include <stdio.h>
#include <string>

int decode(std::string str)
{
    int index_cut_left = -1;
    int index_cut_right = -1;
    int index = 0;
    for(int i=0;i<str.length();i++){
        if(str.at(i) == '('){
            if(index_cut_left == -1){
                index_cut_left = i;
            }
            index++;
        }
        else if(str.at(i) == ')'){
            if(--index == 0){
                index_cut_right = i;
                break;
            }
        }
    }

    if(index_cut_left == -1 && index_cut_right == -1){
        return str.length();
    }

    auto rest = str.substr(index_cut_right+1);
    auto length_rest = decode(rest);
    auto right = str.substr(index_cut_left+1, index_cut_right-index_cut_left-1);
    auto length_right = decode(right);
    auto left = stoi(str.substr(index_cut_left-1, 1));
    auto prefix = str.substr(0, index_cut_left-1);

    return prefix.length() + length_right * left + length_rest;
}

int main()
{
    char c_str[51];
    scanf("%s", c_str);
    
    std::string str(c_str);
    printf("%d", decode(str));
}