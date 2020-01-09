#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(){
    pair <int, int> a = make_pair(1,1);
    pair <string, string> str = make_pair("hi","pair");
    // v(10,0); 0으로 initialize 하는 pair 10개 만들기
    vector <pair<int,string> > v(10,make_pair(1,"zzz")); 

    cout << a.first + a.second <<endl;
    cout << str.first + str.second <<endl;
    for(int i=0; i<(int)v.size();i++)
        cout << v[i].first << ' ' <<v[i].second<<endl;    

    // 비교는 first->second 순으로!
    return 0;
}