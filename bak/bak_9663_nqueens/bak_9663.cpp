#include <iostream>
// 여기에 ; 붙이지마!!
#define CANNOT_ATTACK false
#define CAN_ATTACK true
#define DIRECTION_NUM true
using namespace std;

int N;
int cannot_attack_num = 0;

bool inside_map(int r, int c){
    return r<N && c< N && r>=0 && c >=0;
}

bool attack_check(int** board,int queen_row, int check_col){
    // 지금 추가된 애만 체크하면 됨 그 앞에 애는 이미 걔들끼리는 피해있음.
    // 가로
    for(int c =0; c<N; c++){
        if(c!=check_col && board[queen_row][c] ==1)
            return CAN_ATTACK;
    }
    // 세로 
    for(int r =0; r<N; r++){
        if(r!=queen_row && board[r][check_col] ==1)
            return CAN_ATTACK;
    }
    int direction_info[4][2] = {{-1,-1},{1,1},{1,-1},{-1,1}};
    // 왼쪽위로 가는 대각선
    for(int direction = 0; direction<4; direction++){
        for(int step =0; step<N; step++){
            int test_row = queen_row + direction_info[direction][0]*step;
            int test_col = check_col + direction_info[direction][1]*step; 
            if(inside_map(test_row, test_col)==false) break; // 지도 밖 벗어나면 끝!
            if(test_row!=queen_row && test_col!=check_col && board[test_row][test_col] ==1)
                return CAN_ATTACK;
        }
    }

    return CANNOT_ATTACK;
}

void dfs_find(int current_col, int queen_row,int** board){
    // 제일 마지막 종료 조건
    if(current_col == N && attack_check(board, queen_row, current_col-1)==CANNOT_ATTACK){
        cannot_attack_num++;
        return;
    }else if(current_col == N){
        return;
    }

    if(attack_check(board,queen_row, current_col-1)==CANNOT_ATTACK){ // 이전걸 빼야지 지금까지 추가된 애 체크가능하다.
        // cout << current_col << " ";
        for(int r=0; r < N; r++){
            board[r][current_col] = 1; // 일단 말한 자리에 퀸 두기
            dfs_find(current_col+1, r, board);
            board[r][current_col] = 0; // 일단 말한 자리에 퀸 빼기
        }
    }else{
        return;
    }
}

int main(){
    cin >> N;
    int** board = new int*[N];
    for(int i=0; i<N; i++) board[i] = new int[N];
    fill(&board[0][0], &board[N-1][N], 0);// 0으로 채워넣기

    // board[r][0] = 1; // 일단 말한 자리에 퀸 두기
    
    for(int r=0; r < N; r++){
        board[r][0] = 1; // 일단 말한 자리에 퀸 두기
        dfs_find(0+1, r, board);    
        board[r][0] = 0; // 일단 말한 자리에 퀸 빼기
    }
    cout << cannot_attack_num;
    return 0;
}