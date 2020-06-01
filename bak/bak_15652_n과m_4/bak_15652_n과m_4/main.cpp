//
//  main.cpp
//  bak_15652_n과m_4
//
//  Created by dizwe on 2020/06/01.
//  Copyright © 2020 dizwe. All rights reserved.
//

#include <iostream>
#define MAX_SIZE 8
using namespace std;

int N, M;
int m_list[MAX_SIZE+1];

void find_nm(int);
int main(int argc, const char * argv[]) {
    cin >> N >> M;
    
    find_nm(1);
    return 0;
}

void find_nm(int depth){
    if(depth==M+1){
        for(int i=1; i<=M; i++)
            cout << m_list[i] << " ";
        cout << "\n";
        return;
    }
    int start_point = 1;
    if(depth-1>0){
        start_point = m_list[depth-1];
    }
    for(int i=start_point; i<=N; i++){
        m_list[depth] = i;
        find_nm(depth+1);
    }
}
