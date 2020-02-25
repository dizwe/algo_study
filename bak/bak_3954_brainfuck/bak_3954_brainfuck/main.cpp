#include <iostream>
#include <vector>
#include <stack>
#define INFINITE_LOOP 50000000
using namespace std;

// unsigned 2^8!!!!! 1byte!!!!!!!!!
vector <char> memory_list;
string codes;
string inputs;
int ARRAY_SIZE, CODE_SIZE, INPUT_SIZE;
int test_num;
void run_code(vector<pair <int, int> > pairs);
vector<pair <int, int> > find_pair();

int pointer_idx = 0;// 근데 이게 맞나??
 
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> test_num;
    for(int t=1;t<=test_num;t++){
        cin >> ARRAY_SIZE >> CODE_SIZE >> INPUT_SIZE;
        
        memory_list.resize(ARRAY_SIZE,0);

        cin >> codes;
        cin >> inputs;
        
        vector<pair <int, int> > pairs = find_pair(); // stack으로 괄호 짝 찾기!
    //    for(pair<int, int> one_pair:pairs){
    //        cout << one_pair.first << " " << one_pair.second << "\n";
    //    }
        run_code(pairs);
        memory_list.clear();
    }
    

    return 0;
}

vector<pair <int, int> > find_pair(){
    stack <int> code_stack;
    vector<pair <int, int> > pairs;
    for(int i=0; i<CODE_SIZE; i++){
        if(codes[i] == '['){
            code_stack.push(i);
        }else if(codes[i]==']'){
            int bracket_start_idx = code_stack.top();
            code_stack.pop();
            pairs.emplace_back(make_pair(bracket_start_idx,i));
        }
    }
    return pairs;
}

void run_code(vector<pair <int, int> > pairs){
    int current_code_idx = 0;
    int execute_code_num = 0;
    int input_idx = 0;
    
    while(current_code_idx<CODE_SIZE){
        execute_code_num++;
        char current_code = codes[current_code_idx];
        if(current_code=='-'){ //"" 말고 '' 써야 하는것 잊지 말것!
            memory_list[pointer_idx]--;
        }else if(current_code=='+'){
            memory_list[pointer_idx]++;
        }else if(current_code=='<'){
            int temp_idx = pointer_idx-1;
            if(temp_idx<0) pointer_idx = ARRAY_SIZE-1;
            else pointer_idx = temp_idx;
        }else if(current_code=='>'){
            pointer_idx = (pointer_idx + 1) % ARRAY_SIZE;
        }else if(current_code=='['){
            if(memory_list[pointer_idx]==0){
                // 짝을 이루는게 중요하네!!!
                int next_code_idx = current_code_idx;
                for(pair<int, int> one_pair:pairs){
                    if(one_pair.first==current_code_idx) // 맞는 pair 찾기
                        next_code_idx = one_pair.second;
                }
                current_code_idx = next_code_idx;
                continue; // code_idx를 바꿀 필요가 없으니까
            }
        }else if(current_code==']'){
            if(memory_list[pointer_idx]!=0){
                // 짝을 이루는게 중요하네!!!
                int next_code_idx = current_code_idx;
                for(pair<int, int> one_pair:pairs){
                    if(one_pair.second==current_code_idx) // 맞는 pair 찾기
                        next_code_idx = one_pair.first;
                }
                if(execute_code_num>INFINITE_LOOP){
                    cout << "Loops " << next_code_idx << " " << current_code_idx << "\n";
                    return;
                }
                current_code_idx = next_code_idx;
                continue; // code_idx를 바꿀 필요가 없으니까
            }
        }else if(current_code=='.'){
            //cout << memory_list[pointer_idx]; // 출력은 무시
        }else if(current_code==','){
            // !!??길이보다 더 늘어나는지도 확인해야 할듯
            if(input_idx==INPUT_SIZE){ // EOF
                memory_list[pointer_idx] = (char)255;
                input_idx++;
            }else{
                memory_list[pointer_idx] = inputs[input_idx++];
            }
        }
        current_code_idx++;
    }
    
    cout << "Terminates\n";
}

