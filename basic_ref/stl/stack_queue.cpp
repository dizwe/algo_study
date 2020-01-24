#include <iostream>
#include <stack>
#include <queue>
using namespace std;

int main(){
    // STACK과 QUEUE는 iterator가 없이 계속 pop,push 하는거다
    // empty, size, push, pop 공통적으로 있음
    ////////////// QUEUE
    // !!top
    queue<int> a; 
    cout << a.empty() << ' ';
    a.push(33);
    a.push(55);
    cout << a.front() << " ";
    cout << a.back() << " ";
    a.pop();
    cout << a.front();
    cout << "----\n";

    ////////////// STACK
    // !! back, front 
    stack< int> b; 
    b.push(44);
    b.push(55);
    cout << b.top() << " ";
    b.pop();
    cout << b.top();
    cout << "----\n";

    ////////////// PRIORITY QUEUE
    // 여기서는 top만 쓰인다.
    int aa[10] = {7,1,3,4,10,4,5,6,7,2};
    priority_queue <int> pq;
    for(int i=0;i<10; i++)
        pq.push(aa[i]);
    cout << pq.top() << " ";

    //기본적으로 less<자료형, 함수> 
    priority_queue< int, vector<int>, greater<int> >  pg;
    for(int i=0;i<10; i++)
        pg.push(aa[i]);
    cout << pg.top();

    
    return 0; 
}