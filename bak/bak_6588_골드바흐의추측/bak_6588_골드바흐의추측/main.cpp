#include <iostream>
#define MAX_SIZE 1000000
using namespace std;

bool sosu[MAX_SIZE + 2] ;
int input_num[MAX_SIZE + 2] ;

int main() {
    int idx = 0;
    int max_num=0;
    while(true){
        cin >> input_num[idx];
        if(input_num[idx]>max_num){
            max_num = input_num[idx];
        }
        if(input_num[idx]==0){
            break;
        }
        idx++;
    }

    // 소수 매기기 원래는 MAX값까지 다 받았는데, 시간 초과 떠서 따로 최대값까지로 바꿈.
    // 다음에는 cin.tie 같은거 해서 줄여보자.
    fill(&sosu[0], &sosu[MAX_SIZE+2], true);
    sosu[1] = false;
    for(int i =2; i<=max_num; i++){
        if(sosu[i]==true){
            for(int j = i*2; j<=max_num; j += i){
                sosu[j] = false;
            }
        }
    }
    
    for(int one_num =0; one_num<idx; one_num++){
        bool find_num = false;
        for(int i =2; i<=input_num[one_num]; i++){
            if(sosu[i]==true&&sosu[input_num[one_num]-i]==true){// 소수면 그 빼기 한 애도 소숭인지 확인
                cout << input_num[one_num] << " = " << i << " + " << input_num[one_num]-i << "\n";
                find_num = true;
                break;
            }
        }
        if(find_num==false) cout << "Goldbach's conjecture is wrong.\n";
        
    }
    
    return 0;
}
