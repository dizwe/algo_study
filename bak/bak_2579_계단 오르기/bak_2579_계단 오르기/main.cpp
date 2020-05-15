//
//  main.cpp
//  bak_2579_계단 오르기
//
//  Created by dizwe on 2020/05/15.
//  Copyright © 2020 dizwe. All rights reserved.
//

#include <iostream>
#define MAX_SIZE 300
using namespace std;

int main(int argc, const char * argv[]) {
    int N;
    cin >> N;
    int stairs[MAX_SIZE+2];
    int dp[MAX_SIZE+2];
    for (int n=0; n<N; n++){
        cin >> stairs[n];
    }
    
    dp[0] = stairs[0];
    dp[1] = stairs[0]+stairs[1];
    dp[2] = max(stairs[0]+stairs[2], stairs[1]+stairs[2]);
    
    for(int i=3; i<N; i++){
        int one_step_before = dp[i-3] + stairs[i-1] + stairs[i];
        int two_step_before = dp[i-2] + stairs[i];
        if(one_step_before> two_step_before){
            dp[i] = one_step_before;
        }else{
            dp[i] = two_step_before;
        }
    }
    cout << dp[N-1];
    return 0;
}
