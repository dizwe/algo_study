#include <iostream>
#define MAX_SIZE 1000000

using namespace std;
int T;
int price_info[MAX_SIZE + 2];

int main(int argc, const char * argv[]) {
    cin >> T;
    int n;
    for (int t=0;t<T;t++){
        fill(&price_info[0], &price_info[MAX_SIZE+2], 0);
        cin >> n;
        for(int i=0; i<n; i++){
            cin >> price_info[i];
        }
        
        // 문제 : 나는 dp라 생각함. 뭘 보고 그냥 풀면 되겠다 생가하는건가?
        long long max_price = 0; // !! 답은 부호있는 64bit 정수형으로 표현 가능하다.
        long long max_before_price = 0;
        int max_before_num = 0;
        long long total_price = 0;
        bool find_inc = false;
        
        for(int i=n-1; i>=0; i--){
            if(find_inc==false){// 최초 증가세(반대로 보면 감소세)가 보이는 부분!
                if(price_info[i-1] < price_info[i]){
                    find_inc = true;
                    max_price = price_info[i];
                }
            }else if(i==0&& price_info[i]<=max_price){
                // !! 여기서는 나를 추가해야 한다.(밑에건 나 뺴고 파는거니까)
                total_price += max_price * (max_before_num+1) - max_before_price - price_info[0];
            }else if(i!=0&&price_info[i]>max_price){
                // 전체 flush
                total_price += max_price * max_before_num - max_before_price;
                max_price = price_info[i];
                max_before_price = 0;
                max_before_num = 0;
            }else{
                max_before_price += price_info[i];
                max_before_num++;
            }
            
        }
        cout << total_price << "\n";
    }
    return 0;
}
