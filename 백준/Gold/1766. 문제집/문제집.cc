#include <bits/stdc++.h>
using namespace std;
int indegree[32001];
int visited[32001];
vector<vector<int>> v(32001);
int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int n, m;
	cin >> n >> m;
	priority_queue<int,vector<int>,greater<int>> q;
	for (int i = 0; i < m; i++)
	{
		int a, b;
		cin >> a >> b;
		v[a].push_back(b);
		indegree[b]++;
	}
	for (int i = 1; i <= n; i++)
	{
		if (!indegree[i])
			q.push(i);
	}
	while (!q.empty())
	{
		int curr = q.top();
		q.pop();
		cout << curr << ' ';
		visited[curr] = true;
		for(int i=0;i<v[curr].size();i++)
		{
			indegree[v[curr][i]]--;
			if (indegree[v[curr][i]] == 0)
			{
				q.push(v[curr][i]);
			}
		}
	}
	for (int i = 1; i <= n; i++)
	{
		if (!visited[i])
			cout << i << ' ';
	}
}