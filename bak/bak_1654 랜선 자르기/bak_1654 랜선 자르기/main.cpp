//
//  main.cpp
//  bak_1654 랜선 자르기
//
//  Created by dizwe on 2020/06/09.
//  Copyright © 2020 dizwe. All rights reserved.
//

#include <iostream>
#define MAX_SIZE 1000000
int K, N;
int lan_info[MAX_SIZE+2];
using namespace std;

int get_lan_num(long long len){
    int num = 0;
    for(int i=0; i< K; i++){
        num += lan_info[i]/len; // 나누면 몇개 나오는지 체크
    }
    return num;
}

int main(int argc, const char * argv[]) {
    cin >> K >> N;
    // !! int k = (2 + 2147483647)/2; overflow 생김!!
    long long right = 1; // index랑 별개임!
    long long left = 1;
    for(int i=0; i<K; i++){
        cin >> lan_info[i];
        if(lan_info[i] > right){
            right = lan_info[i];
        }
    }
    
    long long mid;
    long long result = 1;
    while(left <= right){ // !! =도 붙어야 함(같은것도 체크해야 하니까!
        mid =  (left + right)/2;
        int lan_num = get_lan_num(mid);
        
        // 처음에 == N일때만 result를 바꾸려고 했다.
        // 1 10
        // 99 일때
        // 11개가 나누어 떨어지는데, 그게 최대값일때도 있음!
        if(lan_num >= N){ // 찾았다고 끝내면 안된다!! 더 큰게 있을 수 있다.
            if(mid>result)
                result = mid;
            left = mid + 1;
        }else{
            right = mid - 1;
        }
    }
    cout << result;
    
    return 0;
}
