#include <iostream>
using namespace std;

int N;
int cup[10000+2];
int cup_profit[10000+2];
bool concat_check[10000+2] ={false};
void find_max_alchol(int);
void find_max_alchol_with_for_loop();

int main() {
    cin >> N;
    for(int i=0;i<N;i++)
        cin >> cup[i];
    cup_profit[0] = cup[0];
    cup_profit[1] = cup[0]+cup[1];
    concat_check[1] = true;
    if(N==1) cout << cup_profit[0];
    else if(N==2) cout << cup_profit[1];
    // else find_max_alchol(2);
    else find_max_alchol_with_for_loop();
    return 0;
}

void find_max_alchol(int n){
    if(n==N){
        cout << cup_profit[N-1];
        return;
    }
    
    // 앞에 애가 붙어서 이익을 내고 있는데 그대로가 좋은지(cup_profit[n-1]), 떨어뜨리고 넣는게 좋은지
    cup_profit[n] =  max(cup_profit[n-1],cup_profit[n-2]+cup[n]);
    // 혹은 앞에거랑 나랑 붙이되, 그 앞앞에걸 넣는게 좋을지
    cup_profit[n] = max(cup_profit[n],cup_profit[n-3]+cup[n-1]+cup[n]);
    // 이 로직 구현을 위해서 concat_check도 만들고 했었는데 훨씬 간단하다..
    //    int concat_num;
    //    if(concat_check[n-1]==true){ // 꼭 concat 아닐 때 붙어도 상관없음
    //        concat_num = (cup_profit[n-1]-cup[n-2])+cup[n];
    //    }else{
    //        concat_num= cup_profit[n-1]+cup[n];
    //    }
    //    if(cup_profit[n]<concat_num){
    //        cup_profit[n] = concat_num;
    //        concat_check[n] = true;
    //    }
    find_max_alchol(n+1);
}


void find_max_alchol_with_for_loop(){
    for(int n=2; n<N; n++){
        // 앞에 애가 붙어서 이익을 내고 있는데 그대로가 좋은지(cup_profit[n-1]), 떨어뜨리고 넣는게 좋은지
        cup_profit[n] =  max(cup_profit[n-1],cup_profit[n-2]+cup[n]);
        // 혹은 앞에거랑 나랑 붙이되, 그 앞앞에걸 넣는게 좋을지
        cup_profit[n] = max(cup_profit[n],cup_profit[n-3]+cup[n-1]+cup[n]);
    }
    
    cout << cup_profit[N-1];
}
