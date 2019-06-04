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
int dfs(int ** whole_map,int row, int col, int time){
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
                if(row-1>=0&&visited[row-1][col]==0){
                    next_tunnel_type = whole_map[row-1][col];
                    if(next_tunnel_type == 1 || next_tunnel_type == 2 || next_tunnel_type == 5 || next_tunnel_type == 6)
                        total+=dfs(whole_map, row-1, col, time-1);
                }
            }
            if(tunnel_type ==1||tunnel_type ==3||tunnel_type ==4||tunnel_type ==5){
                // 동 만약에 동쪽에 데이터가 있다면
                if(col+1<M&&visited[row][col+1]==0){
                    next_tunnel_type = whole_map[row][col+1];
                    if(next_tunnel_type == 1 || next_tunnel_type == 3 || next_tunnel_type == 6 || next_tunnel_type == 7)
                        total+=dfs(whole_map, row, col+1, time-1);
                }
                
            }
            if(tunnel_type ==1||tunnel_type ==2||tunnel_type ==5||tunnel_type ==6){
                // 남
                if(row+1<N&&visited[row+1][col]==0){
                    next_tunnel_type = whole_map[row+1][col];
                    if(next_tunnel_type == 1 || next_tunnel_type == 2 || next_tunnel_type == 4 || next_tunnel_type == 7)
                        total+=dfs(whole_map, row+1, col, time-1);
                }
            }
            if(tunnel_type ==1||tunnel_type ==3||tunnel_type ==6||tunnel_type ==7){
                // 서
                if(col-1>=0&&visited[row][col-1]==0){
                    next_tunnel_type = whole_map[row][col-1];
                    if(next_tunnel_type == 1 || next_tunnel_type == 3 || next_tunnel_type == 4 || next_tunnel_type == 5)
                        total+=dfs(whole_map, row, col-1, time-1);
                }
              
            }
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
    int result = dfs(whole_map,R,C,L);
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
//20 20 13 11 13
//0 0 0 1 4 4 4 0 0 0 0 0 0 0 0 1 2 3 1 0
//0 0 0 0 0 0 0 0 0 0 0 4 2 7 7 2 0 1 1 0
//0 0 0 0 0 0 0 0 0 6 2 4 4 2 0 4 7 0 6 0
//0 0 0 7 5 5 3 0 0 7 5 0 5 6 4 2 6 3 1 5
//0 0 0 1 2 6 3 3 7 0 3 6 2 4 5 6 7 7 5 7
//0 0 0 3 7 6 1 5 3 3 4 5 7 6 0 4 3 3 1 1
//0 1 2 1 5 6 1 6 1 6 5 1 6 0 0 3 4 1 7 6
//0 2 3 2 2 7 3 0 0 3 2 5 2 1 0 6 5 1 6 5
//0 2 5 7 0 7 1 3 3 4 1 3 3 0 2 3 3 2 4 1
//4 0 0 7 2 4 2 2 1 3 1 6 5 5 6 2 5 1 1 6
//5 6 4 0 3 6 5 2 2 6 1 2 0 1 7 5 7 2 2 2
//1 6 3 1 4 4 1 0 3 0 4 2 7 2 0 2 3 6 2 5
//1 5 7 2 1 1 4 4 2 1 0 2 7 1 6 2 6 6 2 2
//3 7 0 6 5 0 4 0 6 6 7 1 3 1 1 1 5 1 6 6
//0 4 0 1 6 2 1 0 7 0 4 2 5 2 7 0 2 7 1 6
//0 7 3 0 1 7 6 2 0 0 4 2 4 1 3 3 7 0 1 3
//0 1 1 4 3 7 4 5 2 2 4 7 4 7 7 4 6 0 1 6
//0 5 2 2 1 4 6 3 7 0 6 3 5 0 0 6 4 4 2 1
//0 1 2 4 5 6 0 2 0 0 5 6 2 4 6 4 7 6 3 7
//7 7 4 2 3 0 0 4 0 0 7 2 7 5 6 1 4 5 5 4
