//
//  main.cpp
//  bak_11055_가장큰증가부분수열
//
//  Created by dizwe on 2020/05/19.
//  Copyright © 2020 dizwe. All rights reserved.
//

#include <iostream>
#define MAX_SIZE 1000
using namespace std;

int N;
int num_list[MAX_SIZE+2];
int sum_info[MAX_SIZE+2];

int main(int argc, const char * argv[]) {
    // insert code here...
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> N;
    fill(&sum_info[0],&sum_info[N+2],0);
    for(int i=0; i<N ; i++)
        cin >> num_list[i];
    
    sum_info[0] = num_list[0];
    int max_result = num_list[0]; // 나만 골랐을 때
    
    for(int i=0; i<N ; i++){
        bool find_smaller = false;
        for(int j=0; j<i; j++){
            // 이전거랑 나를 더한거랑 비교해서 제일 최대값을 찾아줘!!
            if(num_list[i]> num_list[j]){
                sum_info[i] = max(sum_info[j]+num_list[i], sum_info[i]);
                find_smaller = true;
            }
        }
        // !!조건이 들어있으면 빠진 if문 있는지 그게 정말 필요 없는지 확인해보기!!
        if(find_smaller==false) sum_info[i] = num_list[i];
        if(sum_info[i]>max_result) max_result = sum_info[i];
    }
    
    cout << max_result;
    
    return 0;
}
