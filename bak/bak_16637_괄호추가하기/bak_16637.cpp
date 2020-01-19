#include <iostream>
#include <vector>

using namespace std;

int max_result = -2147483648; 

bool is_digit(char c){
    if(c-'0'>=0 && c-'0'<=9) return true;
    else return false;
}

int cal(int a, int b, char operand){
    if(operand=='+') return a+b;
    else if(operand=='-') return a-b;
    else if(operand=='*') return a*b;
}

void find_max(int cur_operator_idx, bool prev_use_parenthesis, vector<bool> use_parenthesis_list, 
              vector<char> operator_list,  vector<int> operand_list){
    if(cur_operator_idx==operand_list.size()-1){
        // 종료할 때 계산하고 max 계산
        int result = 0;
        int operand_idx = 0; // !!! 막 조건을 만들고 있었는데 이게 더 효율적인듯!
        
        vector<char> without_parenthesis_operator;
        vector<int> parenthesise_calculated;
        // 일단 result 계산
        bool push_last = false;
        for(int i=0; i<operator_list.size();i++){
            // 괄호 먼저 계산하고 vector에 넣음
            if(use_parenthesis_list[i] == true){
                parenthesise_calculated.push_back(cal(operand_list[operand_idx],operand_list[operand_idx+1],operator_list[i]));
                operand_idx +=2; // 두개 사용해서
                push_last=true; // 괄호 한번이라도 사용하면 끝에건 들어간다
            }
            // 양쪽이 괄호일때는 아예 안집어 넣는다(3+8*7-9*2 1001일 때 오른쪽만 괄호일떄도 문제 생김)
            else if(i>0&& use_parenthesis_list[i+1] == true && push_last==true){// && use_parenthesis_list[i-1] == true){
                // !!!!! operator는 넣어야 한다!
                without_parenthesis_operator.push_back(operator_list[i]); // 괄호 없는것만 모으기
            }
            else{  // 아니면 하나만집어넣는다.
                parenthesise_calculated.push_back(operand_list[operand_idx]);
                operand_idx++;
                without_parenthesis_operator.push_back(operator_list[i]); // 괄호 없는것만 모으기
            }
        }
        
        // 다 끝나도 못집어 넣을 수도 있다(전부 괄호 없을 때)
        if(push_last==false) parenthesise_calculated.push_back(operand_list[operand_list.size()-1]);

        // for(int i=0; i< parenthesise_calculated.size(); i++) cout << parenthesise_calculated[i] << " ";
        // cout << "\n";
        // for(int i=0; i< without_parenthesis_operator.size(); i++) cout << without_parenthesis_operator[i] << " ";
        // cout << "\n";
        // for(int i=0; i< use_parenthesis_list.size(); i++) cout << use_parenthesis_list[i] << " ";
        // cout << "\n";
        
        // 헷갈리니까

        result = parenthesise_calculated[0];// 일단 이제 오른쪽꺼를 계속 사용하면 되니까 왼쪽거는 미리 넣는다.
        for(int i=0; i<without_parenthesis_operator.size();i++){
            // 다음 괄호 없는 list 끼리 계산
            result = cal(result,parenthesise_calculated[i+1],without_parenthesis_operator[i]);
        }
         
        if(result> max_result) max_result = result;
    }else{
        if(prev_use_parenthesis==true){
            // 이제 parenthesis 쓰면 안됨!
            use_parenthesis_list[cur_operator_idx] = false;
            find_max(cur_operator_idx+1, false, use_parenthesis_list, operator_list, operand_list);
        }else{
            use_parenthesis_list[cur_operator_idx] = false;
            find_max(cur_operator_idx+1, false, use_parenthesis_list, operator_list, operand_list);

            use_parenthesis_list[cur_operator_idx] = true; // ???이렇게 두번 쓰는게 좋을지... ㅜㅜ
            find_max(cur_operator_idx+1, true, use_parenthesis_list, operator_list, operand_list);
        }
    }
}

int main(){
    int exp_len;
    cin >> exp_len;
    string exp;
    cin >> exp;

    // vector<char> operator_list(exp.length()/2); // 이런식으로 쓰고 그 뒤에 push_back 하면 00 채워지고 뒤에 나옴
    vector<char> operator_list;
    vector<int> operand_list; // operand가 한개 더 많다.
    vector<bool> use_parenthesis_list(exp.length()/2, false);
    // char * operator_list = new char[exp.length()/2];
    // char * operand_list = new char[exp.length()/2];

    for (int i=0; i<exp.size(); i++){
        if(i%2==0) operand_list.push_back(exp[i]-'0');
        else operator_list.push_back(exp[i]); // 
    }

    find_max(0,false, use_parenthesis_list, operator_list, operand_list);
    cout << max_result;
    return 0;
}