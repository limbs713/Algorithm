#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>

using namespace std;
unordered_map <string, vector<string>> graph;
unordered_set <string> visited;
int solution(string begin, string target, vector<string> words) {
    int answer = 0;
    // words들로 그래프 변환
    // begin 노드에서 target 노드로 도달하는 가장 짧은 경로 -> dfs
    words.push_back(begin);
    for(int i=0;i<words.size();i++){
        for(int j=0;j<words.size();j++){
            if(i==j) continue;
            int cnt = 0;
            for(int k=0;k <words[i].size();k++){
                cnt += words[i][k] == words[j][k] ? 1 : 0;
            }
            
            if(words[j].size() - cnt == 1)
            {
                graph[words[i]].push_back(words[j]);
            }
        }
    }
    
    queue<pair<string,int>> q;
    q.push({begin,0});
    
    while(!q.empty()){
        pair <string,int> curr = q.front();
        string word = curr.first;
        int cnt = curr.second;
        q.pop();
        
        if(word == target)
            return cnt; 
        visited.insert(word);
        for(int i=0; i< graph[word].size();i++){
            if(visited.find(graph[word][i]) == visited.end()){
                visited.insert(graph[word][i]);
                q.push({graph[word][i],cnt+1});
            }
        }
    }
    
    
    return 0;    
}