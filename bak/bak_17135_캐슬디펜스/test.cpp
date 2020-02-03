#include <iostream>
#define MAX_W 12
#define MAX_H 15
using namespace std;

typedef struct que_content { 
    int shoot_num;
    int blocks[MAX_H][MAX_W]; // ?? 왜 이렇게 하고 que_elem.blocks= blocks; 하면 오류나지??
} que_content;

int init_blocks[MAX_H][MAX_W]; // 처음 블록 모양

int main(){
    int N, W, H;
    cin >> N >> W >> H;
    int result;
    for(int r=0;r<H;r++){
        for(int c=0;c<W;c++){
            cin >> init_blocks[r][c];
        }
    }

    que_content que_elem;
    int init_blocks[MAX_H][MAX_W]; // 처음 블록 모양
    que_elem.blocks= init_blocks; // 수정할 수 있는 lvalue여야 한다고 말한다...
    return 0;
}