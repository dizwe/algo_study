#include <iostream>
#include <vector>
using namespace std;

int main(){
    vector<int> v(10,0);
    //size
    cout<< v.size() <<endl;
    //resize
    v.resize(12,1); //확장되는 공간의 값은 1로 채운다(축소되면 안먹힘)

    //push_back(뒤에 넣어줌) pop_back(뒤에꺼 빼내기)
    int a[10] = {1,2,3,4,5,6,7,8,9};
    // 1,2,3,4,5 만큼 잘려서 저장됨
    vector <int> k(a,a+5);
    for(int i =0;i<(int)k.size();i++)
        cout<<k[i]<<' ';
    cout <<"\n";
    k.pop_back();
    for(int i =0;i<(int)k.size();i++)
        cout<<k[i]<<' ';
    cout <<" pop_back\n\n";

    vector <string> str;
    str.push_back("kk");
    for(int i =0;i<(int)str.size();i++)
        cout<<str[i]<<' ';
    cout <<"\n";
    str.push_back("bb");
    for(int i =0;i<(int)str.size();i++)
        cout<<str[i]<<' ';
    cout <<" push_back\n";
    
    // v.insert();
    vector <int> vi(5,5);
    vi.insert(vi.begin()+2 ,1); // 551555
    //이런건 안됨 vi.insert(vi[2] ,1); // 551555
    for(int i =0;i<(int)vi.size();i++)
        cout<<vi[i]<<' ';
    vi.insert(vi.end(), a+2, a+4); // sequence 잘라서 넣기(길이보다 더 추가됨)
    cout<<"\n";

    // v.erase();
    vector <string> ve(5,"55");
    ve.insert(ve.begin()+2, "111");
    for(int i =0;i<(int)ve.size();i++)
        cout<<ve[i]<<' ';
    cout <<"\n";    
    // const_iterator와 그냥 Iterator가 있다.
    ve.erase(find(ve.begin(), ve.end(), "111"), ve.end());
    for(int i =0;i<(int)ve.size();i++)
        cout<<ve[i]<<' ';
    cout <<"erase\n";    

    // 이차원
    vector<vector<int> > vv(10);
    for(int i=0; i<(int)vv.size(); i++)
        vv[i].resize(10, i);
    
    for(int i=0; i<(int)vv.size(); i++){
        for(int j=0; i<(int)vv[j].size(); j++)
            cout << vv[i][j] <<' ';
    }
    cout <<"\n";

    v.clear();
    cout<< v.size();
}