#include <iostream>
#include <cmath>
// 여기에 ; 붙이지마!!
#define CANNOT_ATTACK false
#define CAN_ATTACK true
#define DIRECTION_NUM true
#define NOT_EXIST_NUM -42
using namespace std;

int N;
int cannot_attack_num = 0;

bool attack_check_prev(int* board, int until_col){
    // 모두다 0일때에는 처리되면 안되는데...
    for(int c1=0; c1<until_col-1; c1++){
        for(int c2=c1+1; c2<until_col; c2++){ // c1이 체크했으면 그 이후거 체크하면 되지
            if(board[c1]==board[c2] || abs(board[c1]-board[c2]) == abs(c1-c2))
                return CAN_ATTACK;
        }    
    }
    return CANNOT_ATTACK;
}

bool attack_check(int* board, int until_col){
    // 한개 더 추가된 상태로 확인되니까 -1
    int current_col = until_col-1;
    // 모두다 0일때에는 처리되면 안되는데...
    for(int c=0; c<current_col; c++){ 
        if(board[current_col]==board[c] || abs(board[current_col]-board[c]) == abs(current_col-c))
            return CAN_ATTACK;
    }
    return CANNOT_ATTACK;
}

void dfs_find(int current_col, int* board){
    // for(int r=0; r < N; r++) cout<< board[r] << " ";
    // cout << "\n";
    if(current_col == N && attack_check(board,current_col)==CANNOT_ATTACK){
        cannot_attack_num++;
        return;
    }    

    if(attack_check(board,current_col)==CANNOT_ATTACK){
        for(int r=0; r < N; r++){
            board[current_col] = r; // 일단 말한 자리에 퀸 두기
            dfs_find(current_col+1, board);    
            board[current_col] = 0; // 일단 말한 자리에 퀸 빼기
        }
    }
    return;
}

int main(){
    cin >> N;
    int* board = new int[N];
    fill(&board[0], &board[N], NOT_EXIST_NUM);// 0으로 채워넣기

    for(int r=0; r < N; r++){
        board[0] = r; // 일단 말한 자리에 퀸 두기
        dfs_find(1, board);    
        board[0] = 0; // 일단 말한 자리에 퀸 빼기
    }
    cout << cannot_attack_num;
    return 0;
}