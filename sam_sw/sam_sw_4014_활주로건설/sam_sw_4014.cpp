#include <iostream>
#define MAX_MAP_SIZE 21
#define CAN_BUILD true
#define CANNOT_BUILD false
using namespace std;

int runway_map[MAX_MAP_SIZE][MAX_MAP_SIZE];
bool line_check[MAX_MAP_SIZE];
int map_size, slope_size;
int can_build_num = 0;

bool inside_map(int row, int col){
    return row < map_size && col< map_size;
}

// ??? MAX_MAP_SIZE 21로 바꿨는데 갑자기 다 통과 되었다 이유가 모지?
bool can_build_line_horizontal(int row_num){
    // col별로 돌면서 체크
    fill(&line_check[0],&line_check[MAX_MAP_SIZE],false);
    for(int i=0; i<map_size-1; i++){        
        if(runway_map[row_num][i]-1==runway_map[row_num][i+1]){ //// 내려가는건 ""이후가"" 확보되는지 체크
            for(int j=0; j<slope_size-1; j++){
                // 1개일때는 어떡해? -> 길이는 2이상이래!(조건 확인)
                // map에 벗어나거나 값이 달라졌을때(slope에서는 값이 같아야 하니까!)
                if(!(inside_map(row_num,i+2+j))||runway_map[row_num][i+1+j]!=runway_map[row_num][i+2+j])                  
                    return CANNOT_BUILD;
            }
            for(int j=i+1; j<=i+slope_size; j++) line_check[j] = true; // 라인에 이미 활주로를 건설했으면 올라가는 활주로는 못지으니까!
            // slope size만큼은 체크 완료! !! i를 이용할거면 그 뒤에 i가 +1되는거 잊으면 안됨!!!
            i = i+slope_size-1; // !!!i slope 다 끝나야 가는거네!!
        }else if (runway_map[row_num][i]+1==runway_map[row_num][i+1]){ //// 올라가는건 ""이전이"" 확보되는 체크
            for(int j=0; j<slope_size-1; j++){
                // !!! 이전에는 겹치는게 있는가도 체크해야한다
                if(line_check[i-j]==true||line_check[i-1-j]==true) return CANNOT_BUILD;
                // map에 벗어나거나 값이 달라졌을때
                if(!(inside_map(row_num,i-1-j))||runway_map[row_num][i-j]!=runway_map[row_num][i-1-j])  
                    return CANNOT_BUILD;
                // 여기서는 이전걸 본거니까 i 증가시킬 필요가 없음
            }
            for(int j=i-1; j>=i-slope_size; j--) line_check[j] = true;
        }else if (runway_map[row_num][i]!=runway_map[row_num][i+1]){
            // 완전 3에서 1로 툭 뛰는거면 넘어가야 함!
            return CANNOT_BUILD;
        }

    }
    return CAN_BUILD;
}

bool can_build_line_vertical(int col_num){
    // !!! 겹쳐지는걸 체크해야 하니까 추가함
    fill(&line_check[0],&line_check[MAX_MAP_SIZE],false);
    // row별로 돌면서 체크
    for(int i=0; i<map_size-1; i++){ // 제일 마지막건 체크할 필요 없음  
        if(runway_map[i][col_num]-1==runway_map[i+1][col_num]){ //// 내려가는건 ""이후가"" 확보되는지 체크
            for(int j=0; j<slope_size-1; j++){
                if(!(inside_map(col_num,i+2+j))||runway_map[i+1+j][col_num]!=runway_map[i+2+j][col_num]){
                    return CANNOT_BUILD;
                }  
            }
            for(int j=i+1; j<=i+slope_size; j++) line_check[j] = true;
            // !!!slope 다 끝나야 올리지!
            i = i+slope_size-1; // slope size만큼은 체크 완료! !! i를 이용할거면 그 뒤에 i가 +1되는거 잊으면 안됨!!!
        }else if (runway_map[i][col_num]+1==runway_map[i+1][col_num]){ //// 올라가는건 ""이전이"" 확보되는 체크
            for(int j=0; j<slope_size-1; j++){
                // map에 벗어나거나 값이 달라졌을때
                // !!! 이전에는 겹치는게 있는가도 체크해야한다
                if(line_check[i-j]==true||line_check[i-1-j]==true){
                    return CANNOT_BUILD;
                }  
                // ㅆㅃ 여기서 순서 row col 거꾸로 적응ㅁ
                if(!(inside_map(col_num,i-1-j))||runway_map[i-j][col_num]!=runway_map[i-1-j][col_num])  {
                    return CANNOT_BUILD;
                }  
                // 여기서는 이전걸 본거니까 i 증가시킬 필요가 없음
            }
            for(int j=i-1; j>=i-slope_size; j--) line_check[j] = true;
        }else if (runway_map[i][col_num]!=runway_map[i+1][col_num]){
            // 완전 3에서 1로 툭 뛰는거면 넘어가야 함!
            return CANNOT_BUILD;
        }
        

    }
    return CAN_BUILD;
}

int main(){
    int test_num;
    cin >> test_num;


    for(int t=1; t<=test_num;t++){
        can_build_num = 0;
        cin >> map_size >> slope_size;  

        for (int i=0; i<map_size; i++){
            for (int j=0; j<map_size; j++){
                cin >> runway_map[i][j];
            }    
        }
        // 가로 파악
        for (int i=0; i<map_size; i++){
            if(can_build_line_horizontal(i)==CAN_BUILD){
                can_build_num++;
                // cout << "row: " << i << "\n";
            }
                
        }
        
        // 세로 파악
        for (int i=0; i<map_size; i++){
            if(can_build_line_vertical(i)==CAN_BUILD){
                // cout << "col: " << i << "\n";
                can_build_num++;
            }
            
        }
        cout << "#" << t << " " << can_build_num << "\n";
    }
    
    return 0;

}