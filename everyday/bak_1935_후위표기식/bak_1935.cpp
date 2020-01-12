#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

int main(){
    int operand_num;
    
    string expression;
    cin >> operand_num;
    
    // 값 받고 선언해줘야 메모리 낭비가 안생긴다!
    vector<double> operand_val(operand_num,0);
    cin >> expression;

    double temp;

    for(int i=0; i<operand_num; i++){
        cin >> temp; // 바로 vector를 넣지는 못하나봐
        operand_val[i] = temp; 
    }

    stack <double> op_stack;

    // char arr[] = {'+','-','/','*'};
    // vector<char> operator_vector(arr,arr+4);
    double temp_a,temp_b;
    // length 는 따로 비교해줘야 한다.

    for(int i=0; i<(int)expression.length();i++){ 
        // 그 중에 값이 없다면
        // if(find(operator_vector.begin(), operator_vector.end(),expression[i])== operator_vector.end()){
        //     op_stack.push(operand_val[expression[i]-'A']);
        // }
        if(expression[i]!='+' && expression[i]!='-' && expression[i]!='*' && expression[i]!='/'){
            op_stack.push(operand_val[expression[i]-'A']);
        }
        else{ 
            // a,b 순서가 바뀌어야 함
            // top 하고 return 해야 함
            temp_b = op_stack.top();
            op_stack.pop();
            temp_a = op_stack.top();
            op_stack.pop();
            double temp_result; 
            if(expression[i] == '+') temp_result = temp_a+temp_b;
            else if(expression[i] == '-') temp_result = temp_a-temp_b;
            else if(expression[i] == '*') temp_result = temp_a*temp_b;
            else if(expression[i] == '/') temp_result = temp_a/temp_b;
            op_stack.push(temp_result);
        } 
    }
    
    double result = op_stack.top();
    op_stack.pop();
    printf("%.2f",result);

    return 0;
}