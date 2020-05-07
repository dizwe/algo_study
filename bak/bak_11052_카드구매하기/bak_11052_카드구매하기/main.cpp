#include <iostream>
#define MAX_SIZE 1000
using namespace std;

int N;
int card[MAX_SIZE+2];
double card_q[MAX_SIZE+2];
int dp[MAX_SIZE+2];

int main() {
    cin >> N;
    int max = 0;
    int max_i = 1;
    for (int i=1;i<=N; i++){
        cin >> card[i];
        card_q[i] = (double)card[i]/(double)i;
        if(card_q[i]>max){
            max = card_q[i];
            max_i = i;
        }
        dp[i] = max_i;
    }
    
    // 최대 index 채우기
    int card_left = N;
    int result = 0;
    while(card_left >0){
        result += card[dp[card_left]];
        card_left = card_left-dp[card_left];
    }
    
    cout << result;
    
    return 0;
}
