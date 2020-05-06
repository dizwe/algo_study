#include <iostream>
#include <queue>
#include <climits>
#define MAX_SIZE 10

using namespace std;
typedef struct bridge_poss {
    int from;
    int to;
    pair <int, int> from_cord;
    pair <int, int> to_cord;
    int len;
} bridge_poss;

int R, C;
int map[MAX_SIZE+2][MAX_SIZE+2];
queue <pair<int, int > > numbering_que;
queue <pair<int, int > > connect_ch_que;
vector<bridge_poss> bridge_pos_list;
vector<int> bridge_list;
vector<bool> bridge_visit;
short dir[4][2] = {{0,1},{1,0},{0,-1},{0,-1}};
int total_bridge_len = 0;
int min_bridge_len = INT_MAX;

void numbering();
void find_pos();
void find_min_len(int );
int main() {
    cin >> R >> C;
    for(int r=0; r<R; r++){
        for(int c=0; c<C; c++){
            cin >> map[r][c];
        }
    }
    
    numbering();
    
    for(int r=0; r<R; r++){
        for(int c=0; c<C; c++){
            cout << map[r][c] << " ";
        }
        cout << "\n";
    }
    
    find_pos();
    find_min_len(0);
    
    if(min_bridge_len==INT_MAX){
        cout << -1;
    }else{
        cout << min_bridge_len;
    }
    return 0;
}

bool inside_map(int row, int col){
    if(row >=0 && col >=0 && row < R&& col< C){
        return true;
    }
    return false;
}

void numbering(){
    int number = 'a'-1; // !! 1은 채워져 있으니까 a로 해보자.
    for(int r=0; r<R; r++){
        for(int c=0; c<C; c++){
            if(map[r][c]==1){// 연결을 시작해볼까?
                number++;
                bridge_list.emplace_back(number); // 나중에 모든 곳 방문해야 하니까!
                bridge_visit.emplace_back(false);;
                numbering_que.push(make_pair(r, c));
                while(!numbering_que.empty()){
                    pair <int, int> current_cord = numbering_que.front();
                    numbering_que.pop();
                    // 상하좌우 살펴보기
                    for(int i=0; i<4; i++){
                        int next_row = current_cord.first + dir[i][0];
                        int next_col = current_cord.second + dir[i][1];
                        if(inside_map(next_row, next_col) && map[next_row][next_col]==1){
                            map[next_row][next_col] = number;// 거기 번호 매기기
                            numbering_que.push(make_pair(next_row, next_col));
                        }
                    }
                }
            }
        }
    }
}


void find_pos(){
    bool bridge_start = false;
    int start_land = -1;
    pair<int, int> start_cord = make_pair(-1,-1);
    int end_land = -1;
    pair<int, int> end_cord = make_pair(-1,-1);
    int bridge_len = 0;
    // 가로로 파악하기
    for(int r=0; r<R; r++){
        for(int c=0; c<C; c++){
            if(c+1<C && map[r][c]!=0 && map[r][c+1]==0){ // 다리 시작
                // c+1 < C 제일 마지막 row의 경우 start를 할 필요도 없음
                bridge_start = true; // 다리가 시작해도 되는점이다!
                start_land = map[r][c]; // 시작하는 점
                start_cord = make_pair(r, c);
            }else if(bridge_start == true && map[r][c]==0 && map[r][c+1]!=0){ // 다리 끝
                bridge_len++; // 다리 하나 추가
                end_land = map[r][c+1];
                end_cord = make_pair(r, c+1);
                if(bridge_len>1){// 1보다 길이 길면 얘는 뻗어도 됨
                    bridge_pos_list.emplace_back(bridge_poss {
                        start_land, end_land, start_cord, end_cord, bridge_len
                    });
                }
                bridge_start = false;
                bridge_len = 0;
            }else if(bridge_start == true && map[r][c]==0 && map[r][c+1]==0){ // 다리다리
                bridge_len++;
            }
        }
        bridge_start = false;
        bridge_len = 0;
    }
    
    for(int c=0; c<C; c++){
        for(int r=0; r<R; r++){
            if(r+1<R && map[r][c]!=0 && map[r+1][c]==0){ // 다리 시작
                // c+1 < C 제일 마지막 row의 경우 start를 할 필요도 없음
                bridge_start = true; // 다리가 시작해도 되는점이다!
                start_land = map[r][c]; // 시작하는 점
                start_cord = make_pair(r, c);
            }else if(bridge_start == true && map[r][c]==0 && map[r+1][c]!=0){ // 다리 끝
                bridge_len++; // 다리 하나 추가
                end_land = map[r+1][c];
                end_cord = make_pair(r+1, c);
                if(bridge_len>1){// 1보다 길이 길면 얘는 뻗어도 됨
                    bridge_pos_list.emplace_back(bridge_poss {
                        start_land, end_land, start_cord, end_cord, bridge_len
                    });
                }
                bridge_start = false;
                bridge_len = 0;
            }else if(bridge_start == true && map[r][c]==0 && map[r+1][c]==0){ // 다리다리
                bridge_len++;
            }
        }
        bridge_start = false;
        bridge_len = 0;
    }
}

void find_min_len(int idx){
    //다 섬 다 연결했는지 확인(연결하면 그 이후는 안봐도 되니까)
    bool visit_all = true;
    
    // 이렇게 체크하면 안되겠다!!!
//    for(int i=0; i<bridge_list.size(); i++){
//        if(bridge_visit[i]==false){
//            visit_all = false;
//            break;
//        }
//    }
    // 일단 처음 queue에 집어넣기
    
    // 전체 방문 리스트
    while(!connect_ch_que.empty()){
        
    }
    
    if(visit_all ==true){
        if(total_bridge_len < min_bridge_len) min_bridge_len = total_bridge_len;
            cout << total_bridge_len << " ";
        return;
    }else if(idx >= bridge_pos_list.size()){ // 범위 넘어서면
        return;
    }
    // 일단 얘 방문해보기
    total_bridge_len += bridge_pos_list[idx].len; // 무조건 길이를 더할게 아니라 선택될 때더하는거지!(근데 굳이 그럴필요 없을 듯- 아닌 경우도 찾아지니까)

//    bool prev_visit_from = false;
//    bool prev_visit_to = false;
//    for(int i=0; i<bridge_list.size(); i++){
//        if(bridge_list[i]==bridge_pos_list[idx].from){
//            prev_visit_from = bridge_visit[i];
//            bridge_visit[i] = true;
//        }
//        if(bridge_list[i]==bridge_pos_list[idx].to){
//            prev_visit_to = bridge_visit[i];
//            bridge_visit[i] = true;
//        }
//    }
    
    if(bridge_pos_list[idx].from_cord.first==bridge_pos_list[idx].to_cord.first){ // 가로 방향
        int base_row = bridge_pos_list[idx].from_cord.first;
        int from_idx = bridge_pos_list[idx].from_cord.second;
        int to_idx = bridge_pos_list[idx].to_cord.second;
        for(int i = from_idx +1 ; i<to_idx;i++){ // 시작과 끝
            map[base_row][i] = 1; // 다리 그리기
        }
    } else if(bridge_pos_list[idx].from_cord.second==bridge_pos_list[idx].to_cord.second){ // 세로 방향
        int base_col = bridge_pos_list[idx].from_cord.second;
        int from_idx = bridge_pos_list[idx].from_cord.first;
        int to_idx = bridge_pos_list[idx].from_cord.first;
        for(int i = from_idx +1 ; i<to_idx;i++){ // 시작과 끝
            map[i][base_col] = 1; // 다리 그리기
        }
    }
    find_min_len(idx+1);
    
//    total_bridge_len -= bridge_pos_list[idx].len;
//    for(int i=0; i<bridge_list.size(); i++){
//        if(bridge_list[i]==bridge_pos_list[idx].from){
//            bridge_visit[i] = prev_visit_from; // 이미 연결된 애들을 또 다른 곳에서 연결하면 오류 나는 문제 있음
//        }
//        if(bridge_list[i]==bridge_pos_list[idx].to){
//            bridge_visit[i] = prev_visit_to;
//        }
//    }
    
    if(bridge_pos_list[idx].from_cord.first==bridge_pos_list[idx].to_cord.first){ // 가로 방향
        int base_row = bridge_pos_list[idx].from_cord.first;
        int from_idx = bridge_pos_list[idx].from_cord.second;
        int to_idx = bridge_pos_list[idx].to_cord.second;
        for(int i = from_idx +1 ; i<to_idx;i++){ // 시작과 끝
            map[base_row][i] = 0; // 다리 지우기
        }
    } else if(bridge_pos_list[idx].from_cord.second==bridge_pos_list[idx].to_cord.second){ // 세로 방향
        int base_col = bridge_pos_list[idx].from_cord.second;
        int from_idx = bridge_pos_list[idx].from_cord.first;
        int to_idx = bridge_pos_list[idx].from_cord.first;
        for(int i = from_idx +1 ; i<to_idx;i++){ // 시작과 끝
            map[i][base_col] = 0; // 다리 지우기
        }
    }
    find_min_len(idx+1);
    
}
