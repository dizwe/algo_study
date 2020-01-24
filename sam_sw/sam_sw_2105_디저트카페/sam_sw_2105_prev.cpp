#include <stdio.h>
#include <stdlib.h>
#define QUEUE_MAX 200
#define KIND_MAX 200
#include <string.h>

int map[20][20];
int direction[4][2] = {{1,1},{1,-1},{-1,-1},{-1,1}};
int N;// 가로세로 길이

typedef struct{
    int row;
    int col;
    int direction_id;
    int width;
    int height;
    int width_down;
    int height_down;
    int kind[KIND_MAX];
    int visited[20][20];
    int length;
} ELE;

ELE queue[QUEUE_MAX];
int front=0, rear=0;

void put(ELE vertex){
    if((rear+1)%QUEUE_MAX == front){
        printf("FULLL");
    }
    queue[rear] = vertex;
    rear = (++rear)%QUEUE_MAX;
}

ELE get(){
    if(front==rear){
        printf("empty");
    }
    ELE vertex = queue[front];
    front = (++front)%QUEUE_MAX;
    return vertex;
}

// free 해주는 것도 만들기
ELE init_vertex(int start_row, int start_col){
    ELE vertex;
    vertex.row = start_row;
    vertex.col = start_col;
    vertex.direction_id = 0;
    vertex.width = 0;
    vertex.height = 0;
    vertex.height_down = 0;
    vertex.width_down = 0;
    vertex.length = 0;
    for(int i = 0; i<KIND_MAX;i++){
        vertex.kind[i] = 0;
    }
    for(int w = 0; w<20;w++){
        for(int h = 0; h<20;h++){
            vertex.visited[w][h]=0;
        }
    }
    return vertex;
}


int bfs(int start_row, int start_col){
    ELE vertex;
    vertex = init_vertex(start_row, start_col);
   
    // !!!!!!!첫점은 visited로 안해야 돌아갈수 있겠따!!
//    vertex.visited[start_row][start_col]=1;
//    vertex.kind[map[start_row][start_col]] = 1;// 종류에 얘는 이미 방문한거라고 체크
    put(vertex);
    bool not_first = 0; // 처음으로 다시 돌아와야 하는데 하나도 안가고 끝나는 것 방지
    int max_route = 0;
    
    while(front!=rear){ // queue에 들어있는게없을 때 까지
        vertex = get();
        int row = vertex.row;
        int col = vertex.col;
        int length = vertex.length;
        int direction_id = vertex.direction_id;
        // !!!!! 여기서도 시작점은 체크 안하게 해줘야 함
        if(!(row==start_row&&col==start_col))
            vertex.visited[row][col]=1;
        
        // 다시 처음으로 돌아왔을 때
        if(not_first ==1 &&row == start_row && col == start_col){
            if(max_route<length)
                max_route = length;
        }
        not_first = 1;// 이제 첨이 아냐.
        
        ELE temp_vertex;
        
        
        
        // 나아가기(갈 수 있는 가능성의 길들을 추가하는 과정
        // ㄱ 모양일 때( 자유롭게 길게 뻗어 나가자)
        if(vertex.direction_id==0||vertex.direction_id==1){
            // 거기서 계속 나아갈 수도 있고 방향을 바꿀 수도 있음
            int next_row;
            int next_col;
            // 계속 나아가기. 나아갈 수 있으면 추가
            next_row = row + direction[direction_id][0];
            next_col = col + direction[direction_id][1];
            // 방문한 적 없고, kind에 없고, 범위 안넘어설 때
            if(next_row<N&&next_row>=0&&next_col<N&&next_col>=0
               && vertex.visited[next_row][next_col]==0
               && vertex.kind[map[next_row][next_col]]==0){
                    // vertex를 할 떄마다 새롭게 copy 해줘야지!!
                    memcpy(&temp_vertex, &vertex, sizeof(ELE));
                    temp_vertex.kind[map[next_row][next_col]] = 1;
                    temp_vertex.row = next_row;
                    temp_vertex.col = next_col;
                    if(temp_vertex.direction_id==0) //가로를 더하기
                        temp_vertex.width++;
                    else if(temp_vertex.direction_id==1)
                        temp_vertex.height++;
                    temp_vertex.length++;
                    put(temp_vertex);
            }
            // 방향을 바꾸기
            next_row = row + direction[direction_id+1][0];
            next_col = col + direction[direction_id+1][1];
            // 방문한 적 없고, kind에 없고, 범위 안넘어설 때, 그리고 처음에 한번은 이동 했을 때
            if(next_row<N&&next_row>=0&&next_col<N&&next_col>=0
               && vertex.visited[next_row][next_col]==0
               && vertex.kind[map[next_row][next_col]]==0
               && vertex.length>0){
                    memcpy(&temp_vertex, &vertex, sizeof(ELE));
                    temp_vertex.direction_id++;// 방향 바꾸기 따로 해줘야 함
                    temp_vertex.kind[map[next_row][next_col]] = 1;
                    temp_vertex.row = next_row;
                    temp_vertex.col = next_col;
                    // !!!!!! 방향을 바꾸고 나서니까 그 이후로 계산해야지
                    if(temp_vertex.direction_id==1) //가로를 더하기(바뀐 direction id)
                        temp_vertex.height++;
                    else if(temp_vertex.direction_id==2)
                        temp_vertex.width_down++;
                    temp_vertex.length++;
                
                    put(temp_vertex);
            }
            
        }
        // ㄴ 모양일 때 갈 수 있는 길이는 이미 정해져 있음.
        else if(vertex.direction_id==2||vertex.direction_id==3){
            // 길이 꽉 찼을 때는 방향을 바꿀 수 있음
            // 길이 안찼는데 못바꾸면 얘는 가능성 없는거지..
            // ?? 가다 만건 어떻게 처리해야하지?
            // 이미 height와 width는 정해져 있음.
            int next_row;
            int next_col;
            // 계속 나아가기. 나아갈 수 있으면 추가
            next_row = row + direction[direction_id][0];
            next_col = col + direction[direction_id][1];
            // 방문한 적 없고, kind에 없고, 범위 안넘어서고, 길이는 아직 안찼을 때
            // !!!!!!!! height down 비교하는걸 height도 안넘고, width도 안넘는걸로 해버리니까 오류가 난다.
            if(next_row<N&&next_row>=0&&next_col<N&&next_col>=0
               && vertex.visited[next_row][next_col]==0
               &&vertex.kind[map[next_row][next_col]]==0
               &&((direction_id==3&& vertex.height>vertex.height_down)
                ||(direction_id==2&&vertex.width>vertex.width_down))
               ){// 하나라도 높거나 같은게 있으면 안디ㅗㄴ다
                    memcpy(&temp_vertex, &vertex, sizeof(ELE));
                    temp_vertex.kind[map[next_row][next_col]] = 1;
                    temp_vertex.row = next_row;
                    temp_vertex.col = next_col;
                    if(temp_vertex.direction_id==2) //가로를 더하기
                        temp_vertex.width_down++;
                    else if(temp_vertex.direction_id==3)
                        temp_vertex.height_down++;
                    temp_vertex.length++;
                    put(temp_vertex);
                }
            
            // 방향 바꾸기
            next_row = row + direction[direction_id+1][0];
            next_col = col + direction[direction_id+1][1];
            if(next_row<N&&next_row>=0&&next_col<N&&next_col>=0
               && vertex.visited[next_row][next_col]==0
               &&vertex.kind[map[next_row][next_col]]==0
               ){
                    memcpy(&temp_vertex, &vertex, sizeof(ELE));
                    temp_vertex.direction_id++; // 방향 바꾸기 따로 해줘야 함
                    temp_vertex.kind[map[next_row][next_col]] = 1;
                    temp_vertex.row = next_row;
                    temp_vertex.col = next_col;
                    temp_vertex.length++;
                    // !!!!!! 방향을 바꾸고 나서니까 그 이후로 계산해야지
                    if(temp_vertex.direction_id==3) //가로를 더하기
                        temp_vertex.height_down++;
                        put(temp_vertex);
                
            }
            
        }
        
    }
    return max_route;
}

int main(){
    int TEST_NUM;
    scanf("%d",&TEST_NUM);
    
    for (int i = 0;i<TEST_NUM;i++){
        
        
        //init
        for(int w = 0; w<20;w++){
            for(int h = 0; h<20;h++){
                map[w][h]=0;
            }
        }
        
        scanf("%d", &N);
        int max=-1;
        for(int w = 0; w<N;w++){
            for(int h = 0; h<N;h++){
                scanf("%d",&map[w][h]);
            }
        }

        for(int w = 1; w<N-1;w++){// 제일 앞과 끝은 사각형 만들수가 없음
            for(int h = 1; h<N-1;h++){
                int one_spot_result = bfs(w,h);
                if(one_spot_result>max){
                    max = one_spot_result;
                }
            }
        }

        
        if(max ==0)
            max =-1;
        
        printf("#%d %d\n", i+1, max);
    }
    
}

