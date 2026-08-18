#include <string>
#include <vector>
#include <queue>
using namespace std;

vector<vector<int>> adj;
vector<int> weight;

void dijkstra (int st){
    queue<int> q;
    q.push(st);
    weight[st] = 0;
    while(!q.empty()){
        int curr = q.front();
        q.pop();
        for(int i =0 ; i < adj[curr].size();i++){
            int temp = adj[curr][i];
            if(weight[temp] > weight[curr] + 1){
                weight[temp] = weight[curr] + 1;
                q.push(temp);
            }
        }
    }
    
}

int solution(int n, vector<vector<int>> edge) {
    int answer = 0;
    adj.assign(n+1,vector<int>());
    weight.assign(n+1,1e9);

    for(int i=0;i<edge.size();i++){
        int first = edge[i][0];
        int second = edge[i][1];
        
        adj[first].push_back(second);
        adj[second].push_back(first);
    }
    dijkstra(1);
    
    int mx = -1e9;
    for(int i= 1 ;i<=n;i++){
        if(mx < weight[i])
        {
            answer = 1;
            mx = weight[i];
        }
        else if(mx == weight[i]){
            answer++;
        }
    }
    return answer;
}