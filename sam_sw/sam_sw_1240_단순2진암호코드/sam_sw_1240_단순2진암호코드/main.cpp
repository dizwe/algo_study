#include <iostream>
#define ROW_MAX 50+5
#define COL_MAX 100+5
#define ONE_CODE_LEN 7
#define CODE_NUM 8
#define WIERD_SPECIAL_NUM 999

using namespace std;
int ROW, COL;
int code[ROW_MAX][COL_MAX];
int START_ONE_ROW, START_ONE_COL;
bool find_start = false;
string one_row;
int T;

void read_code(int t);
int check_validity(int start_r, int start_c);
int find_code_num();

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> T;
    for(int t=1; t<=T; t++){
        fill(&code[0][0],&code[ROW_MAX-1][COL_MAX],0);
        find_start = false;
        cin >> ROW >> COL;
        
        // !! 띄어쓰기가 되어있는게 아니라서!! 글자를 잘라줘야 한다.
        for(int r =0; r<ROW; r++){
            cin >> one_row;
            for(int c=0; c<COL; c++){
                code[r][c] = one_row[c]-'0';
                if(find_start == false && code[r][c]==1){
                    START_ONE_ROW = r;
                    START_ONE_COL = c;
                    find_start= true;
                }
            }
        }
        
        read_code(t);
        
    }

}

void read_code(int t){
    // 여러줄 체크하기
    bool find_num = false;
    for(int check_col = START_ONE_COL-3; check_col<=START_ONE_COL; check_col++){
        if(check_col>=0){
            int final_result = check_validity(START_ONE_ROW, check_col);
            if(final_result!=WIERD_SPECIAL_NUM){
                cout << "#" <<t << " "<<final_result << "\n";
                find_num = true;
                break;
            }
        }
    }
    if(find_num==false) cout << "#" <<t << " 0" << "\n";
}
int find_code_num(int one_code[ONE_CODE_LEN]){
    // 숫자 자체도 이상한 숫자일수도 있다!
    int code_list[10][ONE_CODE_LEN] = {
        {0,0,0,1,1,0,1},
        {0,0,1,1,0,0,1},
        {0,0,1,0,0,1,1},
        {0,1,1,1,1,0,1},
        {0,1,0,0,0,1,1},
        {0,1,1,0,0,0,1},
        {0,1,0,1,1,1,1},
        {0,1,1,1,0,1,1},
        {0,1,1,0,1,1,1},
        {0,0,0,1,0,1,1},
    };
    
    for (int i=0; i<10; i++){
        bool find_num = true;
        for(int idx=0 ; idx<ONE_CODE_LEN; idx++){
            if(code_list[i][idx]!=one_code[idx]){
                find_num = false;
                break;
            }
        }
        if(find_num == true){
            return i;
        }
    }
    
    return WIERD_SPECIAL_NUM;
}

int check_validity(int start_r, int start_c){
    int num_info[CODE_NUM];
    for(int one_c = 0; one_c <CODE_NUM; one_c++){
        // 한 문자 info 받아서 append 할수 있게 init
        int one_code[ONE_CODE_LEN];
        for(int i=0 ; i<ONE_CODE_LEN; i++){
            one_code[i] = code[start_r][start_c+one_c*ONE_CODE_LEN+i];
        }
        // 그 코드가 무슨 숫자인지 찾기
        int result_num = find_code_num(one_code);
        if(result_num==WIERD_SPECIAL_NUM) return WIERD_SPECIAL_NUM; // 이상한 숫자로 읽힌다면 얘는 아님!
        num_info[one_c] = result_num;
    }
    
    // 다 끝나고 계산하기
    int result = 0;
    for(int one_c = 0; one_c <CODE_NUM-1; one_c++){
        if(one_c%2==0){// 1부터 시작하는 숫자상으론 홀수라면
            result += num_info[one_c]*3;
        }else{
            result += num_info[one_c];
        }
    }
    result += num_info[CODE_NUM-1];
    if(result%10==0){
        int return_result = 0;
        for(int one_c = 0; one_c <CODE_NUM; one_c++){
            return_result += num_info[one_c];
        }
        return return_result;
    }
    else
        return WIERD_SPECIAL_NUM;
}
