#include <iostream>
#define MAX_SIZE 8
using namespace std;
int N, M;
bool visited[MAX_SIZE+2]; // 1부터 시작하자
int m = 0;

void find_pair(int);

int main() {
    cin >> N >> M;
    
    find_pair(1);
    return 0;
}

void find_pair(int n){
    if(m==M){
        for(int i=1; i<=N; i++){
            if(visited[i]==true){
                cout << i << " ";
            }
        }
        cout << "\n";
        return;
    }else if(n>N){
        return;
    }
    visited[n] = true;
    m++;
    find_pair(n+1);// 범위넘었을떈?
    visited[n] = false;
    m--;
    find_pair(n+1);// 범위넘었을떈?
}
