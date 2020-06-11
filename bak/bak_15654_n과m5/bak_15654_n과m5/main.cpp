//
//  main.cpp
//  bak_15654_n과m5
//
//  Created by dizwe on 2020/06/11.
//  Copyright © 2020 dizwe. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
#define MAX_INT 8
using namespace std;
int A[MAX_INT + 2];
int visit[MAX_INT + 2];
int N, M;
vector<int> num_list;
void nm(int depth);

int main(int argc, const char * argv[]) {
    cin >> N >> M;
    
    for(int i=0; i<N; i++)
        cin >> A[i];
    sort(&A[0], &A[N]);
    nm(1);
    return 0;
}


void nm(int depth){
    if(depth>M){
        for(int i=0; i<M; i++){
            cout << num_list[i] << " ";
        }
        cout << "\n";
        return;
    }
        
    for(int i=0; i<N; i++){
        if(visit[i]==false){
            visit[i] = true;
            num_list.emplace_back(A[i]);
            nm(depth+1);
            num_list.pop_back();
            visit[i] = false;
        }
    }
}
