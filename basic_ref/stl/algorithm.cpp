#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

bool desc(int a, int b){
    return a>b;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int temp[] = {1,4,2,3,6};

    // sort
    vector<int> s(temp, temp+5);
    sort(s.begin(), s.end(),desc);

    // binary search
    int myints[] = {10,70,20};
    vector <int> v(myints, myints+3);
    cout <<"binary search position : "<< binary_search(v.begin(), v.end(), 70) << "\n";

    // permutation 순열들 다 찾기
    // n!
    while (next_permutation(myints, myints+3)){
        for(int i=0; i<sizeof(myints)/sizeof(int); i++) cout << myints[i] << " ";
        cout <<"\n";
    }

    // nPk 순열중에 몇개만 찾기
    // int permute_array[] = {1,1,0};
    // while (next_permutation(permute_array, permute_array+3)){
    //     for(int i=0; i<sizeof(permute_array)/sizeof(int); i++){
    //         if(permute_array[i] == 1)
    //             cout << myints[i] << " ";
    //     } 
    //     cout <<"\n";
    // }

    // nCk https://redcoder.tistory.com/46
    

    // lower_bound upper_bound
    sort(v.begin(), v.end());
    vector<int> :: iterator low;
    low = lower_bound(v.begin(), v.end(), 11); // 11보다 작은게 아닌게 시작하는 index

    cout<< "position " << (low-v.begin()) << "\n";      

    // min max
    int a = 2; int b= 5;
    cout << min(a,b) << " ";
    cout << max(a,b);// 둘 중 작은 것, 큰 것 반환함. 
}