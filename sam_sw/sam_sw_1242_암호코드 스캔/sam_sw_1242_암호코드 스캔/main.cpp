#include <iostream>
#include <vector>
#define ROW_MAX 2000+5
#define COL_MAX 500+5
#define ONE_CODE_LEN 7
#define CODE_NUM 8
#define WIERD_SPECIAL_NUM 999

using namespace std;
int ROW, COL;
string code[ROW_MAX]; // 문자 하나씩 들어갈거니까
int START_ROW_IDX;
bool find_start = false;
string one_row;


void read_code();
int find_code_num(vector<int> one_code, int size);

const string hex_char_to_bin(char c)
{
    // TODO handle default / error
    // 요오올!! 엄청 simple하네
    switch(toupper(c)){
        case '0': return "0000";
        case '1': return "0001";
        case '2': return "0010";
        case '3': return "0011";
        case '4': return "0100";
        case '5': return "0101";
        case '6': return "0110";
        case '7': return "0111";
        case '8': return "1000";
        case '9': return "1001";
        case 'A': return "1010";
        case 'B': return "1011";
        case 'C': return "1100";
        case 'D': return "1101";
        case 'E': return "1110";
        case 'F': return "1111";
        default : return to_string(WIERD_SPECIAL_NUM);
    }
}

// !! 문제 시작점이 다를 수도 있다.
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    fill(&code[0],&code[ROW_MAX],"");
    find_start = false;
    string decoded_str = "";
    cin >> ROW >> COL;
    
    // !! 띄어쓰기가 되어있는게 아니라서!! 글자를 잘라줘야 한다.
    for(int r =0; r<ROW; r++){
        cin >> one_row;
        for(int c=0; c<COL; c++){
            // hex to string
            decoded_str = hex_char_to_bin(one_row[c]);
            code[r] += decoded_str;
            if(find_start==false && decoded_str!="0000"){
                START_ROW_IDX = r;
                find_start = true;
            }
        }
    }
    
    read_code();

}

// 어차피 한줄만 보면 된다!
void read_code(){
    int return_result = 0;
    // 어디부터 시작하면 좋을까?
    // 7개씩 읽어서 0아닌게 있는지 일단 확인
    int start_col_idx = 0;
    for(int c=0; c<COL*4; c++){ // !!! 여기서는 COL을 쓰면 안되지... 글자를 다 4배씩 늘린건데
        // 한글자씩 읽으면서 확인하기
        if(code[START_ROW_IDX][c]!='0'){
            cout << "C : "<< c <<"\n";
            // !! 아냐.. 시작점은 2일수도 있잖아... ㅜㅜ-> 어떻게 해야되지
            start_col_idx = c-c%ONE_CODE_LEN; // 7에 나누어 떨어지게 만들기!
            break;
        }
    }
    cout << code[START_ROW_IDX] << " kk\n";
    // 시작부터 7개씩 늘리면서 코드 확인하기
    vector <int> one_code;
    vector <int> code_decoded;
    code_decoded.resize(CODE_NUM, 0);
    int code_multiply = 1; // 코드 사이즈 확인하기(확대 된것 처럼 두배로 늘어날수도 있다고 했응니까
    int code_decoded_idx = 0;
    // 전체 코드 한줄 확인하기
    // 8자리수를 다 받았을 땐 어떻게 해야 할까?
    cout << "start_col_idx " << start_col_idx << "\n";
    for(int c=start_col_idx; c<code[START_ROW_IDX].size(); c++){
        one_code.emplace_back(code[START_ROW_IDX][c]-'0');
        // 7개 단위로 코드 확인하기
        if(c%ONE_CODE_LEN==ONE_CODE_LEN-1){
            int code_num_result = find_code_num(one_code, code_multiply);
            cout << code_num_result << "-\n";
            
            if(code_num_result==WIERD_SPECIAL_NUM){
                //한칸 더 늘려서 계속 보기
                code_multiply++;
            }else{
                // 다 비우고 다음 칸 보기
                code_decoded[code_decoded_idx] = code_num_result;
                code_decoded_idx++;
                one_code.clear(); // !!erase는 범위 지정해서!
                code_multiply=1;
            }
        }
        
        if(code_decoded_idx==CODE_NUM-1){ // 다 했으니까 체크!
            // 다 끝나고 계산하기
            int result = 0;
            // 앞에 7자리
            for(int one_c = 0; one_c <CODE_NUM-1; one_c++){
                if(one_c%2==0){// 1부터 시작하는 숫자상으론 홀수라면
                    result += code_decoded[one_c]*3;
                }else{
                    result += code_decoded[one_c];
                }
            }
            result += code_decoded[CODE_NUM-1];
            if(result%10==0){
                for(int one_c = 0; one_c <CODE_NUM; one_c++){
                    return_result += code_decoded[one_c];
                }
            }
            else{
                cout << "\n"; // 이상하다는 걸 표시하기!
                return;
            }
        }
        
    }
    cout << return_result;
}

int find_code_num(vector<int> one_code, int size){ // 두배로 커질수도 있는 경우 감안
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
    
    for(int idx=0 ; idx<one_code.size(); idx++){
        cout << one_code[idx] << " ";
    }
    
    for (int i=0; i<10; i++){
        bool find_num = true;
        for(int idx=0 ; idx<ONE_CODE_LEN; idx++){
            // 반복해서 테스트하기
            for(int multiply_idx =0; multiply_idx<size; multiply_idx++){
                if(code_list[i][idx]!=one_code[idx*size+multiply_idx]){
                    find_num = false;
                    break;
                }
            }
        }
        
        if(find_num == true){
            return i;
        }
    }
    
    return WIERD_SPECIAL_NUM;
}
