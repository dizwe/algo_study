
#include <stdio.h>
#include <stdlib.h>
#define MAX_N 50
#define MAX_M 50
int visited[MAX_N][MAX_M];
int check[MAX_N][MAX_M];
int N,M;int dfs(int ** whole_map,int row, int col, int time, int prev_row, int prev_col){
    int total = 1;     if(time<=1){
            visited[row][col] = 0;
            check[row][col]=1;
            return total;
    }else{
        int tunnel_type = whole_map[row][col];
        
            visited[row][col] = 1;
            check[row][col]=1;
            int next_tunnel_type;
                        if(tunnel_type == 1 || tunnel_type == 2 || tunnel_type == 4 || tunnel_type == 7){
                                                                if(row-1>=0&&visited[row-1][col]==0){                    next_tunnel_type = whole_map[row-1][col];
                    if(next_tunnel_type == 1 || next_tunnel_type == 2 || next_tunnel_type == 5 || next_tunnel_type == 6)
                        total+=dfs(whole_map, row-1, col, time-1,row, col);
                }
            }
            if(tunnel_type ==1||tunnel_type ==3||tunnel_type ==4||tunnel_type ==5){
                                if(col+1<M&&visited[row][col+1]==0){                    next_tunnel_type = whole_map[row][col+1];
                    if(next_tunnel_type == 1 || next_tunnel_type == 3 || next_tunnel_type == 6 || next_tunnel_type == 7)
                        total+=dfs(whole_map, row, col+1, time-1,row, col);
                }
                
            }
            if(tunnel_type ==1||tunnel_type ==2||tunnel_type ==5||tunnel_type ==6){
                                if(row+1<N&&visited[row+1][col]==0){                    next_tunnel_type = whole_map[row+1][col];
                    if(next_tunnel_type == 1 || next_tunnel_type == 2 || next_tunnel_type == 4 || next_tunnel_type == 7)
                        total+=dfs(whole_map, row+1, col, time-1,row, col);
                }
            }
            if(tunnel_type ==1||tunnel_type ==3||tunnel_type ==6||tunnel_type ==7){
                                if(col-1>=0&&visited[row][col-1]==0){                    next_tunnel_type = whole_map[row][col-1];
                    if(next_tunnel_type == 1 || next_tunnel_type == 3 || next_tunnel_type == 4 || next_tunnel_type == 5)
                        total+=dfs(whole_map, row, col-1, time-1,row, col);
                }
              
            }
                                    visited[row][col] = 0;
            return total;
    }
}

void one_test_case(){
    int  R, C, L;     scanf("%d %d %d %d %d", &N, &M, &R, &C, &L);
        int **whole_map;
    whole_map = (int**) malloc ( sizeof(int*) * N );
    
    for(int i=0; i<N; i++){
        whole_map[i] = (int*) malloc ( sizeof(int) * M );
    }
    
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            scanf("%d",&whole_map[i][j]);
            visited[i][j]=0;
            check[i][j]=0;
        }
    }
    int result = dfs(whole_map,R,C,L,-1, -1);
    int check_num=0;
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            if(check[i][j]==1)
               check_num++;
        }
    }
    
    printf(" %d\n",check_num);
}

int main(){
    int T;     scanf("%d", &T);    for(int i=0;i<T;i++){
        printf("#%d",i+1);
        one_test_case();
    }
    return 0;
}

