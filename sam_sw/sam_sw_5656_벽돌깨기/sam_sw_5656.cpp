#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#define MAX_W 12
#define MAX_H 15
#define ROW 0
#define COL 1
#define INSIDE_MAP true
#define OUTSIDE_MAP false

using namespace std;

int init_blocks[MAX_H][MAX_W]; // 처음 블록 모양
int N, W, H;
int min_result = INT_MAX; // 일단 int_max로 잡기

typedef struct que_content { 
    int shoot_num;
    // int blocks[MAX_H][MAX_W]; // ?? 왜 이렇게 하고 que_elem.blocks= blocks; 하면 오류나지??
    int** blocks;
} que_content;

int direction[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};

// 외않되?
// vector<pair<int, int> > direction;
// direction.push_back(make_pair(0,1));
// direction.push_back(make_pair(1,0));
// direction.push_back(make_pair(0,-1));
// direction.push_back(make_pair(-1,0)); // 동 남 서 북

bool inside_map(int r, int c);

void explode(int start_row, int start_col, bool already_explode[][MAX_W], int** blocks);

void rearrange(int** blocks);

void shoot(int block_col_cord, int** blocks);

int get_left_block_num(int** blocks);

// bfs로 찾기
int find_min_left_block();


int main(){
    cin >> N >> W >> H;
    int result;

    for(int r=0;r<H;r++){
        for(int c=0;c<W;c++){
            cin >> init_blocks[r][c];
        }
    }

    // !!! 매번 할때마다 rearrage 해줘야 그 이후에 것들이 내려가고 파괴되지 않는다/
    result = find_min_left_block();
    cout << result;
    
    return 0;
}

bool inside_map(int r, int c){
    if(r>=0 && c>=0 && r<H && c<W) return INSIDE_MAP;
    else return OUTSIDE_MAP;
}
// !! ROW, COL W,H 다룰떄 조심해야 한다 ㅜㅜ 정말 헷갈리거든 아예 변수를 r,c로 하고 row, col으로 대칭시켜주자
// W, H 도 받고나서 R, C로 바꿔줘도 좋을듯
// 이차원??->!!! malloc 해서 얻으면 어떻게 전달행야 되는거지?????? new 사용한다면 _> test
void explode(int start_row, int start_col, bool already_explode[][MAX_W], int** blocks){ // 좌표 입력
    // 일단 나는 터진다!
    already_explode[start_row][start_col] = true;
    int explode_power = blocks[start_row][start_col];
    blocks[start_row][start_col] = 0; // 빵 터졌으니까 얘는 지워도 된다!
    
    // 상하좌우 
    for(int i=0; i<4; i++){
        // 길이만큼 빵빵!
        for(int one_power=1; one_power<=explode_power-1; one_power++){// 1이면 나만 빵빵! -> 그래서 -1
            int next_row = start_row + one_power*direction[i][ROW];
            int next_col = start_col + one_power*direction[i][COL];
            
            // 한번 outside_map 되면 굳이 그 방향으로 power 더 나갈 필요 없음
            if(inside_map(next_row, next_col)==OUTSIDE_MAP) break; 
            
            // 아니면 진행
            if(inside_map(next_row, next_col)==INSIDE_MAP&&!already_explode[next_row][next_col]){
                explode(next_row, next_col, already_explode, blocks);
            }
        }
    }
}

void rearrange(int** blocks){
    for (int c=0; c<W; c++){
        int new_col[H];
        fill(&new_col[0], &new_col[H], 0);
        int non_zero_num = 0; 
        // 일단 0 아닌거 모으기(블럭을 반대로 쌓아야 된다!)
        for(int r=H-1; r>=0; r--){
            if(blocks[r][c]!=0){
                new_col[H - 1 - non_zero_num] = blocks[r][c];
                non_zero_num++;
            } 
        }
        // 0 아닌거 쫙 뿌리기
        for(int r=0; r<H; r++)
            blocks[r][c] = new_col[r];
    }
}
// xy보다 col, row로 표현하자
void shoot(int block_col_cord, int** blocks){
    // 0이 아닌 첫번째 블록 찾기
    for(int row_i = 0; row_i<H; row_i++){
        if(blocks[row_i][block_col_cord]!=0){ 
            bool already_explode[MAX_H][MAX_W]; // 약간 visited 같은 것 
            fill(&already_explode[0][0], &already_explode[MAX_H-1][MAX_W], false); 
            explode(row_i, block_col_cord, already_explode, blocks); 
            break; 
        }
    }
}

int get_left_block_num(int **blocks){
    int block_num = 0;
    for(int r=0;r<H;r++){
        for(int c=0;c<W;c++){
            if(blocks[r][c]!=0) block_num++;
        }
    }
    return block_num;
}

// bfs로 찾기
int find_min_left_block(){
    queue<int, int**> que;
    que_content que_elem;
    //block new 해서 옮기기 나중에 free 해주자
    int ** queue_blocks = new int*[H];
    for(int i=0; i<H; i++) queue_blocks[i] = new int[W];
    for(int i=0; i<H; i++)
        for(int j=0; j<W; j++)
            queue_blocks[i][j] = init_blocks[i][j];
    

    que_elem.shoot_num = 0;
    que_elem.blocks= queue_blocks;
    que.push(que_elem);
    // 처음에 개수 체크??

    while(!que.empty()){
        que_elem = que.front();
        que.pop();
        if(que_elem.shoot_num<N){
            que_content next_que_elem;
            for(int c=0; c<W; c++){ // column 크기만큼 돌면서 체크
                int ** queue_blocks = new int*[H];
                for(int i=0; i<H; i++) queue_blocks[i] = new int[W];
                for(int i=0; i<H; i++)
                    for(int j=0; j<W; j++)
                        queue_blocks[i][j] = que_elem.blocks[i][j];
                shoot(c,queue_blocks);
                rearrange(queue_blocks); // 이러면 주소값이 가는거라 따로따로 관리가되려나?? -> 아예 복사를 해줘야 할듯?

                next_que_elem.shoot_num = que_elem.shoot_num+1;
                next_que_elem.blocks = queue_blocks;
                que.push(next_que_elem);
            }
        }else if(que_elem.shoot_num==N){ // shoot 다 끝나면
            int result = get_left_block_num(que_elem.blocks);
            if(result<min_result) min_result= result;
        }

        // 다 끝나고 pop한거 free
        for(int i = 0; i < H; ++i) { delete [] que_elem.blocks[i]; } 
        delete [] que_elem.blocks;
    }
    
}


