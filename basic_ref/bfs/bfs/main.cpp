#include <stdio.h>
#define MAX_VERTAX 30

int map[MAX_VERTAX][MAX_VERTAX];
int visit[MAX_VERTAX];
int queue[MAX_VERTAX];
int front, rear, node_num;


// https://gommuluk.tistory.com/m/entry/DFS와-BFS?category=740023

// 이 방식이 간단하긴 한데 queue 크기를 보장 못한다.(계속해서 front, rear증가함)
// 크기를 다시 돌려주는 애가 필요할 듯
// 원형 큐
int get(){
    if(front==rear){
        return -1;
    }
    int k = queue[front];
    front = ++front%MAX_VERTAX;// 다음걸 위해 증가
    return k;
}

int put(int value){
    if((rear+1)%MAX_VERTAX==front){
        return -1; // 오류난거 처리하는건 좀 더 생각해봐야 할듯
    }
    queue[rear] = value;
    rear = ++rear%MAX_VERTAX;// 다음걸 위해 증가
    return value;
}

void bfs(int vertax){
    visit[vertax] = 1;
    printf("%d ", vertax);
    put(vertax);
    while(front!=rear){// queue에 들어있는게 없을떄까지
        vertax = get();
        for(int i=1;i<=node_num;i++){// 모든 다른 노드 방문해서 확인해보기
            if(map[vertax][i]==1 && visit[i]==0){ // 노드에 데이터가 있고 방문한 적도 없으면
                // !!!! 여기서 제대로 방문하는거네
                visit[i] = 1;
                printf("%d ",i);
                put(i);
            }
        }
    }
}

int main(){
    int Test_num;
    int  start;
    scanf("%d",&Test_num);
    scanf("%d %d",&node_num,&start);
    
    int a,b;
    for(int i=0;i<Test_num;i++){
        // 초기화
        for(int i=0;i<MAX_VERTAX;i++){
            for(int j=0; j<MAX_VERTAX; j++){
                map[i][j] = 0;
            }
            visit[i] = 0;
            queue[i]=0;
        }
        front = rear = 0;
        
        while(true){
            scanf("%d %d", &a, &b);
            if(a==-1&&b==-1){
                break;
            }
            map[a][b]=1; map[b][a]=1;
        }
        printf("#%d ", Test_num);
        bfs(start);
        printf("\n");
    }

    return 0;
   
}
