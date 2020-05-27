//
//  main.cpp
//  bak_15651_n과m_3
//
//  Created by dizwe on 2020/05/27.
//  Copyright © 2020 dizwe. All rights reserved.
//

#include <iostream>
#include <vector>
#define MAX_SIZE 7
using namespace std;
int N;
int M;
int num[MAX_SIZE+2];
vector <int> perm_vec;

void find_perm(int);

int main(int argc, const char * argv[]) {
    cin >> N;
    cin >> M;
    find_perm(0);
    return 0;
}

void find_perm(int cum_m){
    if(cum_m == M){
        for(int i=0; i<M; i++){
            cout << perm_vec[i] << " ";
        }
        cout << "\n";
        return;
    }
    for(int i =1 ;i<=N; i++){
        perm_vec.emplace_back(i);
        find_perm(cum_m+1);
        perm_vec.pop_back();
    }
}

