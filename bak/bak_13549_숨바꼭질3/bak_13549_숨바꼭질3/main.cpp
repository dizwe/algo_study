//
//  main.cpp
//  bak_13549_숨바꼭질3
//
//  Created by dizwe on 2020/06/05.
//  Copyright © 2020 dizwe. All rights reserved.
//

#include <iostream>
#include <queue>
#include <vector>
#include <functional>
// !! 이것도 중요했고!!
#define MAX_SIZE 100000 + 1
using namespace std;

int A, B;
priority_queue<pair<int, int>, vector<pair <int, int > >, greater< pair < int, int > > > cord_que;
bool visits[MAX_SIZE+2];
bool check_pow_2(int n);

int main(int argc, const char * argv[]) {
    // insert code here...
    fill(&visits[0], &visits[MAX_SIZE+2],false);
    cin >> A >> B;
    cord_que.push(make_pair(0,A));
    visits[A] = true;
    
    while(!cord_que.empty()){
        pair<int, int> cur_pair = cord_que.top(); // !! 이떄는 top!
        int cur_time = cur_pair.first;
        int cur_cord = cur_pair.second;
        cord_que.pop();
        // !! visit을 할 떄 priority queue는 여기서 하는게 좋을듯
        // 아래 3개 if문에서 하면 3 ,5 가 1초에 있었을때
        // 5+1를 먼저 prirority que에 넣으면, 6은방문한거라
        // 3*2를 넣을 수 없는 문제가 생긴다.
        // Thanks asomeJay
        visits[cur_cord] = true;
        // 나중에 push되었더라도 priority가 같으면 그다음엔 좌표 큰순서대로정렬됨
        if(cur_cord == B){
            cout << cur_time;
            break;
        }

        // !! 범위안넘어가는지먼저!!
        if(cur_cord-1>=0&& !visits[cur_cord-1] ){ // 마이너스로 갈수는 없으니까
            cord_que.push(make_pair(cur_time+1, cur_cord-1));
        }
        if(cur_cord+1<MAX_SIZE && !visits[cur_cord+1]){ // ?? 범위 넘어가면 어떡해? 거긴 안가야
            cord_que.push(make_pair(cur_time+1, cur_cord+1));
        }
        if(cur_cord*2<MAX_SIZE && !visits[cur_cord*2]){
            cord_que.push(make_pair(cur_time, cur_cord*2));
        }
        
        
    }
    return 0;
}

// 바로 다이렉트로 나누어 떨어지고 2의 제곱수라면
//        if((B%cur_cord ==0)&&(check_pow_2(B/cur_cord)==true)){
//            cout << cord_time[cur_cord]; // 더이상 나갈 필요가 없다!
//            break;
//        }else{
            // 왼쪽이나 오른쪽으로 움직이기

bool check_pow_2(int n){
    // 2의 제곱수인지 확인
    // !! 비트 하나씩 빼내는거 확인
    int n_minus_1 = n-1;
    if(n==0) return false;
    if((n& n_minus_1) == 0){ // !! &가 precedence가 낮아서 괄호!
      return true;
    }else{
      return false;
    }
     
}
