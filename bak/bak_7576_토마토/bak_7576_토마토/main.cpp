#include <iostream>
#include <queue>
#define MAX_SIZE 1000
using namespace std;
int ROW, COL;
int green_tomato_total = 0; //총 안익은 토마토 개수
int get_riped_tomato_total = 0;
int tomato_box[MAX_SIZE+2][MAX_SIZE+2];
bool tomato_box_visited[MAX_SIZE+2][MAX_SIZE+2];

int dir_info[4][2]  = {{0,1}, {1,0}, {0,-1}, {-1,0}};
void find_min_period();
bool inside_box(int r, int c);
typedef struct que_info{
    pair <int, int> cord;
    int depth;
} que_info;
queue<struct que_info> tom_que;
int main() {
    cin >> COL >> ROW;
    fill(&tomato_box_visited[0][0], &tomato_box_visited[MAX_SIZE+1][MAX_SIZE+2],false);
    for(int r =0 ; r<ROW; r++){
        for(int c=0; c<COL; c++){
            cin >> tomato_box[r][c];
            if(tomato_box[r][c] == 0) green_tomato_total++;
            else if(tomato_box[r][c] == 1){
                tomato_box_visited[r][c] = true;
                tom_que.push(que_info{make_pair(r,c), 0}); // 시작점이 여러개 동신일때~
            }
        }
    }
    
//    if(green_tomato_total == 0) cout << 0;
    find_min_period();
    return 0;
}

bool inside_box(int r, int c){
    if(r<ROW && r>= 0 && c<COL && c>=0){
        return true;
    }
    else return false;
}

void find_min_period(){
    int depth = 0;
    while(!tom_que.empty()){
        que_info que_front = tom_que.front();
        pair<int, int> front_elem = que_front.cord;
        depth = que_front.depth;
        int cur_row = front_elem.first;
        int cur_col = front_elem.second;
        tom_que.pop();
        
        // elased_time++; // 하루 지남!! depth를 계산하는게 아님
        // 동서남북 다니기
        for(int dir=0; dir<4; dir++){
            int next_row = cur_row + dir_info[dir][0];
            int next_col = cur_col + dir_info[dir][1];
            if(inside_box(next_row, next_col)&&tomato_box_visited[next_row][next_col]==false){
                tomato_box_visited[next_row][next_col] = true;
                if(tomato_box[next_row][next_col]==0){
                    get_riped_tomato_total++;
                    tom_que.push(que_info{make_pair(next_row, next_col), depth+1}); // depth를 높이기
                }
            }
        }
        
    }
    
    if(get_riped_tomato_total==green_tomato_total) cout << depth;
    else cout << -1;
}
