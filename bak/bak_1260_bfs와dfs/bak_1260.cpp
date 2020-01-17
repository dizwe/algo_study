#include <iostream>
#include <stack>
#include <queue>
#include <algorithm>
using namespace std;

int num_vertex, num_edge, start_number;

void dfs_big_first(vector<int> graph[]){
    stack<int> st;
    bool * visited = new bool[num_vertex+1]; // 시작을 1부터로
    fill_n(visited, num_vertex+1, false); // fill_n 안하면 다 1로 fill 되어있음

    st.push(start_number); // vector 자체 말고 그냥 값을 넣으면 됨
    int current_number;
    while(!st.empty()){
        // top하고 pop
        current_number = st.top();
        st.pop();
        if(visited[current_number] == false){
            visited[current_number] = true; // 뽑을 때 방문한걸로 하기!
            cout << current_number << " "; 
            for(int i=0; i<graph[current_number].size();i++){
                // !!! 방문한적 없어야 push
                int next_node = graph[current_number][i];
                if(visited[next_node]==false){
                    st.push(next_node); 
                }
                
            }
        }
    }
}

void dfs_small_first(vector<int> graph[]){
    stack<int> st;
    bool * visited = new bool[num_vertex+1]; // 시작을 1부터로
    fill_n(visited, num_vertex+1, false); // fill_n 안하면 다 1로 fill 되어있음

    st.push(start_number); // vector 자체 말고 그냥 값을 넣으면 됨
    int current_number;
    while(!st.empty()){
        // top하고 pop
        current_number = st.top();
        st.pop();
        if(visited[current_number] == false){ // 내가 방문했는지 붜 먼저 확인해야 한다!!
            visited[current_number] = true; // 뽑을 때 방문한걸로 하기!
            cout << current_number << " "; 
            
            for(int i=graph[current_number].size()-1; i>=0;i--){
                // !!! 방문한적 없어야 push
                int next_node = graph[current_number][i];
                if(visited[next_node]==false){
                    st.push(next_node); 
                }
                
            }
        }
    }
}


//!!! graph[]로 하면 return된다!
void bfs(vector<int> graph[]){
    queue <int> que;
    bool * visited_bfs = new bool[num_vertex+1];
    fill_n(visited_bfs, num_vertex+1, false); // !!!fill_n 안하면 다 1로 fill 되어있음 안하면 값이 이상하게 계속 바뀌더라!

    que.push(start_number);
    int current_number;
    cout << start_number  << " ";
    visited_bfs[start_number] = true;

    while(!que.empty()){
        current_number = que.front();
        que.pop();

        for(int i=0; i<graph[current_number].size(); i++){
            int next_node = graph[current_number][i];
            if(visited_bfs[next_node]==false){ // 방문한 적 없으면
                que.push(next_node);
                cout << next_node  << " "; // 밑에서 다 넣고 하나씩 뽑으면 되니까 여기서 인쇄하면 됨!        
                visited_bfs[next_node] = true;
            }
        }
    }
}

bool desc(int a, int b){
    return a>b;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> num_vertex >> num_edge >> start_number;

    ////// graph 만들기
    // 여기서도 시작이 1이라 크기를 맞춰야 함.
    vector<int> graph[num_vertex+1]; // 정점만큼 정의하기
    // ?? 여기서 graph.resize(num_bector+1); 을 하면 안되나..?(이런 방법으로 만들 방법 없낭??)
    // 간선 개수만큼 cin
    for(int e = 0; e<num_edge; e++){
        int u, v;
        cin >> u >> v;
        // 여기섣도
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    // 작은거부터 방문한다니까 정렬(근데 stack에 넣으면 반대로 되니까... 반대로 정렬해야하나...?)
    for(int v=1; v<=num_vertex; v++) sort(graph[v].begin(), graph[v].end());
    // for(int v=1; v<=num_vertex; v++) sort(graph[v].begin(), graph[v].end(),desc);
    
    // //인쇄해보기
    // for(int v = 1; v<=num_vertex; v++){
    //     for(int i =0; i<graph[v].size(); i++){
    //         // 보통 back하고 pop_back하거나, 아예 없애고 싶지 않을 때에는 그냥 index로!
    //         cout << graph[v][i] << " ";
    //     }
    //     cout << "\n";
    // }
    // cout <<"\n";



    // !! 방문정점이 여러개일때에는 작은 것을 먼저 방문해야한다!!
    ////// DFS - !!STACK 말고도 방문했는지 확인하는 visited도 중요하다!
    dfs_small_first(graph);
    cout << "\n";
    ////// BFS
    bfs(graph);

    return 0;
}
