#include <iostream>
#define MAX_SIZE 1000
#define MOD 10007
using namespace std;
int N;
int memoize[MAX_SIZE+2][10];
void find_asc_num();

int main() {
    cin >> N;
    
    if(N==1){
        cout << 10;
    }else{
        for(int i=0;i<10; i++)
            memoize[1][i] = 1; // 첫번째건 다 1로 채우기
        find_asc_num();
    }
    return 0;
}

void find_asc_num(){
    
    for(int n=2; n<=N; n++){
        for(int i=0;i<10;i++){
            int sum = 0;
            for(int digit=i;digit<10; digit++){
                sum = (sum + memoize[n-1][digit])%MOD;
            }
            memoize[n][i] = sum;
        }
    }
    
    // 자리수별로 다 더하기
    int result = 0;
    for(int i=0;i<10;i++){
        result = (result + memoize[N][i])%MOD;
    }
    cout <<result;
}
