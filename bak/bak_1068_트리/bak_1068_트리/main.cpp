//
//  main.cpp
//  bak_1068_트리
//
//  Created by dizwe on 2020/05/27.
//  Copyright © 2020 dizwe. All rights reserved.
//
#include <iostream>
#include <stack>
#define MAX_SIZE 50
#define EMPTY -99
using namespace std;
int N;
int parent_info[MAX_SIZE+2];
int is_leaf[MAX_SIZE+2];
int DELETE_NODE;
stack <int> parent_stack;

int main(int argc, const char * argv[]) {
    cin >> N;
    for (int i=0; i<N; i++){
        cin >> parent_info[i];
    }
    cin >> DELETE_NODE;
    fill(&is_leaf[0], &is_leaf[MAX_SIZE+2], true);
    parent_stack.push(DELETE_NODE);
    parent_info[DELETE_NODE]=EMPTY;
    is_leaf[DELETE_NODE] = false;
    while(!parent_stack.empty()){
        int parent_idx = parent_stack.top();
        parent_stack.pop();
        for(int i=0; i<N; i++){
            if(parent_info[i]==parent_idx){
                parent_stack.push(i);
                parent_info[i]=EMPTY;
                is_leaf[i] = false;
            }
        }
    }
    
    for(int i=0; i<N; i++){
        if(parent_info[i]!=EMPTY&&parent_info[i]!=-1){
            is_leaf[parent_info[i]] = false; // 넌 이제 부모야!
        }
    }
    
    int result =0;
    for (int i=0; i<N; i++){
        if(is_leaf[i]==true){
            result++;
        }
    }
    cout << result;
        
    
    return 0;
}
