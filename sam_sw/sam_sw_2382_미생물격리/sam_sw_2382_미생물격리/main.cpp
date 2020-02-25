#include <iostream>
#include <vector>
#include <set>
using namespace std;

struct cell_info{
    int row;
    int col;
    int cell_organ_num;
    int cell_dir;
};


int SQUARE_SIZE, CLUSTER_NUM, TIME;
vector<vector<vector< struct cell_info > > > cell_map;
set<pair<int, int> > cell_list;


void simulate();
bool is_inside_medicine(pair <int, int> one_cell);
pair <int, int> next_pair(pair <int, int> one_cell, int dir);

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int test_num;
    cin >> test_num;
    for(int t=1;t<=test_num;t++){
        cin >> SQUARE_SIZE >> TIME >> CLUSTER_NUM;
        
        // 3중 vector 괜찮을까?
        // 이거 없이 cell_list로만 하면 옆에 이웃한 것들 찾을 때 계속 cell_list를 찾아야 하니까 더 별로
        cell_map.resize(SQUARE_SIZE);
        for(int c=0; c<SQUARE_SIZE; c++) cell_map[c].resize(SQUARE_SIZE);
        
        for(int cl=0; cl<CLUSTER_NUM; cl++){
            int row, col, cell_organ_num, cell_dir;
            cin >> row >> col >> cell_organ_num >> cell_dir;
            
            cell_list.emplace(make_pair(row,col));
            cell_map[row][col].emplace_back(cell_info{
                row, col, cell_organ_num, cell_dir
            });
        }
        simulate();
        
        int total_organ =0;
        for(pair<int, int> one_cell:cell_list){
            total_organ+=cell_map[one_cell.first][one_cell.second][0].cell_organ_num;
        }
        cell_map.clear();
        cell_list.clear();
        cout <<"#"<< t<<" "<<total_organ << "\n";
    }
}

void simulate(){
    for (int t=1; t<=TIME;t++){
        set<pair <int, int> > next_cell_list;
        for(pair<int, int> one_cell:cell_list){
            // 일단 cell 옮기기
            // 이 때는 vector에 하나밖에 없음
            cell_info this_cell = cell_map[one_cell.first][one_cell.second][0];
            pair<int, int> next_cord = next_pair(one_cell,this_cell.cell_dir);
            // 있던 애는 빼고 전체는 지우면 안됨!(혹시 뒤에 들어왔던 애가 있을수도 있으니까)
            // erase하면
            cell_map[one_cell.first][one_cell.second].erase(cell_map[one_cell.first][one_cell.second].begin());
            // 옮길 자리에 emplace_back(여러개 들어갈 수 있으니까) ?? 근데 옮긴 자리에 누가 있으면?? -> 일단 emplace_back하니까 하나만 옮겨질거라서 괜춘!
            cell_map[next_cord.first][next_cord.second].emplace_back(this_cell);
            next_cell_list.emplace(next_cord); // set은 emplace래
        }
        
        // 옮기고 나서 합치기(set이라서 중복은 피함)!!!! set
        for(pair<int, int> one_cell:next_cell_list){
            // 약품 발린데 있는지(여기서는 여러개가 갈수가 없으니 하나만 생각하면 될듯
            if(is_inside_medicine(one_cell)==true){
                cell_map[one_cell.first][one_cell.second][0].cell_organ_num /= 2;
                // reference로 좀 더 간단하게 바꿀 방법?
                if(cell_map[one_cell.first][one_cell.second][0].cell_dir==1){
                    cell_map[one_cell.first][one_cell.second][0].cell_dir = 2;
                }else if(cell_map[one_cell.first][one_cell.second][0].cell_dir==2){
                    cell_map[one_cell.first][one_cell.second][0].cell_dir = 1;
                }else if(cell_map[one_cell.first][one_cell.second][0].cell_dir==3){
                    cell_map[one_cell.first][one_cell.second][0].cell_dir = 4;
                }else if(cell_map[one_cell.first][one_cell.second][0].cell_dir==4){
                    cell_map[one_cell.first][one_cell.second][0].cell_dir = 3;
                }
            }
            // 아니면 여러개 겹치는데 있는지
            // 한번 하고 나면 사이즈가 1개가 되니까 넘어가겠지?
            
            if(cell_map[one_cell.first][one_cell.second].size()>1){
                int max_num = 0;
                int total_num = 0;
                int next_dir =0;
                for(cell_info will_unite_cell:cell_map[one_cell.first][one_cell.second]){
                    total_num += will_unite_cell.cell_organ_num;
                    if(will_unite_cell.cell_organ_num >max_num){
                        next_dir = will_unite_cell.cell_dir;
                        max_num = will_unite_cell.cell_organ_num;
                    }
                }
                // 하나로 합치기
                cell_map[one_cell.first][one_cell.second].clear();
                cell_map[one_cell.first][one_cell.second].emplace_back(cell_info{
                    one_cell.first, one_cell.second,
                    total_num, next_dir
                });
            }
        }
        
        // cell_list 비우기
        cell_list.clear();
        // cell_list 다시 넣기
        cell_list = next_cell_list;
    }
}

bool is_inside_medicine(pair <int, int> one_cell){
    if(one_cell.first==0 || one_cell.second ==0 || one_cell.first == SQUARE_SIZE-1 || one_cell.second == SQUARE_SIZE-1){
        return true;
    }
    return false;
}

pair<int, int> next_pair(pair <int, int> one_cell, int dir){
    if(dir==1){
        return make_pair(one_cell.first-1,one_cell.second);
    }else if(dir==2){
        return make_pair(one_cell.first+1,one_cell.second);
    }else if(dir==3){
        return make_pair(one_cell.first,one_cell.second-1);
    }else if(dir==4){
        return make_pair(one_cell.first,one_cell.second+1);
    }
    return make_pair(0,0); // 그냥 추가
}
