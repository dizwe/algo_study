#include <iostream>
#include <vector>
#include <algorithm>
#define PERSON_NUM 9
#define GROUND_NUM 4

using namespace std;
int INNING_NUM;

int max_score = 0;
void find_max_score(vector<vector <int> > & person_info);

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> INNING_NUM;
    
    // ?? vector<int> each_person_total[PERSON_NUM+1] 이렇게 하면 안되나?? begin end 안됨
    vector<vector <int> > person_info;
    person_info.resize(INNING_NUM+1);
    vector<int> each_person_total; // 일부러 전부 0인거 나중에 사용할 수 있도록!
    each_person_total.resize(PERSON_NUM+1);
    fill(each_person_total.begin(), each_person_total.end(), 0);
    
    for(int inning =1; inning<=INNING_NUM; inning++){
        person_info[inning].resize(PERSON_NUM+1);
        for(int person=1; person<=PERSON_NUM; person++){
            int one_person_info;
            cin >> one_person_info;
            person_info[inning][person] = one_person_info;
            each_person_total[person] += one_person_info;
        }
    }
    
    find_max_score(person_info);
    cout << max_score;

}

void find_max_score(vector<vector <int> > & person_info){
    vector<int> cand_list;
    // empalce_back 할거면 resize 하면 안된다고!!
    //cand_list.resize(PERSON_NUM-1);
    vector<int> real_cand_list; // 1번도 추가된 cand_list
    
    
     real_cand_list.resize(PERSON_NUM+1);
    //1번은 빠진 상태로 permutation 돌리기
    for(int cand=2; cand <= PERSON_NUM; cand++) cand_list.emplace_back(cand);
//    cout << cand_list.size();
//    for(int a =0; a<cand_list.size();a++) cout<< cand_list[a];
//    cout << "\n";
    
    do{
        vector<int> ground_info;
        ground_info.resize(GROUND_NUM+1,0); // !! 0으로 채워넣기(들어갈 수 있는 홈-> ground 한 칸씩 !!! 시작하는 점과 돌아오는 점이 같은 점이지만 따로 구분
        int out_num = 0;
        // 일단 4 추가한 상태로 데이터 넣기
        for(int i=1; i<=PERSON_NUM; i++){
            if(i<4){
                real_cand_list[i] = cand_list[i-1];
            }else if(i==4){
                real_cand_list[i] = 1;
            }else if(i>4){
                real_cand_list[i] = cand_list[i-2];
            }
        }
        
        int current_person_idx = 0;
        int current_score = 0;
        for(int inning=1; inning<=INNING_NUM; inning++){
            // out 넘어가면 다음거 하면 됨!
            while(out_num<3){
                current_person_idx = (current_person_idx)%PERSON_NUM + 1; // !!1부터 시작할 때!
//                cout << current_person_idx;
                int current_person = real_cand_list[current_person_idx];
                if(person_info[inning][current_person]==0){ // 안타를 칠지 등 내용이 적혀 있음
                    out_num++;
                }else{
                    // 1루 2루 3루 홈런 K루 만큼 이동 하면서 체크
                    ground_info[0] = 1; // 처음에 서는 점
//                    cout <<person_info[inning][current_person];
                    for(int lu=1; lu<=person_info[inning][current_person]; lu++){
                        // 한개씩 밀기
                        for(int g=GROUND_NUM; g>0; g--){
                            ground_info[g] = ground_info[g-1];
                        }
                        ground_info[0] = 0;
                        // 점수 체크하기r
                        if(ground_info[GROUND_NUM]==1){
                            current_score++;
                        }
                    }
                }
            }
            // 이닝이 시작될 때는 주자는 없다.!!!
            ground_info.clear();
            ground_info.resize(GROUND_NUM+1,0);
            out_num = 0;
        }
        
        if(current_score>max_score) max_score = current_score;

    }while(next_permutation(cand_list.begin(),cand_list.end())); // permutation 돌리기
}
