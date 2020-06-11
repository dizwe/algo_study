//
//  main.cpp
//  bak_2690_최대공약수와 최소공배수
//
//  Created by dizwe on 2020/06/11.
//  Copyright © 2020 dizwe. All rights reserved.
//

#include <iostream>
#define MAX_SIZE 1000
bool prime_list[MAX_SIZE+2];
using namespace std;
int N;
int num_list[100+1];
void find_prime(){
    prime_list[2] = true;
    for(int i=3; i<=MAX_SIZE; i++){
        int divided = false;
        for(int j = 2; j<i; j++){
            if(prime_list[j] == true && i % j == 0){
                divided = true;
            }
        }
        if(divided==false)
            prime_list[i] = true;
    }
}

int main(int argc, const char * argv[]) {
    fill(&prime_list[0], &prime_list[MAX_SIZE + 2], false);
    find_prime(); // 소수 찾기
    
    cin >> N;
    
    for(int i=0; i<N; i++)
        cin >> num_list[i];
    
    int num = 0;
    for(int i=0; i<N; i++){
        if(prime_list[num_list[i]]==true){
            num++;
        }
    }
    cout << num;
    return 0;
}
