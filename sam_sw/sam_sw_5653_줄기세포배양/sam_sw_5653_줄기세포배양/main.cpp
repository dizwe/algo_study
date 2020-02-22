#include <iostream>
#include <vector>
#define MAX_ROW 800
#define MAX_COL 800
#define START_ROW 350
#define START_COL 350

using namespace std;

struct cell_info{
    int row;
    int col;
    int power;
    int active_time;
    int wait_time;
    bool full;
};

int ROW, COL, TIME;
vector<vector<cell_info> > cells_map;
vector<cell_info> live_cells; // 실제 활동하는 애들 정보

void simulate(int t);

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    for(int t=1; t<=T; t++){
        cin >> ROW >> COL >> TIME;
         // 초기화
         cells_map.resize(MAX_ROW);
         for(int r =0; r<MAX_ROW;r++) cells_map[r].resize(MAX_COL);
         
         for(int r=0; r<ROW; r++){
             for (int c=0; c<COL; c++){
                 int power;
                 cin >> power;
                 if(power==0){
                     cells_map[START_ROW+r][START_COL+c].power = 0;
                     cells_map[START_ROW+r][START_COL+c].full = false;
                 }else{
                     cell_info one_cell = cell_info{
                                           START_ROW+r,START_COL+c,
                                           power, power, power,
                                           true
                                         };
                     cells_map[START_ROW+r][START_COL+c] = one_cell;
                     live_cells.emplace_back(one_cell);
                 }
             }
         }
        simulate(t);
        // !! 전역변수를 erase 하자
        cells_map.clear();
        live_cells.clear();
    }
 
}

void simulate(int t){
    // 방향 정보
    vector<pair<int, int> > directions{make_pair(0,1),make_pair(1,0),make_pair(0,-1), make_pair(-1,0)};

    // t 시간 후
    for(int t=1; t<=TIME; t++){
        // 1시간 더 경과한 것 처럼 만들기
        vector<int> erase_list;
        for(int cidx =0; cidx<live_cells.size(); cidx++){
            cell_info one_cell = live_cells[cidx]; // reference로 받기?????!!! 가능한가?? 왜 안되지..
            // 살아 있는 애라면
            if(one_cell.full==true && one_cell.wait_time>0){ // 살아있는데 휴지기인 cell이라면
                // wait time 낮추기(두개 관리하는게 좀 힘드네)
                live_cells[cidx].wait_time--;
                cells_map[live_cells[cidx].row][live_cells[cidx].col].wait_time--;
            }else if(one_cell.full==true && one_cell.wait_time==0 && one_cell.active_time>0){ // 살아있는데 휴지기가 끝났고 active는 안끝났다먄
                // 주변 cell 들을 물들여버리자!
                // 주변에 4방향
                for(int dir = 0; dir<directions.size(); dir++){
                    int next_row = one_cell.row+directions[dir].first;
                    int next_col = one_cell.col+directions[dir].second;
                    // true면 아무 작업도 할 이유가 없지
                    if(cells_map[next_row][next_col].full==false){
                        // !! 처음에 아무것도 없을때 power를 어떻게 비교할거냐?
                        // 오! 처음에 받을 때 power=0으로 세팅하면 되잖아
                        if(cells_map[next_row][next_col].power < one_cell.power){
                            // cell 채워넣기
                            // 추후에 완전히 정해지면 full이라고 넣기
                            cell_info next_cell = cell_info{
                                next_row, next_col, one_cell.power, one_cell.power, one_cell.power, false
                            };
                            cells_map[next_row][next_col] = next_cell;
                            live_cells.emplace_back(next_cell);
                        }
                    }
                }
                // 최대값으로 고르고 걔도 full로 채우기
                live_cells[cidx].active_time--;
                cells_map[live_cells[cidx].row][live_cells[cidx].col].active_time--;
            }else if(one_cell.full==true && one_cell.wait_time==0 && one_cell.active_time==0){ // live_cells 리스트에서 빼버리기
                // 기능을 다한 애는 live_cells에서 지웅기
                // !!!!!! earse 하면 하나씩 당겨지는데 그러면 idx 처리가 안된다!!!
                // erase는 나중에 해야한다!!
                erase_list.push_back(cidx);
               
            }
        }
        
        // https://stackoverflow.com/questions/3487717/erasing-multiple-objects-from-a-stdvector
        // 이 방법은 제일 뒤에거가 앞으로 와서 걔가 지워야 되는 애일때 넘어갈 수도 있음
        // live_cells[cidx] = live_cells.back();
        // live_cells.pop_back();
        
        // !! 다른 방법은 아예 거꾸로 지우면 된다!
        for(int i = int(erase_list.size())-1; i>=0; i--){
            live_cells.erase(live_cells.begin()+erase_list[i]);
        }

        // 다 채우고 나서 그 리스트에 있던것들은 다 full로 바꾸기
        for(int cidx =0; cidx<live_cells.size(); cidx++){
            cells_map[live_cells[cidx].row][live_cells[cidx].col].full = true;
            live_cells[cidx].full = true;// 얘도 true
        }
    }
    int live_cells_size=0;
    for(int cidx =0; cidx<live_cells.size(); cidx++){
        cell_info one_cell = live_cells[cidx];
        // !! 여기서 or다!!
        if(one_cell.full==true && (one_cell.wait_time>0 || one_cell.active_time>0)){
            live_cells_size++;
        }
    }
    cout << "#" << t << " "<< live_cells_size << "\n";
}
