#include <string>
#include <vector>
#include <queue>

using namespace std;

bool visited[200];

int solution(int n, vector<vector<int>> computers) {
    int answer = 0;
    queue <int> q;
    for(int i=0;i<n;i++){
        if(visited[i])
            continue;
        q.push(i);
        visited[i] = true;
        while(!q.empty())
        {
            int curr = q.front();
            q.pop();
            for(int j=0;j<n;j++){
                if(computers[curr][j] && !visited[j])
                {
                    q.push(j);
                    visited[j]= true;
                }
            }
        }
        answer++;
    }
    
    return answer;
}