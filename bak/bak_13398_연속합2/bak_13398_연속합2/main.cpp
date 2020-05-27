#include <iostream>
#define MAX_NUM 100000
using namespace std;

int N;
int num[MAX_NUM+2];
// 하나는 그대로 썼을때, 하나는 취소했을때 최대값
int sum[2][MAX_NUM+2];


int main(int argc, const char * argv[]) {
    cin >> N;
    
    for(int i=0; i<N; i++){
        cin >> num[i];
    }
    
    sum[0][0] = num[0];
    sum[1][0] = num[0];
    int max_sum = sum[0][0];
    
    for(int i=1; i<N; i++){
        // sum [0] 채우기
        sum[0][i] = max(num[i], sum[0][i-1] + num[i]);
        // sum [1] 채우기
        // 이떈 연속된 [0] 데이터를 참고해야 함 sum[0][i-1]
        // (그럼으로써 1번만 딱! 된다는 걸 보장 가능
        // sum[1][i-1] + num[i]
        // 나머지는 연속으로!
        sum[1][i] = max(sum[0][i-1], sum[1][i-1] + num[i]);
        if(max_sum <max(sum[0][i], sum[1][i])){
            max_sum = max(sum[0][i], sum[1][i]);
        }
    }
    
    cout << max_sum;
    
    return 0;
}
