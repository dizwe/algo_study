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

void explore(int idx, int profit){
    if(idx > N){
        if(profit>max_profit) max_profit= profit; // !! ㅋㅋ 끝나고 나서 해야된다.
    }
    for(int ch_idx = idx; ch_idx<= N; ch_idx++){ // !! 여기서도 돌아가는거 만들어야지
        // 현재로 할건지 다음으로 할건지 정해야지!! 근데 현재로 하는게 더 직관적
        int next_date = ch_idx + customer_info[ch_idx].date;
        if(next_date<=N+1){// 상담 끝나는 날이 퇴사일이 아니라면(퇴사일이 다음 일이면 안잡으면 되니까! =붙이기
            explore(next_date, profit + customer_info[ch_idx].profit);
        }else{
            explore(next_date, profit);
        }
    }
}
