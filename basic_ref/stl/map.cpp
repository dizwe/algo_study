#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

int main(){ 
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    map<string, int> lama;
    map<string, int> lam;

    lama.insert(make_pair("ha",0));
    lama.insert(pair<string, int>("kk",0));
    lama["cc"] = 1;
    cout << lama["cc"];
    cout << lama.size();

    map<string, int>::iterator it;
    for (it = lama.begin(); it != lama.end(); it++ ){
        std::cout << it->first //key
                  << ':'
                  << it->second //value
                  << "\n";
    }

    for (auto one_elem = lama.begin(); one_elem != lama.end(); one_elem++ ){
        std::cout << one_elem->first //key
                  << ':'
                  << one_elem->second //value
                  << "\n";
    }
}
    