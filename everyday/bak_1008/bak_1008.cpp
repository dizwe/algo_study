#include <iostream>
#include <iomanip> 
using namespace std;

int main(){
    // double은  소수점 이하 15자리 precision
    // float은 소수점 이하 6자리 preicision
    double a, b;
    // cout 인쇄하는 것 설정
    cout << std::setprecision(10);
    cin >> a;
    cin >> b;
    // 원래는 소수점을 6자리까지만 나타낸다
    // cout << (a/b);
    printf("kkk %11.10lf",a/b);

    return 0;
}