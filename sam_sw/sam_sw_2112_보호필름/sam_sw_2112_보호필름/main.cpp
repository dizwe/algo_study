#include <iostream>
#include <vector>
#include <cstring>
#include <climits>
#define EMPTY 99
#define PASS true
#define MAX_WIDTH 20 + 1
#define MAX_DEPTH 13 + 1
using namespace std;

int DEPTH, WIDTH, K;
bool find_or_not = false;
//vector<vector <short> > film;
//vector<vector <short> > film_test;
short film[MAX_DEPTH][MAX_WIDTH];
short film_test[MAX_DEPTH][MAX_WIDTH];
short med_info[MAX_DEPTH]; // 몇번 약을 썼는지도 적어줘야 함
int min_med = INT_MAX;
void find_min_med(int med_max_num, int current_idx, int current_med_num);

bool check_film();
// 보통 딱 마지막거 하나 틀렸으면 그건 기초적인거 하나 빠진거래!
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for(int t=1;t<=T;t++){
        cin >> DEPTH >> WIDTH >> K;
        
        for(int d =0; d<DEPTH; d++){
            for(int w =0; w<WIDTH; w++){
                cin >> film[d][w];
                film_test[d][w] = film[d][w];
            }
        }
        
        // !! 처음에 0이 계속 거슬리는거니까 따로 체크
        if(K==1||check_film()==PASS){
            cout<< "#" << t << " " << 0 << "\n";
        }else{
            // 처음에 resize
            fill(&med_info[0], &med_info[MAX_DEPTH] , EMPTY);
//            memset(med_info, EMPTY, sizeof(med_info));
            find_min_med(K,0,1);
            cout<< "#" << t << " " << min_med << "\n";
        }
        // memset 하면 안됨!-> 길원 설명 보기
        fill(&film[0][0], &film[MAX_DEPTH-1][MAX_WIDTH] , EMPTY);
        fill(&film[0][0], &film[MAX_DEPTH-1][MAX_WIDTH] , EMPTY);
        fill(&med_info[0], &med_info[MAX_DEPTH] , EMPTY);
        min_med = INT_MAX;
    }
    return 0;
}


// med_num이 for loop돌면서 늘어나는 컨셉!
// 여기 백트래킹의 문제 : 완전 깊이 들어가면서 하나씩 빼는게 아니라 거기의 index도 조정되어야 한다..
void find_min_med(int med_max_num, int current_idx, int current_med_num){
    // !! EMPTY를 한 원소로 했을때 생기는 문제: 0을 굳이 체크할 필요가 있나..?(0 99 는 이미 한번 체크 한건데 또 체크하는 문제 생김)
    // 시작점 조절하는
    // !! recursion으로 안하고 이렇게 하면 중복은 없어지곗지?
    for(int idx=current_idx;idx<DEPTH;idx++){
        for(int med =0; med<=1;med++){
            // med_num 개수만큼 늘릴 수 있게
            med_info[idx] = med;
            // med_info에 따라 film 바꾸기
            for(int c=0; c<WIDTH; c++)
                film_test[idx][c] = med;

            // 깊이 테스트
            if(check_film() == PASS && current_med_num<min_med){
                min_med=current_med_num;
            }else{
                // next_med_num가 min_medㅂ다 커지면 사실 할 필요도 없다.
                if(current_med_num+1<min_med)
                    find_min_med(med_max_num, idx+1, current_med_num+1);
            }
            
            // med_num 개수만큼 늘릴 수 있게
            med_info[idx] = EMPTY;
            // 다시 되돌리기
            for(int c=0; c<WIDTH; c++)
                film_test[idx][c] = film[idx][c];
        }
    }
        
}

bool check_film(){
    // 처음걸로 찾기
    
    // column 별로 움직이기 -> 하나라도 안된다면 not pass
    for(int c=0; c<WIDTH; c++){
        short prev_cell = film_test[0][c];
        int conseq_num = 1;
        for(int r=1; r<DEPTH; r++){
            if(prev_cell==film_test[r][c]){
                conseq_num++;
                if(conseq_num>=K) break;
            }else{
                conseq_num = 1; // 아예 새로 시작되는게 1부터 시작됨
            }
            prev_cell = film_test[r][c];
        }
        if(conseq_num<K) return !PASS;
    }
    
    return PASS;
}



//// med_num이 for loop돌면서 늘어나는 컨셉!
//void find_min_med3(int med_max_num, int current_idx, int current_med_num,int med){
//    if(find_or_not==true) return; // !!recursion 돌다가 다 끝나면 끝내야지!
//    // med_num 개수만큼 늘릴 수 있게
//    med_info[current_idx] = med;
//    // med_info에 따라 film 바꾸기
//    for(int c=0; c<WIDTH; c++)
//        film_test[current_idx][c] = med;
//
//    // 합격하는지 확인하기
//    // 딱 그 개수일때만 체크하면 되잖아
//    if(current_med_num==med_max_num&&check_film()==PASS){ // 합격 하면 break
////        cout << med_max_num;
//        // !! recursion에서 find를 return 하면 문제 있겠지?
//        // current_med_num 계산
//        // !!여기서 문제 깊이 먼저 들어가니까 또 문제 생김
//        find_or_not = true;
//        return;
//    }else{ // 합격 안하면 K보다 작으면 한 depth 더해서 확인하기
//        // med_num까지는 recursion 돌면서 체크!
//        // 모든 값이 다 이상하게 가지는 않는지 확인하자!!!! (특히 값이 증가하는것들)
//        if(current_med_num < med_max_num && current_idx<DEPTH-1){
//            find_min_med(med_max_num, current_idx+1, current_med_num+1, 0);
//            find_min_med(med_max_num, current_idx+1, current_med_num+1, 1);
//        }
//
//    }
//
//    // 안되면 다음거!
//    med_info[current_idx] = EMPTY;
//    // 원래대로 되돌리기
//    for(int c=0; c<WIDTH; c++)
//        film_test[current_idx][c] = film[current_idx][c];
//    // 그러고 다음 idx로 항해~~
//    // 얘는 med_num 자체는 안느니까 그대로!
//    if(current_idx+1<DEPTH){
//        find_min_med(med_max_num, current_idx+1, current_med_num, 0);
//        find_min_med(med_max_num, current_idx+1, current_med_num, 1);
//    }
//
//}
//
//
//void find_min_med2(int med_num, int current_idx, int med){
//    // 약 몇개 넣어야 하는지 체크
//    // !! K보다 크면 확인할 필요도 없다 왜냐하면 둘이 붙여서 만들면 무조건 합격할테니까
//        // for loop는 필요없겠다! recursion 자체가 loop 역할을 하겠다
//        // for(int med_num=0; med_num<=K;med_num++){
//    // med_info 바꾸기 0일떄는 바꿀 필요가 없어서
//
//    med_info[current_idx] = med;
//    // med_num++; recursion 할 떄 줄이니까 다시 넣기
//    // med_info에 따라 film 바꾸기
//    for(int c=0; c<WIDTH; c++)
//        film_test[current_idx][c] = med;
//
//    // 합격하는지 확인하기
//    if(check_film(film_test)==PASS){ // 합격 하면 break
//        cout << med_num;
//        return;
//    }else{ // 합격 안하면 K보다 작으면 한 depth 더해서 확인하기
//        // med_num 1개 느는거니까 는다고 체크!
//        // !!! 악!!! 이런식으로 하면 최소 개수를 알 수 있는게 아니네...(그냥 답 찾기만 하는 느낌?)
//        // num 늘리는걸 우선으로 하면 안되겠네
//        // if(med_num < K)
//        //     find_min_med(med_num+1, current_idx+1, med);
//
//        // 다 안되면 이 번호는 아니니까 빼기(그 이후에는 체크 안하는게 포인트!
//        med_info[current_idx] = EMPTY;
//        // 원래대로 되돌리기
//        for(int c=0; c<WIDTH; c++)
//            film_test[current_idx][c] = film[current_idx][c];
//        // 그러고 다음 idx로 항해~~
//        // 얘는 med_num 자체는 안느니까 그대로!
//        if(current_idx+1<DEPTH)
//            find_min_med2(med_num, current_idx+1, med);
//    }
//
//    // 개수 늘린 상태로 recursion 돌게 하기
//    if(med_num < K){
//        find_min_med2(med_num+1, 0, med);
//    }
//}
