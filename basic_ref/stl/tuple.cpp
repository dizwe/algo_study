// tuple은 -std=c++11에서 부터 사용 가능하다!
#include <iostream>
#include <tuple>
#include <string>

using namespace std;

int main(){
    tuple<int, string> t;
    // tuple <char, int, double, string> k;
    t = make_tuple(54, "HelloWorld");
 
    cout<< get<1>(t);
    // cout<< get<3>(k); 
    get<1>(t) = "안녕! tuple!";
    // cout<< get<3>(k);
    return 0;
}