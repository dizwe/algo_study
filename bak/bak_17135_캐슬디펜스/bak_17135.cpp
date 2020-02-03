#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <climits>

#define MAX_N 15
#define MAX_M 15
#define ABNORMAL 20
#define ARCHER_NUM 3
using namespace std;

int N, M, D; // D가 거리
vector<vector <int> > first_castle_map;
int kill_num_max = -INT_MAX;

int dist(int x1, int y1, int x2, int y2){
    return abs(x1-x2) + abs(y1-y2);
}

// 궁수 하나가 쏠 아이 찾기 -> 한꺼번에 같이 쏘는거라 castle_map을 변형하면 안된다.
// !!넘길떄 reference로 넘기면 좀 빨라지려나
pair<int, int> attack(int archer_col, vector <vector <int> > castle_map){
    // 최대 거리만큼 for loop 돌기
    int min_dist = INT_MAX;
    pair<int, int> min_cord;
    bool enemy_exist = false;
    for(int r = N-1; r>=N-D; r--){
        for(int c = 0; c<M; c++){
            if(castle_map[r][c]==1){// 실제로 적이 있을때만 계산하면 되겟지?
                
                int this_dist = dist(N, archer_col, r, c);
    
                if(this_dist<=D){ // 거리를 계산해야지!!!
                    enemy_exist = true;
                    // 거리가 작거나, 거리가 같은데 더 왼쪽일 떄에는 업데이트 // 미친!! min_cord.second c랑 비교해야 하는데 r이라고 적었다.
                    if((this_dist < min_dist)||(this_dist == min_dist && c < min_cord.second)){
                        min_dist = this_dist;
                        min_cord = make_pair(r,c);
                    }
                }
                
            }
        }
    }
    // 아예 공격할 애가 없을떄에도 처리해줘야 한다!
    if(enemy_exist == true) return min_cord;
    else if(enemy_exist== false) return make_pair(ABNORMAL, ABNORMAL); // 이상치 값을 리턴함으로써
}

bool inside_map(int r, int c){
    // !!! 0보다는 같거나 커야 한다!!
    if(r<N && c<M && r>=0 && c>=0) return true;
    else return false;
}

// 궁수 하나가 쏠 아이 찾기 -> 한꺼번에 같이 쏘는거라 castle_map을 변형하면 안된다.
// 거리 식을 아니까 주변 거리에서 찾아지면 그 다음은 안찾아도 되도록 만든다.
// 70퍼에서 런타임
pair<int, int> attack2(int archer_col, vector <vector <int> > &castle_map){
    // 최대 거리만큼 for loop 돌기
    int min_dist = INT_MAX;
    pair<int, int> min_cord;
    bool enemy_exist = false;
    for(int d =1; d<=D &&  enemy_exist==false; d++){
        // cout << "dist : " << d <<" "<<archer_col<< "\n";
        // 왼쪽 삼각형(왼쪽부터 찾기)
        for(int i =1; i<=d &&  enemy_exist==false;i++){
            int test_row= N-i;
            int test_col = archer_col-(d-i); // 여기서는 d
            // cout << test_row << " " << test_col << "\n";
            if(inside_map(test_row, test_col) && castle_map[test_row][test_col]==1){ // 범위는 벗어나지 않는가? 
                min_dist = d;
                min_cord = make_pair(test_row, test_col);
                enemy_exist = true;
            }
        }
        // 오른쪽 삼각형
        for(int i =1; i<=d-1 &&  enemy_exist==false;i++){
            int test_row= N-(d-i);
            int test_col = archer_col+i;
            // cout << test_row << " " << test_col << "\n";
            // !!! 이거 순서 바뀌어서 런타임 에러남!!!!!!!
            if(inside_map(test_row, test_col)&&castle_map[test_row][test_col]==1){
                min_dist = d;
                min_cord = make_pair(test_row, test_col);
                enemy_exist = true;
            }
        }
    }
    // 아예 공격할 애가 없을떄에도 처리해줘야 한다!
    if(enemy_exist == true) return min_cord;
    else if(enemy_exist== false) return make_pair(ABNORMAL, ABNORMAL); // 이상치 값을 리턴함으로써
}

void get_down(vector< vector<int> > &castle_map){
    for(int r = N-2; r>=0; r--)
        for(int c= 0; c<M; c++)
            castle_map[r+1][c] = castle_map[r][c];
    
    // 제일 위에 row는 0으로 채우기
    for(int c= 0; c<M; c++)
        castle_map[0][c] = 0;
}


void simulate(){ 
    // 조합 만들기!
    // n개중에 k개 만들어줄 친구 initize 000 11로 만든다
    int* permute_idx = new int[M];
    int* choosed_archer_idx = new int[ARCHER_NUM];
    fill(&permute_idx[0], &permute_idx[M], 0);
    for(int i=M-ARCHER_NUM; i<M; i++) permute_idx[i]= 1;

    // sort(&permute_idx[0], &permute_idx[M]);// !!! sort를 꼭 해줘야 한다!!! sorting을 하면서 만들어지느거인듯  아니면 111000이 아니라 000111로 되게 만들던가
    do{
        int push= 0;
        // 3명의 궁수 위치가 정해진다.
        for(int i=0; i<M; i++){
            if(permute_idx[i]== 1) choosed_archer_idx[push++] = i;
        }
        vector <vector <int> > castle_map;
        vector <pair<int, int> > kill_pair;
        pair<int, int> this_pair;
        int kill_num = 0;
        castle_map = first_castle_map;

        //row 개수만큼 내려가면서 게산
        for(int r=0; r<N; r++){
            for(int i =0; i<ARCHER_NUM; i++){
                // cout << "archer" << i << "\n";
                this_pair = attack2(choosed_archer_idx[i],castle_map);
                // cout<< choosed_archer_idx[i] << " \n"; 
                // 아예 죽일 적이 없는 경우에는 추가도 하면 안되지
                if(this_pair.first!=ABNORMAL && this_pair.second!=ABNORMAL)
                    kill_pair.push_back(this_pair); // 죽여야 하는 애들 찾기
            }
            
            // 공격한 애들 죽이기
            for(int i = 0; i<kill_pair.size(); i++){
                castle_map[kill_pair[i].first][kill_pair[i].second] = 0;
                // 공격한 애들중에 겹치면 개수 안센다.
                bool is_attack = false;
                // cout << kill_pair[i].first << " "<< kill_pair[i].second << "\n";
                for(int j = 0; j<i; j++){ // !!내 앞에!! 애 중에서 겹치는게 있었니? 
                    if(kill_pair[j].first == kill_pair[i].first && kill_pair[i].second == kill_pair[j].second) 
                        is_attack = true; 
                }
                if(is_attack == false) kill_num++; 
            }
            kill_pair.clear();

            // 한칸 내리기
            get_down(castle_map);
            // cout << "\n";
            // for(int r =0; r<N; r++){
            //     for(int c=0; c<M; c++){
            //         cout << castle_map[r][c] << " ";
            //     }
            //     cout << " \n";
            // }
            // cout << kill_num << "\n";

        }
        
        if(kill_num> kill_num_max) kill_num_max = kill_num;
        // for(int i=0; i<ARCHER_NUM; i++){
        //     cout << choosed_archer_idx[i]  << " ";
        // }
        // cout << "\n---- NEXTPERMUTE --" << kill_num <<"\n";
    }while(next_permutation(&permute_idx[0], &permute_idx[M]));

    
}


void simulate2(){ 
    // 조합 만들기!
    // n개중에 k개 만들어줄 친구 initize 000 11로 만든다
    int* permute_idx = new int[M];
    int* choosed_archer_idx = new int[ARCHER_NUM];
    fill(&permute_idx[0], &permute_idx[M], 0);
    for(int i=M-ARCHER_NUM; i<M; i++) permute_idx[i]= 1;
    // 정렬해서 3번째 column보다 값이 작으면 아예 돌리지도 않게(같으면 돌리고)
    int* col_enemy_info = new int[M];
    int* col_enemy_info_for_sort = new int[M];
    for(int c=0; c<M; c++){
        int col_enemy_num = 0;
        for(int r=0; r<N; r++)
            if(first_castle_map[r][c]==1) col_enemy_num++;
        col_enemy_info[c] = col_enemy_num;
        col_enemy_info_for_sort[c] = col_enemy_num; // sort는 따로 확인용을 위해 사용!
    }
    sort(&col_enemy_info_for_sort[0], &col_enemy_info_for_sort[M]);
    int third_enemy_num = col_enemy_info_for_sort[2]; // 3번째로 큰거

    // sort(&permute_idx[0], &permute_idx[M]);// !!! sort를 꼭 해줘야 한다!!! sorting을 하면서 만들어지느거인듯  아니면 111000이 아니라 000111로 되게 만들던가
    do{

        int push= 0;
        // 3명의 궁수 위치가 정해진다.
        for(int i=0; i<M; i++){
            if(permute_idx[i]== 1) choosed_archer_idx[push++] = i;
        }
        
        // 하나라도 third_enemy_num보다 작으면 아예 안돌리고 넘어가자.
        bool should_calculate = true;
        for(int i=0; i<ARCHER_NUM; i++){
            if(col_enemy_info[choosed_archer_idx[i]]<third_enemy_num){
                should_calculate = false;
                break;
            }
        }
        if(should_calculate==false) continue;
        vector <vector <int> > castle_map;
        vector <pair<int, int> > kill_pair;
        pair<int, int> this_pair;
        int kill_num = 0;
        castle_map = first_castle_map;

        //row 개수만큼 내려가면서 게산
        for(int r=0; r<N; r++){
            for(int i =0; i<ARCHER_NUM; i++){
                // cout << "archer" << i << "\n";
                this_pair = attack2(choosed_archer_idx[i],castle_map);
                // cout<< choosed_archer_idx[i] << " \n"; 
                // 아예 죽일 적이 없는 경우에는 추가도 하면 안되지
                if(this_pair.first!=ABNORMAL && this_pair.second!=ABNORMAL)
                    kill_pair.push_back(this_pair); // 죽여야 하는 애들 찾기
            }
            
            // 공격한 애들 죽이기
            for(int i = 0; i<kill_pair.size(); i++){
                castle_map[kill_pair[i].first][kill_pair[i].second] = 0;
                // 공격한 애들중에 겹치면 개수 안센다.
                bool is_attack = false;
                // cout << kill_pair[i].first << " "<< kill_pair[i].second << "\n";
                for(int j = 0; j<i; j++){ // !!내 앞에!! 애 중에서 겹치는게 있었니? 
                    if(kill_pair[j].first == kill_pair[i].first && kill_pair[i].second == kill_pair[j].second) 
                        is_attack = true; 
                }
                if(is_attack == false) kill_num++; 
            }
            kill_pair.clear();

            // 한칸 내리기
            get_down(castle_map);
            // cout << "\n";
            // for(int r =0; r<N; r++){
            //     for(int c=0; c<M; c++){
            //         cout << castle_map[r][c] << " ";
            //     }
            //     cout << " \n";
            // }
            // cout << kill_num << "\n";

        }
        
        if(kill_num> kill_num_max) kill_num_max = kill_num;
        // for(int i=0; i<ARCHER_NUM; i++){
        //     cout << choosed_archer_idx[i]  << " ";
        // }
        // cout << "\n---- NEXTPERMUTE --" << kill_num <<"\n";
    }while(next_permutation(&permute_idx[0], &permute_idx[M]));

    
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> M >> D;
    
    first_castle_map.resize(N);
    for(int r =0; r<N; r++){
        first_castle_map[r].resize(M); // [r]하는거 까먹지 말자은!!
        for(int c=0; c<M; c++)
            cin >> first_castle_map[r][c];
    }
    simulate2(); 
    
    // cout << "\n";
    cout << kill_num_max << "\n";
    // for(int r =0; r<N; r++){
    //     for(int c=0; c<M; c++){
    //         cout << first_castle_map[r][c] << " ";
    //     }
    //     cout << "\n";
    // }
    return 0;
}

/////???!!!!