//
//  main.cpp
//  bak_13023_ABCDE
//
//  Created by dizwe on 2020/05/30.
//  Copyright © 2020 dizwe. All rights reserved.
//

#include <iostream>
#include <vector>
#define MAX_SIZE 2000
using namespace std;

vector<int> friends_info[MAX_SIZE+1];
bool visit[MAX_SIZE+1];
int PERSON_NUM, REL_NUM;
int depth = 1;
bool find_ans = false;
void find_abcde(int);
int main(int argc, const char * argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    fill(&visit[0], &visit[MAX_SIZE+1],false);
    
    cin >> PERSON_NUM >> REL_NUM;
    
    int a, b;
    for(int i=0; i<REL_NUM; i++){
        cin >> a >> b;
        friends_info[a].emplace_back(b);
        friends_info[b].emplace_back(a);
    }
    
    // 시작점??
    for(int s = 0; s < PERSON_NUM; s++){
        if(find_ans==true){
            break;
        }
        visit[s] = true;
        find_abcde(s);
        visit[s] = false;
    }
    if(find_ans==true){
        cout << 1;
    }else{
        cout << 0;
    }
    return 0;
}

void find_abcde(int start){
    if(depth==5||find_ans==true){ // 찾았따!
        find_ans = true;
        return;
    }
    
    for(int i = 0; i < friends_info[start].size(); i++){
        int s = friends_info[start][i];
        if(visit[s]== false){ //  && friends_info[start][s]==true
            visit[s] = true;
            depth++;
            find_abcde(s);
            depth--;
            visit[s] = false;
        }
    }
}









