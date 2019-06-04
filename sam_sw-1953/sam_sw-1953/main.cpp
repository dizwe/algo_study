//
//  main.cpp
//  sam_sw-1953
//
//  Created by dizwe on 04/06/2019.
//  Copyright © 2019 dizwe. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#define MAX_N 50
#define MAX_M 50
int visited[MAX_N][MAX_M];
int N,M;// dfs의 파라미터로 주고받고 하는데 그러기에는 코드만 복잡해지는것 같기에 global로
// visited를 parameter로 써도 상관없을까? -> 여러개로 갈라졌을 때 길이 겹쳐도 다른 길로 인식 함.(이 문제에서는 찾아야 하는 길을 물어보는게 아니라 범위이다.)
int dfs(int ** whole_map,int row, int col, int time, int prev_row, int prev_col){
    int total = 1; // 일단 나는 방문한거니까 1부터 시작
    if(time<=1){
//        if(visited[row][col]==0){
            visited[row][col] = 1;
            return total;
//        }else{
//            return 0;
//        }
    }else{
        int tunnel_type = whole_map[row][col];
//        !!! visited 되었는지 안되었는지는 방문하기 전에 체크하자
//        if(visited[row][col]==0){
        
            visited[row][col] = 1;
            int next_tunnel_type;
            // !!!! if else if 를 하면 다른건 돌아가지도 않는다!!!!!!!!
            if(tunnel_type == 1 || tunnel_type == 2 || tunnel_type == 4 || tunnel_type == 7){
                // 북 만약에 위쪽에 데이터가 있다면!
                // !!!가는 방향이 가 갈 수 있는지(내려갔는데 파이프가 연결이 안되어있는지)도 체크해야지!!
                // prev_row!=row-1&&prev_col!=col 로 하면 안되나??
                if(row-1>=0&&visited[row-1][col]==0){//&&!(prev_row==row-1&&prev_col==col)){
                    next_tunnel_type = whole_map[row-1][col];
                    if(next_tunnel_type == 1 || next_tunnel_type == 2 || next_tunnel_type == 5 || next_tunnel_type == 6)
                        total+=dfs(whole_map, row-1, col, time-1,row, col);
                }
            }
            if(tunnel_type ==1||tunnel_type ==3||tunnel_type ==4||tunnel_type ==5){
                // 동 만약에 동쪽에 데이터가 있다면
                if(col+1<M&&visited[row][col+1]==0){//&&!(prev_row==row&&prev_col==col+1)){
                    next_tunnel_type = whole_map[row][col+1];
                    if(next_tunnel_type == 1 || next_tunnel_type == 3 || next_tunnel_type == 6 || next_tunnel_type == 7)
                        total+=dfs(whole_map, row, col+1, time-1,row, col);
                }
                
            }
            if(tunnel_type ==1||tunnel_type ==2||tunnel_type ==5||tunnel_type ==6){
                // 남
                if(row+1<N&&visited[row+1][col]==0){//&&!(prev_row==row+1&&prev_col==col)){
                    next_tunnel_type = whole_map[row+1][col];
                    if(next_tunnel_type == 1 || next_tunnel_type == 2 || next_tunnel_type == 4 || next_tunnel_type == 7)
                        total+=dfs(whole_map, row+1, col, time-1,row, col);
                }
            }
            if(tunnel_type ==1||tunnel_type ==3||tunnel_type ==6||tunnel_type ==7){
                // 서
                if(col-1>=0&&visited[row][col-1]==0){//&&!(prev_row==row&&prev_col==col-1)){
                    next_tunnel_type = whole_map[row][col-1];
                    if(next_tunnel_type == 1 || next_tunnel_type == 3 || next_tunnel_type == 4 || next_tunnel_type == 5)
                        total+=dfs(whole_map, row, col-1, time-1,row, col);
                }
              
            }
            // !!! 중복 방문을 허용해야 최소거리를 찾을수 있음-> 노트 보기(근데 그러면 개수자체가 틀린데?)
            // !!! dfs로 푸시는 분들은 중복방문은 허용하되 방금전에 왔던 곳으로 돌아가는 것만 방지해주시면 통과할 수 있어
//            visited[row][col] = 0;
            return total;
//        }else{
//            return 0; // 방문했던 곳이니까 그냥 체크 안해도 됨.
//        }
    }
}

void one_test_case(){
    int  R, C, L; // 세로, 가로, 맨세, 멘가, 시간
    scanf("%d %d %d %d %d", &N, &M, &R, &C, &L);// Test Case

    //!! 원래라면 그냥 max 크기만큼 넉넉하게 받는게 더 좋음(이미 크기 지정해줬으니까)
    int **whole_map;
    whole_map = (int**) malloc ( sizeof(int*) * N );
    
    for(int i=0; i<N; i++){
        whole_map[i] = (int*) malloc ( sizeof(int) * M );
    }
    
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            scanf("%d",&whole_map[i][j]);
            visited[i][j]=0;
        }
    }
    int result = dfs(whole_map,R,C,L,-1, -1);
    printf(" %d\n",result);
}

int main(){
    int T; // 테스트 수,
    scanf("%d", &T);// Test Case
    for(int i=0;i<T;i++){
        printf("#%d",i+1);
        one_test_case();
    }
    return 0;
}

//1
//10 10 4 3 9
//0 0 0 0 0 0 0 0 0 0
//0 0 0 7 5 0 5 0 0 0
//0 0 3 2 2 6 0 0 0 0
//0 4 7 2 2 2 7 0 0 4
//0 3 0 1 1 2 2 0 0 5
//0 5 6 1 1 1 1 6 2 5
//7 4 1 2 0 0 4 6 0 0
//5 3 1 7 0 2 2 6 5 7
//7 3 2 1 1 7 1 0 2 7
//3 4 0 0 4 0 5 1 0 1
