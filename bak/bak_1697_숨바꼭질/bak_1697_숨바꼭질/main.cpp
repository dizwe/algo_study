#include <iostream>
#include <queue>
#define MAX_SIZE 100000
using namespace std;

int A, B;
int time_info[MAX_SIZE+2]; // !! initialize
// !! 다시 방문할 필요가 없다는 것
queue<int > cord_que;

void find_min_time();
int current_time = 0;
int main() {
    cin >> A >> B;
    fill(&time_info[0],&time_info[MAX_SIZE+2],-1);
    time_info[A] = 0; // 첫 시작점이니까
    find_min_time();
   
    return 0;
}

bool inside_map(int cord){
    if(cord>=0 && cord<=100000){
        return true;
    }else{
        return false;
    }
}

void find_min_time(){
    // 일단 que 출발점 넣기
    cord_que.push(A);
    
    while(!cord_que.empty()){
        // que 뽑기
        int current_cord =cord_que.front();
        cord_que.pop();
        
        if(current_cord==B){
            cout << time_info[current_cord];
            return;
        }
        
        // 3가지 방식으로 이동하로 queue에 넣기
        if(inside_map(current_cord-1) && time_info[current_cord-1]==-1){ // 왼쪽
            cord_que.push(current_cord-1);
            time_info[current_cord-1] = time_info[current_cord] +1;
        }
        if(inside_map(current_cord+1) && time_info[current_cord+1]==-1){ // 오른쪽
            cord_que.push(current_cord+1);
            time_info[current_cord+1] = time_info[current_cord] +1;
        }
        if(inside_map(current_cord*2) &&  time_info[current_cord*2]==-1){ // 점프
            cord_que.push(current_cord*2);
            time_info[current_cord*2] = time_info[current_cord] +1;
        }
        
    }
}
