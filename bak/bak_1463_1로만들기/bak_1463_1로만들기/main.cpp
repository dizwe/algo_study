//
//  main.cpp
//  bak_1463_1로만들기
//
//  Created by dizwe on 2020/04/18.
//  Copyright © 2020 dizwe. All rights reserved.
//

#include <iostream>
#include <climits>
using namespace std;
int N;
int *memorize;
void find_min(int);
// 조금이라도 의심이 들면 ㅋㅋㅋ 1부텈ㅋㅋ

int main(int argc, const char * argv[]) {
    cin >> N;
    memorize = new int[N+1];
    fill(&memorize[1], &memorize[N+1], 0);
    // 예외적인 가장 작은 경우도 생각해야함!!
    if (N==1)
        cout << 0;
    else
        find_min(N-1);// index니까 10이면 9까지 
}

void find_min(int n){

    int sub_one = INT_MAX, div_two = INT_MAX, div_three = INT_MAX;
    if(n +1 <= N) // 1로 뺀거
        sub_one = memorize[n+1]+1;
    if(n*2 <= N) // 2로 나눈거
        div_two = memorize[n*2]+1;
    if(n*3 <= N) // 3으로 나눈거
        div_three = memorize[n*3]+1;;
    
    int cal_num= min(sub_one, div_two);
    cal_num = min(cal_num, div_three);
    memorize[n] = cal_num;
    
    if(n==1) cout << memorize[1];
    else find_min(n-1);
}
