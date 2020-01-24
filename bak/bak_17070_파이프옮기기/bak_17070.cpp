#include <iostream>
#include <queue>
#define HOUSE_MAX_SIZE 16
#define HORIZONTAL 0
#define VERTICAL 1
#define DIAGONAL 2
#define INSIDE_HOUSE true
#define NO_WALL true

using namespace std;

typedef struct que_content{
    pair<int, int> cord;
    int direction;
} que_content;

int house[HOUSE_MAX_SIZE+1][HOUSE_MAX_SIZE+1]; // 1번부터 시작하게 채울거니까
que_content que_elem;
queue<que_content> que;
int result=0;


// bfs로 데이터 찾기
int bfs(int);
bool inside_house();
bool inside_house(pair <int, int> cord, int house_size);
bool check_no_wall(pair <int, int> cord, int direction);
void check_and_push(pair <int, int> cord, int house_size, int direction);

int main(){
    int house_size;
    
    // array fill 하는 방법
    fill(&house[0][0], &house[HOUSE_MAX_SIZE][HOUSE_MAX_SIZE],0);
    cin >> house_size;

    for(int i=1; i<house_size+1;i++){
        for(int j=1;j<house_size+1; j++){
            cin >> house[i][j];
        }
    }

    // bfs로 search
    int result = bfs(house_size);
    cout <<result;
    return 0;
}

bool inside_house(pair <int, int> cord, int house_size){
    return cord.first <= house_size && cord.second <=house_size;
}

bool check_no_wall(pair <int, int> cord, int direction){
    // 옮길 미래의 좌표 기준으로 체크
    // 가로, 세로는 그냥 한칸만 체크
    if(direction==HORIZONTAL||direction==VERTICAL)
        return house[cord.first][cord.second]!=1; 
    else
        return house[cord.first][cord.second]!=1
        && house[cord.first-1][cord.second]!=1 
        && house[cord.first][cord.second-1]!=1;// 대각선은 여러개 체크
}

void check_and_push(pair <int, int> cord, int house_size, int direction){
    if(inside_house(cord, house_size)==INSIDE_HOUSE&&check_no_wall(cord, direction)==NO_WALL){
        if(cord.first == house_size&& cord.second == house_size){ 
            // 도착지에 나아갔으면 que에 넣을 필요 없음 가능성 있는 애 개수 늘리기
            result++;
        }else{
            // !!! 여기에서도 que_elem을 쓰면 que_elem이 전역이니까 같이 증가하지!
            que_content will_push_que_elem;
            will_push_que_elem.cord = cord;
            will_push_que_elem.direction = direction;
            que.push(will_push_que_elem);
        }
    }  
}

int bfs(int house_size){
    pair <int, int> current_cord = make_pair(1,2); // 파이프 끝이 가르키는 첫 좌표
    pair <int, int> next_cord; // 가능성의 좌표들
    int current_dir = HORIZONTAL;
    que_elem.cord = current_cord;
    que_elem.direction = current_dir;
    que.push(que_elem);
    while(!que.empty()){
        que_elem = que.front();
        que.pop();
        // 가능성 있는것들 다 넣기
        current_cord = que_elem.cord;
        // BFS 에서는 push를 next에서 한다.
        // 대각선이거나 가로 일때 가로 가능ㅇㅇ
        if(que_elem.direction ==HORIZONTAL || que_elem.direction ==DIAGONAL){
            next_cord = make_pair(que_elem.cord.first, que_elem.cord.second+1);
            // 벽이거나 주변이 1인지 확인하고 push
            check_and_push(next_cord, house_size,HORIZONTAL);
        }
        // 대각선이거나 세로 일때 세로 가능ㅇㅇ
        if(que_elem.direction ==VERTICAL || que_elem.direction ==DIAGONAL){
            //벽이거나 주변이 1인지 확인
            next_cord = make_pair( que_elem.cord.first+1, que_elem.cord.second);
            // 벽이거나 주변이 1인지 확인하고 push
            check_and_push(next_cord, house_size, VERTICAL);
        }
        // 대각선은 무조건 테스트!
        next_cord = make_pair( que_elem.cord.first+1, que_elem.cord.second+1);
        //벽이거나 주변이 1인지 확인
        check_and_push(next_cord, house_size, DIAGONAL);
    }
    return result;
}