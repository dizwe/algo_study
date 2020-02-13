#include <iostream>
#include <vector>
#include <climits>
#define LARGE_PAPER_NUM 10
#define IMPOSSIBLE_NUM 20
#define BIGGEST_PAPER_SIZE 5
#define EACH_PAPER_LIMIT 5
#define CANNOT_ATTACH false
#define CAN_ATTACH true
#define INSIDE_MAP true
#define OUTSIDE_MAP false
using namespace std;

int min_paper_num = INT_MAX;
int need_cover_num = 0;

bool inside_map(int r, int c){
    if(r>=0 && r<LARGE_PAPER_NUM && c>=0 && c<LARGE_PAPER_NUM){
        return INSIDE_MAP;
    }else{
        return OUTSIDE_MAP;
    }
}

bool find_can_attach_spot(vector < vector <int> > large_paper, int size, int current_row, int current_col, vector <int> each_size_paper_num){
    if(each_size_paper_num[size]>EACH_PAPER_LIMIT){
        return CANNOT_ATTACH;
    }

    // 3 체크할때는 45 체크 안해도 되게? 하면 좋을듯?
    // !! 범위를 넘지는 않는지 확인
    for(int r=0; r<size; r++){
        for(int c=0; c<size; c++){
            int next_row =current_row + r;
            int next_col = current_col + c;
            if(inside_map(next_row, next_col)==OUTSIDE_MAP||large_paper[next_row][next_col]!=1) return CANNOT_ATTACH;
        }    
    }
    // 다 1이었으면
    return CAN_ATTACH;
}

pair <int, int> find_next_point(vector<vector <int> > &large_paper,int start_row, int start_col){
    // 시작점 부터 순서대로 하나씩 데이터 1인 부분 찾아보기
    // !! 범위를 넘지는 않는지 확인하기
    for(int r=start_row;r<LARGE_PAPER_NUM;r++){
        int col = 0;
        if(r==start_row) col = start_col; // 얘는 col부터 시작!
        for (int c=col; c<LARGE_PAPER_NUM; c++){
            if(large_paper[r][c]==1) return make_pair(r,c);
        } 
    }
    // 아무것도 없을떄
    return make_pair(IMPOSSIBLE_NUM, IMPOSSIBLE_NUM);
}

void find_min_paper_num(vector < vector <int> > large_paper, int current_cover_num, int current_row, int current_col, vector <int> each_size_paper_num){ 
    if(need_cover_num==0) min_paper_num = 0;// 0이면 덮을걸 찾을수가 없어서 따로 처리
    
    for(int size=BIGGEST_PAPER_SIZE; size>=1; size--){
        // 붙일 수 있는지 확인하기
        if(find_can_attach_spot(large_paper, size, current_row, current_col,each_size_paper_num)==CAN_ATTACH){
            // 그냥 large paper 그대로 쓰는게 좋으려나?? -> 어차피 복사하는거면 그냥 & 안쓰고 복사해서 받는게 더 좋을지도?
            // 붙일수 있다고 했으니까 붙이기
            // cout << current_row << " " << current_col <<  " " <<size << "\n";
            for(int sr=0; sr<size; sr++){
                for(int sc=0; sc<size; sc++){
                    large_paper[current_row+sr][current_col+sc] = 2; // !!! delta는 따로 delta로 저장해놓는게 좋을듯!
                    current_cover_num++;
                }
            }
            
            each_size_paper_num[size]++;
            // 붙여지면 붙여진 상태로 다음거 찾아서 돌리기
            // !!! 지금 붙인데로 하면 안되지! size를 더해줘야 이동이 되겠지!근데  아예 다음 row가 될수도 있고 다음 col이 될 수도 있다.
            int temp_col = (current_col+size>=LARGE_PAPER_NUM)?0:current_col+size;
            int temp_row = (current_col+size>=LARGE_PAPER_NUM)?current_row+1:current_row; // 만약에 col이 넘어가면 다음 row 찾아야 하니까

            pair<int, int> start_pair = find_next_point(large_paper, temp_row, temp_col); 
            // cout << "next" << start_pair.first << " " << start_pair.second << "\n"; 
            // !!!더이상 붙일수 있는걸 찾을수가 없어! -> 그러면 어떡하지?? 그냥 return!(그 한 점만 찾는거라 바로 for loop 자체가 돌 필요가 없음)
            if(start_pair.first == IMPOSSIBLE_NUM && start_pair.second==IMPOSSIBLE_NUM){
                // !!! 개수를 다섯개 넘지는 않았는지 체크하기!!
                if(need_cover_num==current_cover_num){ // 더이상 안덮어도 되는지 확인
                    int total_paper = 0;
                    for(int s = 1; s<=BIGGEST_PAPER_SIZE; s++){
                        total_paper+=each_size_paper_num[s];
                    }
                    // cout << "total" << total_paper << "\n";
                    if(min_paper_num > total_paper){
                        min_paper_num = total_paper;
                        return; // 더이상 탐색할 필요가 없겠쥬?
                    }
                }
            }
            // !!!!!기존에 찾았던 total_paper보다 더 커지면 굳이 더 찾을 필요 없음!(모두 1일때 가능성 확 준다!)
            int total_paper = 0;
            for(int s = 1; s<=BIGGEST_PAPER_SIZE; s++) total_paper+=each_size_paper_num[s];
        
            if(total_paper<=min_paper_num){
                // 찾았으면 리턴 계속하기
                find_min_paper_num(large_paper, current_cover_num, start_pair.first, start_pair.second, each_size_paper_num);
            }

            // 붙이고나서 되돌리기
            for(int sr=0; sr<size; sr++){
                for(int sc=0; sc<size; sc++){
                    large_paper[current_row+sr][current_col+sc] = 1;
                    current_cover_num--;
                }
            }
            
            each_size_paper_num[size]--;
        }
    }
    
}



int main(){
    vector<vector <int> > large_paper;
    vector <int> each_size_paper_num;
    each_size_paper_num.resize(BIGGEST_PAPER_SIZE+1);// 1부터 시작하게 생각
    fill(&each_size_paper_num[0],&each_size_paper_num[BIGGEST_PAPER_SIZE+1],0);

    large_paper.resize(LARGE_PAPER_NUM);
    for(int i=0; i < large_paper.size(); i++){
        large_paper[i].resize(LARGE_PAPER_NUM);
        int data;
        for(int j =0; j<LARGE_PAPER_NUM; j++){
            cin >> data;
            large_paper[i][j] = data;
            if(data==1) need_cover_num++;
        }
    }
    pair<int, int> start_pair;
    start_pair = find_next_point(large_paper, 0,0);

    find_min_paper_num(large_paper, 0, start_pair.first, start_pair.second, each_size_paper_num);
    
    if(min_paper_num==INT_MAX) cout << -1;// 아예 찾지를 못했으면!
    else cout <<min_paper_num;
        
    return 0;
}
