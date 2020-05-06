#include <iostream>
#include <climits>
#define MAP_SIZE 10
#define MAX_PAPER_NUM 5
#define PAPER_TYPE_NUM 5
#define WEIRD_NUM -99

using namespace std;

int map[MAP_SIZE+2][MAP_SIZE+2];
int one_num =0;

int one_num_use = 0;
int min_result = INT_MAX;
int paper_info[PAPER_TYPE_NUM+2]; // 5가지 종류

void find_min_paper(int, int, int);

int main() {
    // 이거 삼성에서 써도 되나
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    for(int r=1; r<=MAP_SIZE; r++){
        for(int c=1; c<=MAP_SIZE; c++){
            cin >> map[r][c];
            if(map[r][c]==1) one_num++;
        }
    }
    
    if(one_num==0){
        cout << 0;
    }else{
        fill(&paper_info[0],&paper_info[PAPER_TYPE_NUM+2], MAX_PAPER_NUM);
        bool break_ch = false;
        for(int nr=1; nr<=MAP_SIZE&&break_ch==false; nr++){
            for(int nc=1; nc<=MAP_SIZE&&break_ch==false; nc++){
                if(map[nr][nc]==1){
                    break_ch = true;
                    find_min_paper(nr,nc,0); // !! next row를 할거면 시작점부터 next_row가 해야지
                    break;
                }
            }
        }
        
        if(min_result != INT_MAX)
            cout << min_result;
        else
            cout << -1;
    }
    return 0;
}

bool fill_paper_or_not(int sr, int sc, int size){
    for(int r=sr; r<sr+size; r++){
        for(int c=sc; c<sc+size; c++){
            if(map[r][c] != 1){
                return false;
            }
        }
    }
    for(int r=sr; r<sr+size; r++){
        for(int c=sc; c<sc+size; c++){
            map[r][c] = 10+size;// 1이 겹쳐서 11로 표현(만들다가 실패가 되면? 되돌려야 하므로 위에 넣으면 안됨!!!!)
            one_num_use ++;
        }
    }
    return true;
}

void fill_back_paper(int sr, int sc, int size){
    // 이미 얘가 다 채워져야 한다는건 알고잇다!
    for(int r=sr; r<sr+size; r++){
        for(int c=sc; c<sc+size; c++){
            map[r][c] = 1; // 다시 1로 다 되돌리기
        }
    }
    one_num_use -= size*size; // for loop 안에 쓰면 써지다가 말거 같아서!
}

pair<int, int> find_next_row_col(int row_start, int col_start){
    // 다음으로 이동 할 친구 찾기
    bool break_ch = false;
    for(int nr=row_start; nr<=MAP_SIZE&&break_ch==false; nr++){
        if(nr!=row_start)
            col_start= 0;
        for(int nc=col_start; nc<=MAP_SIZE&&break_ch==false; nc++){
            if(map[nr][nc]==1){
                break_ch = true;
                return make_pair(nr, nc);
            }
        }
    }
    
    return make_pair(WEIRD_NUM, WEIRD_NUM);
}


void find_min_paper(int row_start, int col_start, int total_paper_use){
    // 끝났는지 확인
    if(one_num==one_num_use){
        if(total_paper_use<min_result)
            min_result = total_paper_use;
        return; // !! 여기 리턴하는 것도 중요!!
    }

    for(int size =1; size<=PAPER_TYPE_NUM; size++){
        if(paper_info[size]>0){ // 더이상 사용못하면 넘어가야지
            // 사이즈 만큼 채우기
            if(fill_paper_or_not(row_start, col_start, size)==true){ // 하면서 1num도 증가
                paper_info[size]--;
                pair<int, int> next_info = find_next_row_col(row_start,col_start);
                find_min_paper(next_info.first, next_info.second, total_paper_use+1);
                fill_back_paper(row_start, col_start, size);
                paper_info[size]++;
            }

        }
    }
}


//void find_min_paper(int row_start, int col_start, int total_paper_use){
//    // 시간초과... 백트래킹은 체크 한건 다시 체크 안한다!! 이므로 다시 쫌 짜보자...
//    if(one_num==one_num_use){
//        if(total_paper_use<min_result)
//            min_result = total_paper_use;
//        return;
//    }
//    for(int r=row_start; r<=MAP_SIZE; r++){
//        for(int c=1; c<=MAP_SIZE; c++){
//            if(map[r][c]==1){
//                for(int size=1; size <= PAPER_TYPE_NUM; size++){
//                    if(paper_info[size]>0){ // 더이상 사용못하면 넘어가야지
//                        // 사이즈 만큼 채우기
//                        if(fill_paper_or_not(r, c, size)==true){ // 하면서 1num도 증가
//                            paper_info[size]--;
//                            if(c+size>MAP_SIZE){
//                                find_min_paper(r+1,0,total_paper_use+1);
//                            }else{
//                                find_min_paper(r,c+size, total_paper_use+1);
//                            }
//
//                            fill_back_paper(r, c, size);
//                            paper_info[size]++;
//                        };
//                    }
//                }
//            }
//        }
//    }
//}
