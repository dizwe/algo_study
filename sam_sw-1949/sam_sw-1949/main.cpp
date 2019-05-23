//
//  main.cpp
//  sam_sw-1949
//
//  Created by dizwe on 22/05/2019.
//  Copyright © 2019 dizwe. All rights reserved.
//

#include <stdio.h>
#define MAX_MAP_WIDTH 8
int N; // 지도 한 변의 길이
int K; // 최대 공사 가능 깊이
int map[MAX_MAP_WIDTH][MAX_MAP_WIDTH];
int visited[MAX_MAP_WIDTH][MAX_MAP_WIDTH];
int four_side[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};


int InputData(){
    // 읽으면서 max 높이도 같이 찾음
    int r, c, maxh = 0;
    scanf("%d %d", &N, &K);
    for(r=0;r<N;r++){
    for(c=0;c<N;c++){
        scanf("%d", &map[r][c]);
        if(maxh < map[r][c]) maxh = map[r][c];
    }
    }
    return maxh;
}


int dfs(int row, int col, int current_height, int digged){
    // visited도 꼭 해줘야 한다!
    int max_length = 1;
    int current_length = 0;
    
    // visit은 지금 있는 노드잖아
    visited[row][col] = 1;
    for(int i =0; i<4; i++){// start 좌표에서 상하좌우 살피기
        // 시계방향 북쪽부터 좌표 북동남서
        int moved_row = row + four_side[i][0];
        int moved_col = col + four_side[i][1];
        if(moved_row<0||moved_row>=N||moved_col<0||moved_col>=N){
            // 범위넘은건 체크할 가치도 없다.
            continue;
        }else{
            // 내려갈 수 있는 애인지 체크하기
            if(map[moved_row][moved_col]<current_height&&visited[moved_row][moved_col]==0){
                // 동서남북 비교해서 max_length 리턴하기, digged도 이전에 받았던거 받아야 함
                current_length = 1 + dfs(moved_row, moved_col, map[moved_row][moved_col], digged);
                // 길면 return할 max_length 값 바꾸기
                if(current_length>max_length){
                    max_length = current_length;
                }
            }else if(map[moved_row][moved_col]-current_height<=K&&digged==0&&visited[moved_row][moved_col]==0){
                // !!!지금 더 높은데 더 낮은 경우로 계산했다.(current_height-map[moved_row][moved_col]<=K)
                // 최대 가능 공사 길이만큼  판적도 없다면,
                // 굳이 데이터를 바꿀 필요는 없음
                // !!! 1부터 하면 값도 안바뀌었는데 옆으로 가는 경우 생김
                // !!!+1 해줘야 같을때도 1부터 테스트 해봄
                for(int j = map[moved_row][moved_col]-current_height+1; j<=K;j++){
                    current_length = 1 + dfs(moved_row, moved_col, map[moved_row][moved_col]-j, 1);
                    if(current_length>max_length){
                        max_length = current_length;
                    }
                }
            }
        }
        
    }
    //visited[row][col] = 0;
    // 아무데도 방문 안하면 그냥 1이겠지?
    return max_length;
}

int find_max_height_and_search(int max_h){
    // 일단 원하느 높이 있는 좌표들 찾기
    int r, c, way_length, max_length = 0;
    for(r=0;r<N;r++){
        for(c=0;c<N;c++){
            if(map[r][c]==max_h){
                way_length = dfs(r,c,max_h,0);
                if(way_length>max_length) max_length=way_length;
            }
        }
    }
    return max_length;
}

int main(){
    int test_num, t;
    scanf("%d", &test_num);
    for(t=1;t<=test_num;t++){
        // 가장 높은 높이 읽어서
        int maxh = InputData();
        // 풀기
        int ans = find_max_height_and_search(maxh);
        printf("#%d %d\n", t, ans);
    }
    return 0;
}

