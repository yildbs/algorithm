#include <string>
#include <map>
#include <vector>

using namespace std;

enum class STATE{
    DONT_KNOW,
    NOT_CONVERTEDFIX,
    CONDITION1FIX,
    CONDITION2FIX,
    CONDITION12FIX,
    CONDITION1,
    CONDITION2,
    CONDITION12,
};

bool islower(char c){
    if('a' <= c && c <= 'z'){
        return true;
    }
    return false;
}
bool isupper(char c){
    if('A' <= c && c <= 'Z'){
        return true;
    }
    return false;
}

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
string solution(string sentence) {

    sentence += " ";
    
    map<char, bool> used;
    for(char c='a';c<='z';c++){
        used[c] = false;
    }
    
    int start = 0;
    STATE word_left = STATE::DONT_KNOW;
    char c_condition1;
    char c_condition2;
    string str_org;
    vector<string> strings;
    for(int i=0;i<sentence.length();){
        bool increase_i = true;
        auto c = sentence[i];
        if(c == ' '){
            if(str_org != ""){
                strings.push_back(str_org);
            }
            break;
        }

        bool end_word = false;

        if(start == 0){
            if(islower(c)){
                //소문자로 시작
                word_left = STATE::CONDITION2;
                if(used[c]){
                    return "invalid";
                }
                else{
                    used[c] = true;
                }
                c_condition2 = c;
            }
            else{
                //대문자로 시작
                word_left = STATE::CONDITION1;
                str_org.push_back(c);
            }
            start++;
        }
        else if(word_left == STATE::CONDITION1 && start == 1){
            if(islower(c)){
                //대문자+소문자
                word_left = STATE::CONDITION1FIX;
                if(used[c]){
                    return "invalid";
                }
                else{
                    used[c] = true;
                }
                c_condition1 = c;
            }
            else{
                //대문자+대문자
                word_left = STATE::NOT_CONVERTEDFIX;
                str_org.push_back(c);
            }
            start++;
        }
        else if(word_left == STATE::CONDITION2 && start == 1){
            if(islower(c)){
                //소문자+소문자 invalid
                return "invalid";
            }
            else{
                //소문자+대문자
                word_left = STATE::CONDITION2; 
                str_org.push_back(c);
                //아직 가능성이 남아있음
                // 소문자+대문자+소문자 --> CONDITION12FIX
                // 소문자+대문자+대문자 --> CONDITION2FIX
            }
            start++;
        }
        else if(word_left == STATE::CONDITION2 && start == 2){
            if(islower(c)){
                // 소문자+대문자+소문자 --> CONDITION12FIX
                word_left = STATE::CONDITION12FIX;
                if(used[c]){
                    return "invalid";
                }
                else{
                    used[c] = true;
                }
                if(c == c_condition2){
                    //invalid
                    return "invalid";
                }
                c_condition1 = c;
            }
            else{
                // 소문자+대문자+대문자 --> CONDITION2FIX
                word_left = STATE::CONDITION2FIX;
                str_org.push_back(c);
            }
            start++;
        }
        else if(word_left == STATE::CONDITION1FIX){ 
            if(start % 2 == 1){
                if(islower(c)){
                    if(c == c_condition1){
                        //규칙에 맞음 패스
                        start++;
                    }
                    else{
                        //다른 문자의 시작이라고봐야함
                        //규칙 2 혹은 규칙 12의 문자열 시작
                        end_word = true;
                    }
                }
                else{
                    //다른 문자의 시작이라고봐야함
                    //규칙 1 혹은 NOTCONVERTED 문자열의 시작
                    end_word = true;
                }
            }
            else{
                //대문자이므로 문자 수집해야함
                str_org.push_back(c);
                start++;
            }
        }
        else if(word_left == STATE::CONDITION2FIX){ 
            if(islower(c)){
                //다른 문자의 시작이라고봐야함
                //규칙 1 혹은 NOTCONVERTED 문자열의 시작
                end_word = true;
                i++;
            }
            else{
                //대문자이므로 문자 수집해야함
                str_org.push_back(c);
                start++;
            }
        }
        else if(word_left == STATE::CONDITION12FIX){ 
            if(start % 2 == 1){ // 홀수번째 --> 소문자 
                if(islower(c)){
                    if(c == c_condition2){ // 문자열의 끝
                        //다른 문자의 시작이라고봐야함
                        //규칙 1 혹은 NOTCONVERTED 문자열의 시작
                        end_word = true;
                    }
                    else if(c == c_condition1){ //패스
                        start++;
                    }
                    else{
                        //invalid
                        return "invalid";
                    }
                }
                else{
                    //invalid
                    return "invalid";
                }
            }
            else{
                str_org.push_back(c);
                start++;
            }
        }
        else if(word_left == STATE::NOT_CONVERTEDFIX){ 
            str_org.push_back(c);
            start++;
        }

        if(end_word){
            strings.push_back(str_org);
            str_org = "";
            start = 0;
            increase_i = false;
            word_left = STATE::DONT_KNOW;
            c_condition1 = 0;
            c_condition2 = 0;
        }

        if(increase_i){
            i++;
        }
    }

    string answer = strings[0];strings.erase(strings.begin());
    for(auto str : strings){
        answer.push_back(' ');
        answer += str;
    }

    return answer;
}




int main()
{
    vector<string> answers;
    answers.push_back(solution("AxAxAxABcCc"));
//    answers.push_back(solution("SpIpGpOpNpGJqOqA"));
//    answers.push_back(solution("HaEaLaLaObWORLDb"));
//    answers.push_back(solution("AxAxAxAoBoBoB"));

}