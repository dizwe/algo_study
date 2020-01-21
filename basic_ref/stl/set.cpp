#include <iostream>
#include <set>

using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    set<string> s;

    //insert
    s.insert("abc");
    s.insert("abc");
    s.insert("def");
    s.insert("ghi");

    //erase
    s.erase("ghi");

    // find
    cout << *s.find("abc") << "\n";

    //count
    cout << s.count("abc") << "\n"; // 두번 적어도 한번만

    // iter
    for(auto it = s.begin(); it!=s.end(); it++){
        cout << "value:" << *it<<"\n";
    }
    for(set<string>::iterator it = s.begin(); it!=s.end(); it++){
        cout << "value:" << *it<<"\n";
    }
    return 0;
}