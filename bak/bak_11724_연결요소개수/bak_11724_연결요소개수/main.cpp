//
//  main.cpp
//  bak_11724_연결요소개수
//
//  Created by dizwe on 2020/06/03.
//  Copyright © 2020 dizwe. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>
#define MAX_SIZE 1000
using namespace std;
int N, M;
vector<int> graph[MAX_SIZE+2];
bool visited[MAX_SIZE+2];
queue<int> gr_q;
int connected_component_num = 0;
int main(int argc, const char * argv[]) {
    cin >> N >> M;
    
    int from, to;
    for(int i=1; i<=M; i++){
        cin>> from >> to;
        graph[from].emplace_back(to);
        graph[to].emplace_back(from); // !! 양쪽에 넣어줘야 한다!!!!!
    }
    
    fill(&visited[0], &visited[MAX_SIZE+2],false);
    while(true){
        bool visit_all = true;
        for(int i=1; i<=N; i++){
            if(visited[i]==false){
                visit_all = false;
                gr_q.push(i);
                visited[i] = true;
                break;
            }
        }
        if(visit_all==true) break;
        connected_component_num++;
        
        while(!gr_q.empty()){
            int from = gr_q.front();
            gr_q.pop();
            for(int to_i = 0; to_i< graph[from].size(); to_i++){
                if(visited[graph[from][to_i]]==false){
                    visited[graph[from][to_i]] = true; // visited 체크된건 넣지말자!
                    gr_q.push(graph[from][to_i]);
                }
            }
        }
    }
    
    cout << connected_component_num;
    return 0;
}

