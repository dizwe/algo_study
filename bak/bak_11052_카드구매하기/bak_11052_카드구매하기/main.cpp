#include <iostream>
#define MAX_SIZE 1000
using namespace std;

int N;
int card[MAX_SIZE+2];
int dp[MAX_SIZE+2];

int main() {
    cin >> N;
    for (int i=1;i<=N; i++){
        cin >> card[i];
        dp[i] = card[i]; // f(n) 전체적으로 다 쓰는 방법은 따로 저장해두기
    }
    
    for(int n=2; n<=N; n++){
        for(int i=1; i<n; i++){ // !!dp도 2차원 가능하다!
            dp[n] = max(dp[n], dp[n-i]+card[i]);
        }
    }
    
    cout << dp[N];
    
    return 0;
}
