#include <iostream>
#include <vector>
#define MAX_SIZE 8
using namespace std;

int N, M;

bool permute_cand_info[MAX_SIZE + 2] = {false};
int num_list[MAX_SIZE + 2];
vector<int> perm_vec;
void get_one_permute(int);


int main() {
    cin >> N >> M;
    for(int i=1; i<=N; i++)
        num_list[i] = i;
    get_one_permute(0);
    
    return 0;
}

// !! 백트래킹인데
void get_one_permute(int cnt){
    if(cnt >= M){
        for(int i=0; i<M; i++){
            cout << perm_vec[i] << " ";
        }
        cout << "\n";
        return;
    }
    
    for(int i=1; i<=N; i++){// !!조합  문제는 이전에 봤던건 더이상 안보는건데 순열은 봤던 애도 다시 본다.
        if(permute_cand_info[i]==true) continue;
        permute_cand_info[i] = true;
        perm_vec.emplace_back(num_list[i]);
        get_one_permute(cnt+1);
        perm_vec.pop_back(); // !!쌓아놓고 빼줘야 백트래킹에 의미가 있다!
        permute_cand_info[i] = false;
    }
}


// !! 문제에 사전순으로 되어 있어야 한다고 함.
// 백트래킹을 다음건 안보는걸로만 생각함
//void get_one_permute_prev(int idx,int current_use){
//    // 종료 조건
//    // 해당 개수보다 안차면 뒤에는 다 채우는걸로!!
//    int selected_num[M];
//    int selected_idx = 0;
//    if(idx > N){
//        // 해당되는 애만 vector에 집어넣기
//        for(int i=1; i<=N; i++){
//            if(permute_cand_info[i]==true){
//                selected_num[selected_idx++] = i;
//            }
//        }
//
//        // permutation
//        do{
//            for(int i=0; i<M; i++)
//                cout << selected_num[i]<< " ";
//            cout << "\n";
//        }while(next_permutation(&selected_num[0], &selected_num[M]));
//        return;
//    }
//
//    // for loop
//    // true로 하고싶을 떄
//    if(current_use<M){
//        permute_cand_info[idx] = true;
//        get_one_permute(idx+1, current_use+1);
//    }
////    if(M-current_use>N-idx){ // !! 무조건 true로 채워야 할 때 빼고!(양 줄ㅇ여보려고 한ㄴ건데.. ㅜㅜ)
//    permute_cand_info[idx] = false;
//    get_one_permute(idx+1, current_use);
////    }
//
//
//}
