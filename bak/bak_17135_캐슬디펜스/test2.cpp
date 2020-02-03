#include <iostream>
#include <algorithm>
#define MAX_N 15
#define MAX_M 15

using namespace std;
int N, M, D;

// input
// 5 5 1
// 0 0 0 0 0
// 0 0 0 0 0
// 0 0 0 0 0
// 0 0 0 0 0
// 1 1 1 1 1


void attack1(int castle_map2[MAX_N][MAX_M]){
    castle_map2[2][2]=22;
}

void attack2(int (&castle_map1)[MAX_N][MAX_M]){
    castle_map1[3][3]=33;
}


int main(){
    cin >> N >> M >> D;
    int castle_map[MAX_N][MAX_M];
    for(int r =0; r<N; r++)
        for(int c=0; c<M; c++)
            cin >> castle_map[r][c];
    attack1(castle_map); // int castle_map[MAX_N][MAX_M];를 넘기지 않는다.
    cout << "\n";
    for(int r =0; r<N; r++){
        for(int c=0; c<M; c++){
            cout << castle_map[r][c] << " ";
        }
        cout << "\n";
    }
    attack2(castle_map); // int castle_map[MAX_N][MAX_M];를 넘기지 않는다.
    cout << "\n";
    for(int r =0; r<N; r++){
        for(int c=0; c<M; c++){
            cout << castle_map[r][c] << " ";
        }
        cout << "\n";
    }
    return 0;
}

