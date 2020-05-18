//
//  main.cpp
//  bak_14002_가장긴증가하는부분수열4
//
//  Created by dizwe on 2020/05/18.
//  Copyright © 2020 dizwe. All rights reserved.
//

#include <iostream>
#define MAX_SIZE 1000
using namespace std;


int N;
int row[MAX_SIZE+2];
int dp[MAX_SIZE+2];
int prev_idx[MAX_SIZE+2];
int shortest_way[MAX_SIZE+2];

int main(int argc, const char * argv[]) {
    
    cin >> N;
    
    for(int i=0; i<N; i++){
        cin >> row[i];
    }
    
    dp[0] = 1;
    prev_idx[0] = -1; // this is start
    
    for(int i=1;i<N; i++){
        int len = 1; // 나는 포함이 되니까?
        for(int j=0;j<i;j++){
            if(row[i]> row[j]){
                if(dp[j] + 1 > len){
                    len = dp[j] + 1; // 그 이전에서 더 가는거!
                    prev_idx[i] = j;
                }
            }
        }
        
        if(len ==1){
            dp[i] = 1;
            prev_idx[i] = -1;
        }else{
            dp[i] = len;
        }
    }
    
    // lower bound를 쓰기도 하네..
    // !! prev 하면 거꾸로 되니까 거꾸로 적을것도 생각해야 한다..
    cout << dp[N-1] << "\n";
    int k = N-1;
    int i = dp[N-1]-1; // 지금 들어갈 개수
    while(prev_idx[k] !=-1){
        shortest_way[i--]= row[k];
        k = prev_idx[k];
    }
    shortest_way[0] = row[k];
    
    for(int i=0 ; i<dp[N-1] ;i++){
        cout << shortest_way[i] << " ";
    }
    
    return 0;
}
