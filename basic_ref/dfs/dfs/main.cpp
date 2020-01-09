#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 30
int vertex;
int map[MAX_VERTEX][MAX_VERTEX];
int visited[MAX_VERTEX];

void dfs(int v){
    
      visited[v]=1;
      // 주의!!! 1부터 시작해서 끝까지 가야함. node 자체가 1부터 시작하니까!
      for(int i=1;i<=MAX_VERTEX;i++){
            if(map[v][i]==1&&!visited[i]){
                  printf("%d ",i);
                  dfs(i);
                }
          }
}

int main(){
      int test_num;
      scanf("%d", &test_num);
    
      // 초기화
      for(int i =0; i<test_num;i++){
            for(int j=0;j<MAX_VERTEX;j++){
                  for(int k=0;k<MAX_VERTEX;k++){
                        map[j][k]=0;
                      }
                  visited[j]=0;
                }
          }
    
      int start;
      scanf("%d %d",&vertex, &start);
      while(true){
            int s,e;
            scanf("%d %d",&s, &e);
            if(s==-1&&e==-1){
                  break;
            }
            map[s][e]=1;
            map[e][s]=1;
          }
    
      printf("%d ",start);
      dfs(start);
}

