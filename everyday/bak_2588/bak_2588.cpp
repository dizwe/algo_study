#include <iostream>
#include <array>
#include <string>
#include <cmath>
using namespace std;

int main(){
    int a, b;
    cin >> a;
    cin >> b;

    // to_string 어떻게든 다 string으로 바뀜
    
    // string -> int stoi
    // stoi = string to int
    // stof = string to float
    // stol = string to long int
    // stod = string to double

    // char* -> int atoi 마지막에 null 문자 쓸때 
    // atoi = char to int = 문자열을 정수 타입으로
    // atof = char to double = 문자열을 실수 타입으로
    // atol = char to long int = 문자열을 long 정수 타입으로

    // // 세자리라고 주어져있었음!(그래도 좀 활용해서 여러자리로 해보자!)
    // cout << to_string(b).length();
    int digit_num = to_string(b).length();
    // array<int, k> every_digit; // 이런식으로 변수를 쓰면 안되고 상수(ex.3)로 써야 함
    int* every_digit = new int[digit_num]; 
    // %하면 1000 나누면 일의자리가 아니라 900으로 나온다 
    // digit 별로 넣기(0이 첫번째 자리) 
    for(int i =0;i<digit_num;i++){
        every_digit[digit_num-i-1] = a*(to_string(b)[i]-'0');
    }
    
    int total_num = 0;
    for(int i =0;i<digit_num;i++){
        total_num += every_digit[i]*(int)pow(10,i);
        cout << every_digit[i] << "\n";
    }
    cout << total_num << "\n";
    return 0; 
}