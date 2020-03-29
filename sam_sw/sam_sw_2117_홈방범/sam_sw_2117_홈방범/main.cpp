#include <iostream>
#include <climits>
#include <vector>
#include <cmath>
#define MAX_SIZE 20

using namespace std;

int SIZE, INCOME;
int map[MAX_SIZE+2][MAX_SIZE+2]; // !! 늘 여유롭게 많이 적자
int map_people[MAX_SIZE+2];
int max_house = INT_MIN;
int T;

void find_max_house();
void get_house_num(int center_r, int center_c);
bool inside_boundary(int row, int col);

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> T;
    for(int t=1;t<=T;t++){
        fill(&map[0][0],&map[MAX_SIZE+2][MAX_SIZE+2],0);
        max_house = INT_MIN;
        cin >> SIZE >> INCOME;
        for(int r=0; r<SIZE; r++){
            for(int c=0; c<SIZE; c++){
                cin >> map[r][c];
            }
        }
        
        find_max_house();
        cout << "#" << t << " "<< max_house << "\n";
    }
    return 0;
}

void find_max_house(){
    for (int r=0; r<SIZE; r++){
        for(int c=0; c<SIZE; c++){
            fill(&map_people[0],&map_people[MAX_SIZE+2],0);
            int cummulated_house = 0; // 주변에 한개씩 더 쌓으면서 체크하기(그냥 아예 거리를 두고 확인하기)
            get_house_num(r, c);
            // 각 사이즈별로 거리 확인하기
            for(int s=1; s<=SIZE+1; s++){ // !!  짝수 홀수 때문에 범위가 안맞음! 한개 더 해야
                // 손해를 안볼 때
                cummulated_house += map_people[s];
                if(s*s+(s-1)*(s-1) <= cummulated_house*INCOME){
                    if(max_house < cummulated_house)
                        max_house = cummulated_house;
                }
            }
        }
    }
}

bool inside_boundary(int row, int col){
    if(row>=0 && row<SIZE && col>=0 && col<SIZE)
        return true;
    else
        return false;
}

int manhatan_distance(int x1, int x2, int y1, int y2){
    return abs(x1-x2) + abs(y1-y2);
}

void get_house_num(int center_r, int center_c){
    for(int sr= center_r-(SIZE-1); sr<center_r+SIZE; sr++){
        for(int sc= center_c-(SIZE-1); sc<center_c+SIZE; sc++){
            if(inside_boundary(sr, sc)==true && map[sr][sc]==1){
                int house_dist = manhatan_distance(sr, center_r, sc, center_c) + 1;
                if(house_dist<=SIZE+1) // 범위넘는건 예상치 못한 결과 나올 수 있음.
                    map_people[house_dist]++; // 해당 거리의 개수
            }
        }
    }
}

