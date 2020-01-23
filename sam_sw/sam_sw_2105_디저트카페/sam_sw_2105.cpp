#include <iostream>
#include <vector>
#include <stack>

#define MAX_FRUIT 101 // 1부터 시작해서!
#define DIRECTION_NUM 4
using namespace std;

// 구조체 말고도 tuple(구조체 wrapup 한 것), map, class 도 사용 가능하다.
typedef struct  stack_content {   // 구조체 정의
    pair<int, int> cord;
    int direction_info;
    vector<int> dessert_num; // 먹은 디저트 수
    vector<bool> eat_fruit; 
} stack_content;

pair<int, int> get_next_cord(pair<int, int> curr_cord, int direction){
    if(direction==0) return make_pair(curr_cord.first+1, curr_cord.second+1);
    else if(direction==1) return make_pair(curr_cord.first+1, curr_cord.second-1);
    else if(direction==2) return make_pair(curr_cord.first-1, curr_cord.second-1);
    else if(direction==3) return make_pair(curr_cord.first-1, curr_cord.second+1);
    else return make_pair(0,0); // 나중에 징워야지
}

bool inside_the_wall(pair<int, int> cord, int map_size){
    // !!  계속 양쪽 범위를 생각해야하는데 하나만 생각하네..
    return cord.first<map_size && cord.second<map_size && cord.first>=0 && cord.second>=0;
}

bool dessert_not_exist(vector<bool> dessert, int num){
    return !dessert[num]; 
}

// stack으로 풀어보기
int find_max_route(vector<vector<int> > dessert_map, int map_size){
    // 공용으로 쓸 수 있는 것
    vector< vector<bool> > visited(map_size);
    for(int i=0;i<map_size;i++) visited[i].resize(map_size);

    int max_result = -1;

    pair<int, int> start_cord;
    stack < stack_content > map_stack; // stack에 여러개 넣기

    // stack에 쌓아야 하는 것 으로 쓸 수 있는 것
    pair<int, int> current_cord;
    pair<int, int> next_cord;
    int direction_info;
    vector<int> dessert_num(DIRECTION_NUM, 0); // 각 방향별로 dessert_num을 기록해서 최소한 한번은 움직이고, 0번 1번 넘어가면 똑같이 돌게 만들기
    vector<bool> eat_fruit(MAX_FRUIT, false); 

    for(int i =0; i<map_size-2; i++){ // 두칸 위까지만 돌아가도 된다! 
        for(int j =0; j<map_size-1; j++){ // 제일 오른쪽 건 안들어 가도 된다. 
            start_cord = make_pair(i,j); // 시작점에 돌아왔는지 나중에 확인하기 위함
            // 일단 싹 비우기
            // visited는 통째로 비워야지! 
            // !!! visited는 안써도 되겠다! ㅜㅜ (왜그런지 상술할 것!)
            // !! 앗! fill_n은 begin!!
            // for(int x =0; x<map_size; x++) fill_n(visited[x].begin(), map_size, false); 
            fill_n(eat_fruit.begin(), MAX_FRUIT, false);
            direction_info = 0;
            fill_n(dessert_num.begin(), DIRECTION_NUM, 0);

            // recursion 하듯이 stack에 struct넣기
            // cout << "---" <<  i << " " << j<< "--\n";
            stack_content stack_temp;
            stack_temp.cord = make_pair(i,j);
            stack_temp.direction_info = direction_info;
            stack_temp.dessert_num = dessert_num;
            stack_temp.eat_fruit = eat_fruit;
            map_stack.push(stack_temp); 

            stack_content stack_top;
            while(!map_stack.empty()){ // 시작점으로 갈 수 있는 모든거 다 들여다 보는거 아녀..?
                stack_top = map_stack.top(); // 현재 stack 뽑아내기
                current_cord = stack_top.cord;
                direction_info =  stack_top.direction_info;
                dessert_num = stack_top.dessert_num;
                eat_fruit = stack_top.eat_fruit;
                map_stack.pop();

                int current_dessert_num = dessert_map[current_cord.first][current_cord.second];
                int next_dessert_num;
                // 내가! 방문했는지 확인하기
                // if(visited[current_cord.first][current_cord.second]==false){
                    // 내가 시작점이면서 direction_info ==0 면 visted 체크안해야 다음으로 돌아올수 있을듯
                    // cout << current_cord.first << " " << current_cord.second << "--\n";
                    if(!(direction_info==0&& start_cord.first==current_cord.first && start_cord.second == current_cord.second)){
                        //     visited[current_cord.first][current_cord.second] = true;
                        // 여기 두면 시작점 디저트를 먹어버리면 돌아올 땐 디저트를 이미 먹었으니까 못먹었다고 말한다!(if문 안에 둬야 함!!)
                        eat_fruit[current_dessert_num] = true; // 디저트 종류도 하나 늘겠네!( 겹치는건 이미 stack 넣을 때 안넣음)
                        dessert_num[direction_info]++; // 디저트 한개 더 먹을 수 있겠네!
                    }
                    // 가능성 순회
                    // 방향을 소진하고 이제 나라면!-> 더이상 나아가지 말고 dessert_num 잘 체크하기
                    if(direction_info==3&& start_cord.first==current_cord.first && start_cord.second == current_cord.second){
                        int total_dessert_num = 0;
                        for(int one_d = 0; one_d<DIRECTION_NUM; one_d++) total_dessert_num += dessert_num[one_d]; 
                        if(total_dessert_num>max_result) max_result = total_dessert_num;
                    }else if(direction_info==3){
                        // 3번이면서 도착하지 않으면 그대로 직진!(사실 stack 안쌓고 가도 상관은 없는데)
                        // 그대로 가기
                        next_cord = get_next_cord(current_cord, direction_info);
                        // 방문안하고 벽을 안넘고 먹은 디저트도 아니면 돌리기
                        if(inside_the_wall(next_cord, map_size)){
                            next_dessert_num = dessert_map[next_cord.first][next_cord.second];
                            if(dessert_not_exist(eat_fruit, next_dessert_num)){     // visited[next_cord.first][next_cord.second]==false  && 
                                stack_temp.cord = next_cord;
                                stack_temp.direction_info = direction_info;
                                stack_temp.dessert_num = dessert_num;
                                stack_temp.eat_fruit = eat_fruit;
                                map_stack.push(stack_temp);
                            }
                        }
                    }else if(direction_info==2){// 2번이면 따라가거나 방향 바꾸기!
                        // 아직 번호가 안차면 따라가기
                        if(dessert_num[direction_info]<dessert_num[0]){// 그대로 가기
                            next_cord = get_next_cord(current_cord, direction_info);
                            // 방문안하고 벽을 안넘고 먹은 디저트도 아니면 돌리기
                            if(inside_the_wall(next_cord, map_size)){
                                next_dessert_num = dessert_map[next_cord.first][next_cord.second];
                                if(dessert_not_exist(eat_fruit, next_dessert_num)){     // visited[next_cord.first][next_cord.second]==false  && 
                                    stack_temp.cord = next_cord;
                                    stack_temp.direction_info = direction_info;
                                    stack_temp.dessert_num = dessert_num;
                                    stack_temp.eat_fruit = eat_fruit;
                                    map_stack.push(stack_temp);
                                }
                            }
                        }else{// 다 차면 방향 바꾸기
                            // if(dessert_num[direction_info]>0){ // 이건 필요가 없음!(개수 똑같게 돌아갈테니)
                            next_cord = get_next_cord(current_cord, direction_info+1);
                            if(inside_the_wall(next_cord, map_size)){
                                // 얘를 if문 밖에 뒀었는데 그러면 범위 넘어갈 떄 오류 생긴다!
                                next_dessert_num = dessert_map[next_cord.first][next_cord.second];
                                // 방문안하고 벽을 안넘고 먹은 디저트도 아니면 돌리기
                                if(dessert_not_exist(eat_fruit, next_dessert_num)){ //visited[next_cord.first][next_cord.second]==false  && 
                                    stack_temp.cord = next_cord;
                                    stack_temp.direction_info = direction_info+1;
                                    stack_temp.dessert_num = dessert_num;
                                    stack_temp.eat_fruit = eat_fruit;
                                    map_stack.push(stack_temp);
                                }
                            }
                            // }
                        }   
                    }else{ // 아니면 전체 돌기
                        // 그대로 가기
                        next_cord = get_next_cord(current_cord, direction_info);
                        // 방문안하고 벽을 안넘고 먹은 디저트도 아니면 돌리기
                        if(inside_the_wall(next_cord, map_size)){
                            next_dessert_num = dessert_map[next_cord.first][next_cord.second];
                            if(dessert_not_exist(eat_fruit, next_dessert_num)){     // visited[next_cord.first][next_cord.second]==false  && 
                                stack_temp.cord = next_cord;
                                stack_temp.direction_info = direction_info;
                                stack_temp.dessert_num = dessert_num;
                                stack_temp.eat_fruit = eat_fruit;
                                map_stack.push(stack_temp);
                            }
                        }
                        // 방향 바꾸기(방향 3일때는 더이상 못바꾸고 직진만 가능!)
                        // 그리고 한번은 움직여야 방향 바꿈
                        if(direction_info<3&&dessert_num[direction_info]>0){
                            next_cord = get_next_cord(current_cord, direction_info+1);
                            if(inside_the_wall(next_cord, map_size)){
                                // 얘를 if문 밖에 뒀었는데 그러면 범위 넘어갈 떄 오류 생긴다!
                                next_dessert_num = dessert_map[next_cord.first][next_cord.second];
                                // 방문안하고 벽을 안넘고 먹은 디저트도 아니면 돌리기
                                if(dessert_not_exist(eat_fruit, next_dessert_num)){ //visited[next_cord.first][next_cord.second]==false  && 
                                    stack_temp.cord = next_cord;
                                    stack_temp.direction_info = direction_info+1;
                                    stack_temp.dessert_num = dessert_num;
                                    stack_temp.eat_fruit = eat_fruit;
                                    map_stack.push(stack_temp);
                                }
                            }
                        }
                    }
                    
                }
            }
        }

    return max_result;
}

int main(){
    // 테스트케이스별로 돌리기
    vector<vector<int> > dessert_map;
    int test_num;
    int map_size;
    int max_result;

    cin >> test_num;

    for(int t=0; t<test_num; t++){
        cin >> map_size;

        dessert_map.resize(map_size);
        for(int i=0; i<map_size; i++){
            dessert_map[i].resize(map_size);
            for(int j=0; j<map_size; j++)
                cin >> dessert_map[i][j];
        }

        max_result = find_max_route(dessert_map, map_size);
        cout<< "#" << t+1 << " " << max_result << "\n";
    }

}
