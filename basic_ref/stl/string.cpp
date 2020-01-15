#include <iostream>
using namespace std;

int main(){
    string a = "haha";
    // printf("%s\n", a); //이러면 안나옴
    cout << a; //나옴
    printf("%s\n", a.c_str());

    string x;
    // scanf("%s", x);
    // cout <<x <<endl; // 안됨. scanf는 안됨!
    cin >> x;
    cout <<x <<endl;
    cout << "----\n";

    // length
    cout <<a.length();
    cout <<a.size();
    a.resize(10,'b'); // 빈공간을 'b'로 채운다.
    cout << "----\n";

    //push_back, pop_back
    a.push_back('c'); // 여기서 char만 됨 즉 ""는 안됨
    cout << a;
    a.pop_back();
    cout << a;
    cout << "----\n";

    //front, back
    cout << a.front();
    cout << a[1];
    cout << "----\n";

    // 연산자
    string z = "hahah";
    string y = "kiki";
    cout << z+ ' ' + y <<endl;
    if(z == y) cout << 1;
    cout << "----\n";

    return 0;
}