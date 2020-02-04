#include <iostream>
#include <algorithm> 
#include <vector>
#include <cmath>
#define SIDE_NUM 4
#define HEX_16 16
using namespace std;
int T, N, K;
string first_shape;
vector <char> box;

int one_hex_to_dec(char c){
    // 16진수 숫자 "한개" 10진수로 바꾸기 F->15
    if(c-'0'>=0&&c-'0'<=9){// 그냥 10진수일 떄
        return c-'0';
    }else{
        return c-'A'+10; // 10을 넘어갈 때
    }
}

int keys_to_dec(vector<char> &keys){
    // keys의 자리수만큼의 16진수를 10진수 수로 바꾸기
    int one_key_len = keys.size();
    int result_dec= 0;
    for(int i=0; i<one_key_len; i++){
        int one_dec = one_hex_to_dec(keys[i]);
        result_dec += one_dec*int(pow(HEX_16,one_key_len-i-1)); // 첫째자리는 16^3
    }
    return result_dec;
}

void keys_to_secret_list(vector<int> &secret_list){
    int one_side_len = N/SIDE_NUM;
    // N개의 key를 4변 길이만큼 잘라서 넣기!
    vector<char> keys(one_side_len); 
    
    for(int i=0; i<box.size(); i++){
        keys[i%one_side_len] = box[i]; 
        if(i%one_side_len == one_side_len-1){ // 한 변에 4개짜리면 0123 데이터 얻고 계산
            int secret_dec = keys_to_dec(keys);
            
            // !! find
            if(find(secret_list.begin(), secret_list.end(), secret_dec) == secret_list.end()){// secret_list에 secret_dec이 없다면
                secret_list.push_back(secret_dec);
            }
            keys.clear(); 
            keys.resize(one_side_len); // !!!clear 하면 사이즈가 없어진다!
        } 
    }
}

void rotate(){
    int last_one = box[N-1];
    for(int i=N-2; i>=0; i--){
        box[i+1] = box[i];
    }
    box[0] = last_one;
}

bool desc(int a, int b){
    return a>b;
}

int find_secret(){
    vector<int> secret_list;
    keys_to_secret_list(secret_list);
    
    // move
    int one_side_len = N/SIDE_NUM;
    for(int ro =1; ro<one_side_len; ro++){
        rotate();
        keys_to_secret_list(secret_list);
    }

    // 내림차순으로!!
    sort(secret_list.begin(), secret_list.end(),desc);
    
    return secret_list[K-1];
}

int main(){
    cin >> T;

    for(int te=1; te<=T; te++){
        cin >> N >> K;
        cin >> first_shape;

        box.resize(N);
        for(int ch=0; ch<N; ch++) box[ch] = first_shape[ch];
        cout << "#" << te << " " << find_secret()<< "\n";
    }

    return 0;
}
