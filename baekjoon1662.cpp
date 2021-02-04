#include <stdio.h>
#include <string>

std::string decode(std::string str)
{
    int index_cut_left = 0;
    int index_cut_right = 0;
    for(int i=0;i<str.length();i++){
        if(str.at(i) == '('){
            index_cut_left = i;
            break;
        }
    }
    for(int i=str.length()-1;i>=0;i--){
        if(str.at(i) == ')'){
            index_cut_right = i;
            break;
        }
    }

    if(index_cut_left == 0 && index_cut_right == 0){
        return str;
    }

    auto right = str.substr(index_cut_left+1, index_cut_right-index_cut_left-1);
    right = decode(right);
    auto temp = right;

    auto left = stoi(str.substr(index_cut_left-1, 1));
    for(int i=0;i<left-1;i++){
        temp += right;
    }

    auto prefix = str.substr(0, index_cut_left-1);
    return prefix + temp;
}

int main()
{
    char c_str[51];
    scanf("%s", c_str);
    
    std::string str(c_str);

    printf("%d", decode(str).length());
    
}