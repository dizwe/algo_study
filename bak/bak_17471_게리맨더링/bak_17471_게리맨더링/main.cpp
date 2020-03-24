#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <cmath>
#define MAX_N 10
#define NOT_AVAIL -1
#define EMPTY 99

using namespace std;
int N;
int divisions_map[MAX_N + 5][MAX_N + 5];
int divisions_people_info[MAX_N + 5];
int divisions[MAX_N + 5]; // 1과 0으로 나누기
int min_diff = INT_MAX;

void find_fair_division(int from_idx);
int test_connectivity();

int main(int argc, const char * argv[]) {
    cin >> N;

    // 1번부터 번호가 매겨져 있으니 1번부터 채우자!(!!!헷갈리니까 비어있는건 EMPTY)
    // !! EMPTY로 했을 때 생기는 문제 정리하기!(1,0, 9,9,9로 확인하면 이상하지!)
    fill(&divisions[0], &divisions[MAX_N + 5], 0);
    // 체크할 때 EMPTY 이후는 안봐도 됙 하는거지!
    fill(&divisions_map[0][0], &divisions_map[MAX_N + 4][MAX_N + 5], EMPTY);
    
    for(int i=1; i<=N; i++)
        cin >> divisions_people_info[i];
    
    for(int i=1; i<=N; i++){
        int neighbor_num;
        cin >> neighbor_num;
        for(int ne =1; ne<=neighbor_num; ne++){
            int one_neighbor;
            cin >> one_neighbor;
            // map안의 정보는 0부터 시작!
            divisions_map[i][ne] = one_neighbor;
        }
    }
    divisions[1] = 1; // 1번은 고정해서 똑같은 조합인데 1과 0이 뒤집히는 일은 업섹 하기
    find_fair_division(2);
    if(min_diff!=INT_MAX)
        cout << min_diff;
    else
        cout << -1;
    return 0;
}

void find_fair_division(int current_idx){
//    bool visited[MAX_N+5];
//    fill(&visited[0], &visited[MAX_N+5], false);
    
    for(int num=0; num<=1; num++){
        divisions[current_idx] = num;
        int test_result = test_connectivity();
        if(test_result!= NOT_AVAIL){ // 차를 abs로 받기(차가 -1은 나올리가 없음)
            if(test_result<min_diff){
                min_diff = test_result;
            }
        }
        if(current_idx+1<=N)
            find_fair_division(current_idx+1);
    }
}

int test_connectivity(){
    int two_total[2] = {0,0};
    
    int visited[MAX_N+5];
    fill(&visited[0], &visited[MAX_N+5],EMPTY);
    
    // 0과 1 모두 방문해보기! -> 모양이 똑같으면 방문 가능한거지
    for(int div_num=0; div_num<=1; div_num++){
        queue<int> test_que;
        if(div_num ==1){
            test_que.push(1);
            visited[1] = div_num;
            two_total[1] += divisions_people_info[1];
        }else{
            // 최초의 0을 찾기
            for(int i=1;i<=N;i++){
                if(divisions[i]==0){
                    test_que.push(i);
                    visited[i] = div_num;
                    two_total[0] += divisions_people_info[i];
                    break;
                }
            }
        }
        
        // 방문
        while(!test_que.empty()){
            int current_pos = test_que.front();
            test_que.pop();
            
            int ne=1;
            // 이웃들 찾기
            while(ne<= N && divisions_map[current_pos][ne]!=EMPTY){ // 이웃하는 애들 찾기
                int neighbor_idx = divisions_map[current_pos][ne];
                if(divisions[neighbor_idx] ==div_num && visited[neighbor_idx]==EMPTY){ // 방문 안했고 이웃하는 애가 내가 찾는 그 번호라면
                    two_total[div_num] += divisions_people_info[neighbor_idx];
                    visited[neighbor_idx] = div_num; // !! visit은 여기에!
                    test_que.push(neighbor_idx);
                    
                }
                ne++;
            }
        }
        
    }
    
    // 1인건 1인지 확인(사실 미리 확인할 수 있으면 좋긴 한데)
    int idx = 1;
    while(idx<= N){
        if(visited[idx]!=divisions[idx]){
            return NOT_AVAIL;
        }
        idx++;
    }
        
    // 다 끝나면 잘 맞는지 확인
    return abs(two_total[0]-two_total[1]);
}



