#include <iostream>
#include <vector>
#include <algorithm>

#define SDOKU_SIZE 9
#define WIERD_SIZE 19
using namespace std;

struct c_info{
    int row;
    int col;
    vector<int> cand_vector;
};
bool find_result = false;
vector <vector <int> > init_sdoku;


vector <vector <c_info> > get_cand_info(vector <vector <int> > &init_sdoku);
void find_answer(vector <vector <int> > &current_sdoku, vector <vector <c_info> > &cand_info, int start_r, int start_c);

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    init_sdoku.resize(SDOKU_SIZE);
    for(int r=0;r<SDOKU_SIZE; r++){
        for(int c=0;c<SDOKU_SIZE; c++){
            int n;
            cin >> n;
            init_sdoku[r].emplace_back(n);
        }
    }
    
    vector <vector <c_info> > cand_info;
    cand_info = get_cand_info(init_sdoku);
    
    int start_r=WIERD_SIZE, start_c=WIERD_SIZE; // 만약에 아예 0이 없는 상태가 된다면
    bool br=false;
    for(int r=0; r<SDOKU_SIZE&&br==false; r++){
        for(int c=0; c<SDOKU_SIZE&&br==false; c++){
            if(init_sdoku[r][c]==0){
                start_r = r;
                start_c = c;
                br = true;
            }
        }
    }
    
    // 아예 다 채워져 있으면 그냥 출력해도 되니까 그대로!
    if(start_r!=WIERD_SIZE&& start_c != WIERD_SIZE){
        find_answer(init_sdoku, cand_info, start_r, start_c);
    }else{
        cout << "\n";
        for(int r=0;r<SDOKU_SIZE;r++){
            for(int c=0;c<SDOKU_SIZE;c++){
                cout << init_sdoku[r][c] << " ";
            }
            cout << "\n";
        }
    }
    
    return 0;
}

vector <vector <c_info> > get_cand_info(vector <vector <int> > &init_sdoku){
    vector <vector <c_info> > cand_info;
    // row, col, square 별로 모든 Information 얻기
    // !!! []와 ()의 차이 알아내기!
    vector< vector<int> > row(SDOKU_SIZE);
    vector< vector<int> > col(SDOKU_SIZE);
    vector< vector<int> > square(SDOKU_SIZE);
    
    vector<int> whole_number({1,2,3,4,5,6,7,8,9});
    for(int r=0;r<SDOKU_SIZE; r++){
        vector<int> exist_number({});
        for(int c=0;c<SDOKU_SIZE; c++){
            exist_number.emplace_back(init_sdoku[r][c]);
        }
        row[r].resize(SDOKU_SIZE);
        // !!!set_differnce 사용하려면 sort를 해줘야 한다!!
        // !!!back_inserter를 사용하기도 한다
        sort(exist_number.begin(), exist_number.end());
        set_difference(whole_number.begin(), whole_number.end(),
                       exist_number.begin(), exist_number.end(), row[r].begin());
    }
    
    for(int c=0;c<SDOKU_SIZE; c++){
        vector<int> exist_number({});
        for(int r=0;r<SDOKU_SIZE; r++){
            exist_number.emplace_back(init_sdoku[r][c]);
        }
        col[c].resize(SDOKU_SIZE);
        sort(exist_number.begin(), exist_number.end());
        set_difference(whole_number.begin(), whole_number.end(),
                       exist_number.begin(), exist_number.end(), col[c].begin());

    }

    // square
    for(int r=0;r<SDOKU_SIZE; r+=+3){
        for(int c=0;c<SDOKU_SIZE; c=c+3){
            vector<int> exist_number({});
            for(int ir=0; ir<3; ir++){
                for(int ic=0; ic<3; ic++){
                exist_number.emplace_back(init_sdoku[r+ir][c+ic]);
                }
            }
            // !!!범위를 잘못 지정하니까 엄청 느려지느넉였네! 저번에도 그런적 있었음!(엉뚱한 범위 들어갔을 떄)
            square[3*(r/3)+c/3].resize(SDOKU_SIZE);
            sort(exist_number.begin(), exist_number.end());
            // 3개씩 사각형 모양 만드려면 이런식으로! 3*(r/3)+c/3
            set_difference(whole_number.begin(), whole_number.end(),
                           exist_number.begin(), exist_number.end(),square[3*(r/3)+c/3].begin());
        }
    }
    
    cand_info.resize(SDOKU_SIZE);
    for(int r=0; r<SDOKU_SIZE; r++){
        cand_info[r].resize(SDOKU_SIZE);
        for(int c=0; c<SDOKU_SIZE; c++){
            if(init_sdoku[r][c]==0){
                // set_intersection도 sort되어 있어야 한다.
                vector<int> temp_cand_info(SDOKU_SIZE);
                vector<int> one_cand_info(SDOKU_SIZE);
                set_intersection(row[r].begin(), row[r].end(), col[c].begin(), col[c].end(), temp_cand_info.begin());
                set_intersection(temp_cand_info.begin(), temp_cand_info.end(), square[3*(r/3)+c/3].begin(), square[3*(r/3)+c/3].end(), one_cand_info.begin());
                cand_info[r][c] = c_info{r,c,one_cand_info}; // !! 오 이렇게도 되네!!
            }
        }
    }
    return cand_info;
}

void find_answer(vector <vector <int> > &current_sdoku, vector <vector <c_info> > &cand_info, int start_r, int start_c){
    if(find_result==true) return;
    // 일단 얘는 0인 애다
    // 안괜찮으면 다음 cand 찾기(규칙대로 채울 수 없는 경우의 입력은 주어지지 않는다.)
    for(int cand = 0; cand<cand_info[start_r][start_c].cand_vector.size(); cand++){
        int cand_val = cand_info[start_r][start_c].cand_vector[cand];
        if(cand_val==0) continue; // 0으로 fill 되어있어서 삭제
//        cout << cand_val;
        current_sdoku[start_r][start_c] = cand_val;
        // 넣고나서 잘 넣었는지 확인
        bool avail = true;
        
        // 가로
        for(int c=0; c<SDOKU_SIZE&&avail==true; c++){
            // 0은 아니면서 값이 있는게 있는지
            if(c!=start_c&&cand_val!=0&&current_sdoku[start_r][c]==cand_val){
                avail= false;
            }
        }
        // 세로
        for(int r=0; r<SDOKU_SIZE&&avail==true; r++){
            if(r!=start_r&&cand_val!=0&&current_sdoku[r][start_c]==cand_val){
                avail= false;
            }
        }
        // 사각형
        for(int r=0; r<3&&avail==true; r++){
            for(int c=0; c<3&&avail==true; c++){
                int square_r = 3*(start_r/3)+r;
                int square_c = 3*(start_c/3)+c;
                if(start_r!=square_r&& start_c!=square_c && cand_val!=0 && current_sdoku[square_r][square_c]==cand_val){
                    avail = false;
                }
            }
        }
        
        // 가능하면 찾으면 cord 다음 0으로 이동(끝까지 가면 그만두기)
        if(avail==true){
            int current_r=WIERD_SIZE, current_c=WIERD_SIZE; // 그면 끝날때는 어떻게 되지?
            bool br = false;
            for(int r=0; r<SDOKU_SIZE&&br==false; r++){
                // !!!!start_c 부터 하면 안되네... 이거 앞에서도 그런 문제 있었는딩...
                for(int c=0; c<SDOKU_SIZE&&br==false; c++){
                    if(current_sdoku[r][c]==0){
                        current_r = r;
                        current_c = c;
                        br = true;
                    }
                }
            }
            // 가능하면 다음거로 넘어가자.
            if(current_c!=WIERD_SIZE && current_r != WIERD_SIZE){
                find_answer(current_sdoku, cand_info, current_r, current_c);
            }else{
                find_result = true;
                // 다 찾았다 생각하고 인쇄
                //  여러개 나오면 find_result가 해결해줌!
                cout << "\n";
                for(int r=0;r<SDOKU_SIZE;r++){
                    for(int c=0;c<SDOKU_SIZE;c++){
                        cout << current_sdoku[r][c] << " ";
                    }
                    cout << "\n";
                }
            }
            
        } // !!아예 안되면 다음 cand 찾을테지
    }
    // !! 무조건 초기화 해줘야 한다.
    current_sdoku[start_r][start_c] = 0;
        
    
}

