//
//  main.cpp
//  bak_1912_연속합
//
//  Created by dizwe on 2020/05/25.
//  Copyright © 2020 dizwe. All rights reserved.
//

#include <iostream>
#define MAX_NUM 100000
using namespace std;

int N;
int num[MAX_NUM+2];
int sum[MAX_NUM+2];

int main(int argc, const char * argv[]) {
    cin >> N;
    
    for(int i=0; i<N; i++){
        cin >> num[i];
    }
    
    sum[0] = num[0];
    int max_sum = sum[0];
    for(int i=1; i<N; i++){
        if(num[i] > sum[i-1] + num[i]){
            sum[i] = num[i];
        }else{
            sum[i] = sum[i-1] + num[i];
        }
        if(sum[i]> max_sum){
            max_sum = sum[i];
        }
    }
    cout << max_sum;
    
    return 0;
}
