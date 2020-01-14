#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

vector <vector <int> > chains;

void rotate_clockwise(int chain_num){
    // 시계방향으로 회전(1)
    // 마지막건 [0]로 가야 하므로 keep
    int last_one = chains[chain_num][7];
    for(int i=7;i>0;i--){
        chains[chain_num][i] = chains[chain_num][i-1];
    }
    chains[chain_num][0] = last_one;
}

void rotate_counter_clockwize(int chain_num){
    // 반시계 방향으로 회전(-1)
    // 제일 앞에건 끝으로 가야하므로 keep
    int first_one = chains[chain_num][0];
    for(int i=0;i<7;i++){
        chains[chain_num][i] = chains[chain_num][i+1];
    }
    chains[chain_num][7] = first_one;
}

int check_out_of_idx(int idx){
    if(idx<0 || idx>3)
        return 1;
    else 
        return 0;
}

int main(){    
    chains.resize(4);
    
    for(int i=0; i<(int)chains.size();i++) chains[i].resize(8);

    string chain_info;

    // chain 정보 얻기
    for(int i=0;i<4;i++){
        cin >> chain_info;
        for(int j=0;j<8;j++){
            chains[i][j] = chain_info[j]-'0';
        }
    }

    int K;
    cin >> K;

    for(int rotate_num=0;rotate_num<K;rotate_num++){
        int chain_num, rotate_direction;
        
        // -99는 아무것도 안들어갔다는 의미
        int rotate_info[4] = {-99,-99,-99,-99}; // !!! rotate 정보를 reset 해줘야지!!(새로 돌리는거니까)
        cin >> chain_num; 
        cin >> rotate_direction;
        chain_num = chain_num-1; // 번호가 1번부터 시작하네!!! 
        
        rotate_info[chain_num] = rotate_direction;
        
        int left_find_idx = chain_num -1; 
        int right_find_idx = chain_num +1; 
        
        // 왼쪽이 끝날때까지(순서대로 확인함) 내가(왼쪽애 말고) 0으로 결정될 때에는 그 이후에는 확인할 필요가 없음
        while(check_out_of_idx(left_find_idx)!=1&&rotate_info[left_find_idx+1]!=0){         
            // 지금꺼랑 왼쪽꺼랑 같은지 확인
            if(chains[left_find_idx+1][6] != chains[left_find_idx][2]){
                // 왼쪽건 반대 방향으로 돌아줘!
                rotate_info[left_find_idx]=rotate_info[left_find_idx+1]*-1;
            }else{
                // 이제 더 안돌아도 된다!
                rotate_info[left_find_idx]=0;
            }
            left_find_idx--;
        }
        
        // 오른쪽이 끝날때까지(순서대로 확인함) 0으로 결정될 때에는 그 이후에는 확인할 필요가 없음
        while(check_out_of_idx(right_find_idx)!=1&&rotate_info[right_find_idx-1]!=0){//
            // 지금꺼랑 오른쪽꺼랑 같은지 확인
            if(chains[right_find_idx-1][2] != chains[right_find_idx][6]){
                // 오른쪽건 반대 방향으로 돌아줘!
                rotate_info[right_find_idx]=rotate_info[right_find_idx-1]*-1;
            }else{
                // 이제 더 안돌아도 된다!
                rotate_info[right_find_idx]=0;
            }
            right_find_idx++;
        }

        // rotate direction에  따라서 회전하기
        for(int i=0;i<4;i++){
            if(rotate_info[i]==1){  
                rotate_clockwise(i);
            }else if(rotate_info[i]==-1){
                rotate_counter_clockwize(i);
            }
        }
    }

    int score = 0;
    for(int i=0;i<4;i++){
        score += chains[i][0]*(int)pow((double)2,(double)i);
    }
    cout << score;

    return 0;
}