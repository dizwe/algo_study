#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <algorithm>
#define DIRNUM 4
using namespace std;

struct rotate_info{
    int idx;
    int row;
    int col;
    int size;
};

int ROW, COL, ROTATE;
vector< vector<int> > arr;
vector<rotate_info> rotate_info_list;
// 으으 방향도 잘못했어
vector<pair<int, int> > dir_info{make_pair(0,1), make_pair(1,0), make_pair(0,-1), make_pair(-1,0)};

void find_min_A();
int find_A();

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin>> ROW >> COL >> ROTATE;
    
    arr.resize(ROW);
    for(int r=0; r<ROW; r++){
        arr[r].resize(COL);
        for(int c=0; c<COL; c++){
            cin >> arr[r][c];
        }
    }
    
    for(int ro=0; ro<ROTATE; ro++){
        int row, col, size;
        cin >> row >> col >> size;
        // !! 우어ㅓ어어 또 실수했어!ㅜㅜ 1부터 시작
        rotate_info_list.emplace_back(rotate_info{
            ro, row-1, col-1, size
        });
    }
    
    find_min_A();
    
    return 0;
}

int find_A(vector< vector<int> > & this_arr){
    int row_sum_min = INT_MAX;
    for(int r=0; r<ROW; r++){
        int row_sum = 0;
        for(int c=0; c<COL; c++)
            row_sum +=this_arr[r][c];
        if(row_sum<row_sum_min) row_sum_min = row_sum;
    }
    return row_sum_min;
}

void rotate_arr(vector<rotate_info> rotate_info_list, vector< vector<int> > &this_arr){
    for(rotate_info one_rotate:rotate_info_list){
        // 사이즈별로 살펴보기
        for (int s=1; s<=one_rotate.size; s++){ // 2면 5칸 가는거
            int start_row = one_rotate.row - s;
            int start_col = one_rotate.col - s;
            int current_size = s*2;
            int this_val = this_arr[start_row][start_col];
            // 네방향 움직이기
            int current_row = start_row;
            int current_col = start_col;
            for(int dir =0; dir<DIRNUM; dir++){
                for(int one_step=1; one_step<=current_size; one_step++){
                    // !!! 이렇게 하면 오른쪽에서 왼쪽으로갈 때 문제
                    //int current_row = start_row + dir_info[dir].first;
                    //int current_col = start_col + dir_info[dir].second*one_step;
                    current_row = current_row + dir_info[dir].first;
                    current_col = current_col + dir_info[dir].second;
                    int next_val = this_arr[current_row][current_col];
                    this_arr[current_row][current_col] = this_val; // 한쪽으로 밀기
                    this_val = next_val; // 이제 다음 방향
                }
            }
        }
    }
 }

bool compare_struct(rotate_info A, rotate_info B){
    return A.idx < B.idx;
}

void find_min_A(){
    // !!! next_permutation recursion으로 할 방법 생각해보기
    int min_A = INT_MAX;
    do{
        vector< vector<int> > this_arr = arr;
        rotate_arr(rotate_info_list, this_arr);
        int A = find_A(this_arr);
        if(A<min_A) min_A = A;
    }while(next_permutation(rotate_info_list.begin(), rotate_info_list.end(), compare_struct));
    // !! next_pemutation int 처럼 비교되는게 아니면 안되나봐...
    cout << min_A;
}

