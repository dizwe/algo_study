#include <iostream>
#define DEC_NUM 10
#define MAX_NUM 100
#define MOD 1000000000
using namespace std;
int N;
int num_info[MAX_NUM+2][DEC_NUM] ={0}; // 1부터 시작/ 0~9

void find_stair_num(int );
int main() {
    cin >> N;
    num_info[1][0] = 0;
    for(int i=1; i<=9; i++) num_info[1][i] = 1;
    
    if(N==1) cout << 9;
    else find_stair_num(2); //2부터 차근차근 올라가자유
    return 0;
}

void find_stair_num(int n){
    // 현째인지 나중인지, 나인지 남인지 잘 파악하자..ㅜㅜㅜㅜ (num_info[n-1][i]를 했었음 전부다
    for(int i=0; i<DEC_NUM; i++){
        if(i==0){
            num_info[n][0] += num_info[n-1][1];
        }else if(i==9){
            num_info[n][9] += num_info[n-1][8];
        }else{
            num_info[n][i] += (num_info[n-1][i-1] + num_info[n-1][i+1])%MOD;
        }
    }
    if(n==N){
        int total_num = 0;
        for(int i=0; i<DEC_NUM; i++)
            total_num = (total_num + num_info[n][i])%MOD;
        cout << total_num;
    }else{
        find_stair_num(n+1);
    }
}
