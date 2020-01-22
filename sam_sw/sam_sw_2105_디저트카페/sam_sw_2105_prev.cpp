#include <stdio.h>
#include <stdlib.h>
#define QUEUE_MAX 200
#define KIND_MAX 200
#include <string.h>

int map[20][20];
int direction[4][2] = {{1,1},{1,-1},{-1,-1},{-1,1}};
int N;
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
   
           put(vertex);
    int not_first = 0;      int max_route = 0;
    
    while(front!=rear){          vertex = get();
        int row = vertex.row;
        int col = vertex.col;
        int length = vertex.length;
        int direction_id = vertex.direction_id;
                 if(!(row==start_row&&col==start_col))
            vertex.visited[row][col]=1;
        
                 if(not_first ==1 &&row == start_row && col == start_col){
            if(max_route<length)
                max_route = length;
        }
        not_first = 1;
        ELE temp_vertex;
        
        
        
                          if(vertex.direction_id==0||vertex.direction_id==1){
                         int next_row;
            int next_col;
                         next_row = row + direction[direction_id][0];
            next_col = col + direction[direction_id][1];
                         if(next_row<N&&next_row>=0&&next_col<N&&next_col>=0
               && vertex.visited[next_row][next_col]==0
               &&vertex.kind[map[next_row][next_col]]==0){
                                         memcpy(&temp_vertex, &vertex, sizeof(ELE));
                    temp_vertex.kind[map[next_row][next_col]] = 1;
                    temp_vertex.row = next_row;
                    temp_vertex.col = next_col;
                    if(temp_vertex.direction_id==0)                          temp_vertex.width++;
                    else if(temp_vertex.direction_id==1)
                        temp_vertex.height++;
                    temp_vertex.length++;
                    put(temp_vertex);
            }
                         next_row = row + direction[direction_id+1][0];
            next_col = col + direction[direction_id+1][1];
                         if(next_row<N&&next_row>=0&&next_col<N&&next_col>=0
               && vertex.visited[next_row][next_col]==0
               && vertex.kind[map[next_row][next_col]]==0
               && vertex.length>0){
                    memcpy(&temp_vertex, &vertex, sizeof(ELE));
                    temp_vertex.direction_id++;                     temp_vertex.kind[map[next_row][next_col]] = 1;
                    temp_vertex.row = next_row;
                    temp_vertex.col = next_col;
                                         if(temp_vertex.direction_id==1)                          temp_vertex.height++;
                    else if(temp_vertex.direction_id==2)
                        temp_vertex.width_down++;
                    temp_vertex.length++;
                
                    put(temp_vertex);
            }
            
        }
                 else if(vertex.direction_id==2||vertex.direction_id==3){
                                                                int next_row;
            int next_col;
                         next_row = row + direction[direction_id][0];
            next_col = col + direction[direction_id][1];
                         if(next_row<N&&next_row>=0&&next_col<N&&next_col>=0
               && vertex.visited[next_row][next_col]==0
               &&vertex.kind[map[next_row][next_col]]==0
               &&((direction_id==3&& vertex.height>vertex.height_down)
                ||(direction_id==2&&vertex.width>vertex.width_down))
               ){                     memcpy(&temp_vertex, &vertex, sizeof(ELE));
                    temp_vertex.kind[map[next_row][next_col]] = 1;
                    temp_vertex.row = next_row;
                    temp_vertex.col = next_col;
                    if(temp_vertex.direction_id==2)                          temp_vertex.width_down++;
                    else if(temp_vertex.direction_id==3)
                        temp_vertex.height_down++;
                    temp_vertex.length++;
                    put(temp_vertex);
                }
            
                         next_row = row + direction[direction_id+1][0];
            next_col = col + direction[direction_id+1][1];
            if(next_row<N&&next_row>=0&&next_col<N&&next_col>=0
               && vertex.visited[next_row][next_col]==0
               &&vertex.kind[map[next_row][next_col]]==0
               ){
                    memcpy(&temp_vertex, &vertex, sizeof(ELE));
                    temp_vertex.direction_id++;                      temp_vertex.kind[map[next_row][next_col]] = 1;
                    temp_vertex.row = next_row;
                    temp_vertex.col = next_col;
                                         if(temp_vertex.direction_id==3)                          temp_vertex.height_down++;
                    temp_vertex.length++;
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

        for(int w = 1; w<N-1;w++){             for(int h = 1; h<N-1;h++){
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

