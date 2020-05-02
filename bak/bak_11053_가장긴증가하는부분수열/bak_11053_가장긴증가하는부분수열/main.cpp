#include <iostream>
#define MAX_SIZE 1000
using namespace std;

int N;

int numbers[MAX_SIZE+2];
int dp[MAX_SIZE+2];
int result = 0;

void find_max_len();

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N;
    for(int i =1; i<=N; i++)
        cin >> numbers[i];
    fill(&dp[0], &dp[N], 0);
    find_max_len();
    cout << result;
    return 0;
}

void find_max_len(){
    for(int idx = 1; idx<=N; idx++){
        int len = 0;
        for(int i = 1; i<idx; i++ ){
            if(numbers[idx] > numbers[i]){
                // 나보다 작은애가 있으면
                // 여기에 +1을 적으면 비교할때마다 비교될듯
                len = max(len, dp[i]);
            }
        }
        dp[idx] = len+1;
        if(dp[idx] > result) result = dp[idx];
    }
}




