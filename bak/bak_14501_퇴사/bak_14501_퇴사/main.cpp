#include <iostream>
#define MAX_CUSTOMER 15

using namespace std;

// struct 편하게 만들어지는거 다시 복습
// -> a = customer{2,3} 이런식으로 넣을 수 있음
typedef struct customer{
    int date;
    int profit;
} customer;

customer customer_info[MAX_CUSTOMER + 2];
int N;
int max_profit;
void explore(int idx, int profit);
void find_max_profit();

int main() {
    cin >> N;
    // 예제 되어있는대로 하자... ㅜㅜ 번호 1부터
    for (int i=1; i<=N; i++){
        cin >> customer_info[i].date >> customer_info[i].profit;
    }
    find_max_profit();
    cout << max_profit;
    return 0;
}

void find_max_profit(){
    for(int i=1; i <=N; i++){
        int profit = 0;
        explore(i, profit);
    }
}

// ~~dfs를 현재로 할거냐 미래로 할거냐 있을 수 있는데, 현재로 해야지!
void explore(int idx, int profit){
    // ~~ 끝날 떄 조건은 제일 앞에
    if(idx > N){
        if(profit>max_profit) max_profit= profit; // !! ㅋㅋ 끝나고 나서 해야된다.
    }
    // ~~ 백트래킹이라면, 보통 dfs에서는 for loop 가 있겟지
    // 이 문제에서 for loop는 스킵하고 넘기는 개념
    for(int ch_idx = idx; ch_idx<= N; ch_idx++){ // !! 여기서도 돌아가는거 만들어야지
        int next_date = ch_idx + customer_info[ch_idx].date;
        // ~~ 경계 이내의 것은 그대로 계산하면 됨.
        if(next_date<=N+1){// 상담 끝나는 날이 퇴사일이 아니라면(퇴사일이 다음 일이면 안잡으면 되니까! =붙이기
            explore(next_date, profit + customer_info[ch_idx].profit);
        }else{
            // ~~ !! 보통은 경계를 넘고 종료하는데 그 경계를 넘으려 할 때 아무것도 안하는게 중요하다
            explore(next_date, profit);
        }
    }
}
