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
        for(int j =1; j<map_size-1; j++){ // 제일 오른쪽 건 안들어 가도 된다. 
            start_cord = make_pair(i,j); // 시작점에 돌아왔는지 나중에 확인하기 위함
            // 일단 싹 비우기
            // !! 앗! fill_n은 begin!!
            fill_n(eat_fruit.begin(), MAX_FRUIT, false);
            direction_info = 0;
            fill_n(dessert_num.begin(), DIRECTION_NUM, 0);

            // recursion 하듯이 stack에 struct넣기
            stack_content stack_temp;
            stack_temp.cord = make_pair(i,j);
            stack_temp.direction_info = direction_info;
            stack_temp.dessert_num = dessert_num;
            stack_temp.eat_fruit = eat_fruit;
            map_stack.push(stack_temp); 

            stack_content stack_top;
            while(!map_stack.empty()){ 
                stack_top = map_stack.top(); // 현재 stack 뽑아내기
                current_cord = stack_top.cord;
                direction_info =  stack_top.direction_info;
                dessert_num = stack_top.dessert_num;
                eat_fruit = stack_top.eat_fruit;
                map_stack.pop();

                int current_dessert_num = dessert_map[current_cord.first][current_cord.second];
                int next_dessert_num;

                //시작점 디저트를 먹어버리면 돌아올 땐 디저트를 이미 먹었으니까 못먹었다고 말한다!(if문 안에 둬야 함!!)
                if(!(direction_info==0&& start_cord.first==current_cord.first && start_cord.second == current_cord.second)){
                    eat_fruit[current_dessert_num] = true; // 디저트 종류도 하나 늘겠네!( 겹치는건 이미 stack 넣을 때 안넣음)
                    dessert_num[direction_info]++; // 디저트 한개 더 먹을 수 있겠네!
                }

                // 가능성 순회
                if(direction_info==2){ // 이제 방향이 2번이라면 끝까지 0,1번 정보대로 걷기
                    // 2번 방향으로 걷기 0번 방향 개수 참고해서!
                    bool avail = true; // 가다가 벽 넘어간다거나 이미 있던 디저트 먹거나 하진 않았니?
                    while(dessert_num[direction_info]<dessert_num[0]) {
                        // 이미 위에서 eat_fruit된건 가능하다고 체크된거야!
                        current_cord = get_next_cord(current_cord, direction_info);
                        // 만나는 중에 벽 만났으면 그냥 그만둬도 됨!(있는 정보대로 가야하는데 못가는거니까)
                        if(inside_the_wall(current_cord, map_size)){
                            current_dessert_num = dessert_map[current_cord.first][current_cord.second];
                            if(dessert_not_exist(eat_fruit, current_dessert_num)){
                                // cout << "current" <<  current_cord.first << " " << current_cord.second << "--\n";
                                eat_fruit[current_dessert_num] = true;
                                dessert_num[direction_info]++; 
                            }else{
                                avail = false;
                                break;
                            }
                        }else{
                            avail=false;
                            break;
                        }

                    }
                    // 3번 방향으로 걷기
                    direction_info++;
                    while(dessert_num[direction_info]<dessert_num[1]&&avail) {
                        // 이미 위에서 eat_fruit된건 가능하다고 체크된거야!
                        current_cord = get_next_cord(current_cord, direction_info);
                        
                        // 만나는 중에 벽 만났으면 그냥 그만둬도 됨!
                        if(inside_the_wall(current_cord, map_size)){
                            current_dessert_num = dessert_map[current_cord.first][current_cord.second];
                            if(dessert_not_exist(eat_fruit, current_dessert_num)){
                                eat_fruit[current_dessert_num] = true;
                                dessert_num[direction_info]++; 
                            }else{
                                avail = false;
                                break;
                            }
                        }else{
                            avail=false;
                            break;
                        }
                    }
                    // 다 돌고 정보 확인하기
                    if(start_cord.first==current_cord.first && start_cord.second == current_cord.second && avail){
                        int total_dessert_num = 0;
                        for(int one_d = 0; one_d<DIRECTION_NUM; one_d++) total_dessert_num += dessert_num[one_d]; 
                        if(total_dessert_num>max_result) max_result = total_dessert_num;
                        // if(max_result >= (map_size-1)*2) return max_result; // 바로 끝내버리기 -> 별로 효과없음
                    }
                }else{ // 0번, 1번에서는 그냥 돌기
                    // 그대로 가기
                    next_cord = get_next_cord(current_cord, direction_info);
                    // 방문안하고 벽을 안넘고 먹은 디저트도 아니면 돌리기
                    if(inside_the_wall(next_cord, map_size)){
                        next_dessert_num = dessert_map[next_cord.first][next_cord.second];
                        if(dessert_not_exist(eat_fruit, next_dessert_num)){  
                            stack_temp.cord = next_cord;
                            stack_temp.direction_info = direction_info;
                            stack_temp.dessert_num = dessert_num;
                            stack_temp.eat_fruit = eat_fruit;
                            map_stack.push(stack_temp);
                        }
                    }
                    // 방향 바꾸기
                    // 한번은 움직여야 방향 바꿈
                    if(dessert_num[direction_info]>0){
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
