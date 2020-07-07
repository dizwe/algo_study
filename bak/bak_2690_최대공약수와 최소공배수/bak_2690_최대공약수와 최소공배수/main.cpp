//
//  main.cpp
//  bak_2690_최대공약수와 최소공배수
//
//  Created by dizwe on 2020/06/11.
//  Copyright © 2020 dizwe. All rights reserved.
//

#include <iostream>
#include <vector>
#define MAX_SIZE 10000

using namespace std;
bool prime_list[MAX_SIZE+2];
int two_num[2];
vector<int> portion_list;


void find_prime(){
    prime_list[2] = true;
    for(int i=3; i<=MAX_SIZE; i++){
        int divided = false;
        for(int j = 2; j<i; j++){
            if(prime_list[j] == true && i % j == 0){
                divided = true;
            }
        }
        if(divided==false){
            prime_list[i] = true;
        }
            
    }
}

int main(int argc, const char * argv[]) {
    fill(&prime_list[0], &prime_list[MAX_SIZE + 2], false);
    find_prime(); // 소수 찾기
    
    cin >> two_num[0] >> two_num[1];
    bool divided = true;
    while(divided){
        divided = false; // 나눠지면 나중에 true로 바뀜
        int min_end = max(two_num[0], two_num[1]); // !! min으로 해야된다! (max로 하면 %2)
        for(int i=2; i<=min_end; i++){ // 나 자신은 안써야 함
            if(prime_list[i]==true){
                if((two_num[0] % i)==0 && (two_num[1] % i)==0){
                    portion_list.emplace_back(i);
                    two_num[0] = two_num[0] / i;
                    two_num[1] = two_num[1] / i;
                    divided = true;
                    break;
                }
            }
        }
    }
    
    
    // 최대공약수
    int max_div = 1;
    for(int i=0; i<portion_list.size(); i++){
        max_div *= portion_list[i];
    }
    cout << max_div << "\n";
    // 최소공배수1
//    cout << two_num[0]  << two_num[1];
    if(two_num[0] != two_num[1])
        cout << max_div * two_num[0] *two_num[1];
    else // 값이 같으면
        cout << max_div * two_num[0];
    
    return 0;
}
