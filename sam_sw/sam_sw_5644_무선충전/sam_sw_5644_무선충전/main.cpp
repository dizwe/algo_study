#include <iostream>
#include <vector>
#include <cmath>
#define MAP_SIZE 10
#define IMPOSSIBLE_CORD 20

using namespace std;
int M, A; // M = 총 이동시간, A = BC의 개수
vector<int> a_steps;
vector<int> b_steps;
vector<vector <vector <int> > > map;
vector<int> ap_power;
int whole_energy = 0;

bool inside_map(int x, int y);
int get_distance(int x1, int y1, int x2, int y2);
pair<int, int> next_cord(pair <int, int> cur_cord, int dir);
void write_map();
void find_max_energy();

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for(int t=1;t <=T; t++){
        ap_power.push_back(0);// 0번에는 아무것도 없어서(1번부터 시작해서) 일단 비우기
           
        cin >> M >> A;
        a_steps.push_back(0); // 처음에 0번발자국
        for (int step=0; step<M; step++){
           int one_step;
           cin >> one_step;
           a_steps.push_back(one_step);
        }
        b_steps.push_back(0);
        for (int step=0; step<M; step++){
           int one_step;
           cin >> one_step;
           b_steps.push_back(one_step);
        }

        map.resize(MAP_SIZE+1); // 1부터 시작하자
        for(int c = 1; c<=MAP_SIZE; c++){
           map[c].resize(MAP_SIZE+1);
        }

        write_map();

        find_max_energy();
           
        cout << "#" << t << " "<< whole_energy << "\n";
        // 전역이었으니까 초기화 해줘야 한다.
        a_steps.clear();
        b_steps.clear();
        map.clear();
        ap_power.clear();
        whole_energy = 0;
    }
   

    return 0;
}

bool inside_map(int x, int y){
    if(x>=1&&y>=1&&x<=MAP_SIZE&& y<=MAP_SIZE) return true;
    else return false;
}

int get_distance(int x1, int y1, int x2, int y2){
    return abs(x1-x2) + abs(y1-y2);
}

pair<int, int> next_cord(pair <int, int> cur_cord, int dir){
    if(dir==0) return make_pair(cur_cord.first, cur_cord.second);
    if(dir==1) return make_pair(cur_cord.first-1, cur_cord.second);
    if(dir==2) return make_pair(cur_cord.first, cur_cord.second+1);
    if(dir==3) return make_pair(cur_cord.first+1, cur_cord.second);
    if(dir==4) return make_pair(cur_cord.first, cur_cord.second-1);
    else return make_pair(IMPOSSIBLE_CORD, IMPOSSIBLE_CORD);
}

void find_max_energy(){
        pair <int, int> a_cord = make_pair(1,1);
        pair <int, int> b_cord = make_pair(10,10);
    
        // 실제로 step 움직이기
        for(int m_step=0; m_step<=M; m_step++){ // !! 0부터면 아에 0넣는 아이디어
            a_cord = next_cord(a_cord, a_steps[m_step]);
            b_cord = next_cord(b_cord, b_steps[m_step]);
    
            int current_max_energy = 0;
            int current_energy = 0;
            for(int a_cand=0; a_cand<map[a_cord.first][a_cord.second].size(); a_cand++){
                for(int b_cand=0; b_cand<map[b_cord.first][b_cord.second].size(); b_cand++){
                    int a_ap = map[a_cord.first][a_cord.second][a_cand];
                    int b_ap = map[b_cord.first][b_cord.second][b_cand];
                    if(a_ap==b_ap){
                        current_energy = ap_power[a_ap]/2 + ap_power[b_ap]/2;
                    }else{
                        current_energy = ap_power[a_ap] + ap_power[b_ap];
                    }
                    if(current_energy>current_max_energy) current_max_energy = current_energy;
                }
            }
            whole_energy = whole_energy + current_max_energy;
        }
}

void write_map(){
    // !!! 아에 없는 경우에도 가능성에 들어강야 하므로 0을 추가하자
    for (int r=1; r<=MAP_SIZE; r++){
        for (int c=1; c<=MAP_SIZE; c++){
             map[r][c].push_back(0);
        }
    }
    
    for (int ap=1; ap<=A; ap++){
        int power;
        int x, y, size;
        cin >> x >> y >> size;
        // size만큼 vector 채우기
        
        for(int sr = -1*size ; sr<=size ; sr++){
            for(int sc = -1*size ; sc<=size ; sc++){
                if(inside_map(y+sr,x+sc)==true){ // 일단 그게 map 안에 있다면 체크
                    if(get_distance(y,x,y+sr, x+sc)<=size){
                        map[y+sr][x+sc].push_back(ap);
                    }
                }
            }
        }
        cin >> power;
        ap_power.push_back(power);
    }
}


// 1. 거리만큼 그림 그리기 문제 생기는 코드
//        // 문제! 두개가 겹쳐버린다.
//        for(int one_s = 1; one_s<=size; one_s++){
//            for(int s = 0; s<=one_s;s++){ // !!!여기서는 0부터 시작해야지!(나부터)
//                // 대각선, 이런 그림 식 잘 생각해보기!!!
//                // 범위 넘어가면 넘기기!
//                if(y+(one_s-s)<=MAP_SIZE&&x+s<=MAP_SIZE) map[y+(one_s-s)][x+s].push_back(ap); // 오른쪽 아래
//                if(y+(one_s-s)<=MAP_SIZE&&x-s>=1) map[y+(one_s-s)][x-s].push_back(ap); // 오른쪽 위
//                if(y-(one_s-s)>=1&& x+s<=MAP_SIZE) map[y-(one_s-s)][x+s].push_back(ap); // 왼쪽 아래
//                if(y-(one_s-s)>=1 && x-s>=1) map[y-(one_s-s)][x-s].push_back(ap); // 왼쪽 위
//            }
//        }


// 2. 먼저 한 가능성을 fix해두면 문제 생기는 코드
//        int a_max = 0;
//        int overlap_a = 0;
//        for(int a_cand=0 ; a_cand<map[a_cord.first][a_cord.second].size(); a_cand++){
//            int current_a = ap_power[map[a_cord.first][a_cord.second][a_cand]];
//            for(int b_cand =0 ; b_cand<map[b_cord.first][b_cord.second].size(); b_cand++){
//                // 같은 충전기를 가지면
//                if(map[a_cord.first][a_cord.second][a_cand]==map[b_cord.first][b_cord.second][b_cand]){
//                    current_a = current_a /2;
//                    overlap_a = map[a_cord.first][a_cord.second][a_cand];
//                }
//            }
//            if(current_a>a_max){
//                // !!겹쳤을 때 a를 "선택"했느냐 안했느냐에 따라서
//                a_max = current_a;
//            }
//        }
//
//        // 이렇게 따로 하는 이유가 하나는 없고 하나는 있는 경우에는 처리가 안되기 때문
//        // b에서 겹치는게 있는지 확인하고 겹치면 반으로 해서 좋은 값 얻기
//        // !!! 아!!! 앞에 애가 뭘 선택했느냐에 따라서 /2를 할건지 안할건지도 정해야 하는구나!!
//        int b_max = 0;
//        for(int b_cand=0 ; b_cand<map[b_cord.first][b_cord.second].size(); b_cand++){
//            int current_b = ap_power[map[b_cord.first][b_cord.second][b_cand]];
//            for(int a_cand =0 ; a_cand<map[a_cord.first][a_cord.second].size(); a_cand++){
//                // 같은 충전기를 가지면
//                if(map[a_cord.first][a_cord.second][a_cand]==map[b_cord.first][b_cord.second][b_cand]){
//                    current_b = current_b /2;
//                }
//            }
//            if(current_b>b_max) b_max = current_b;
//        }


//        for(int r = 1; r<=MAP_SIZE; r++){
//            for(int c = 1; c<=MAP_SIZE; c++){
//                if(map[r][c].size()>0){
//                    cout << map[r][c][0] << " ";
//                }else{
//                    cout <<"0 ";
//                }
//
//            }
//            cout << "\n";
//        }


