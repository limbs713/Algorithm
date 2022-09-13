#include <bits/stdc++.h>
using namespace std;
#define MAX 1001
int indegree[MAX];
long long sum[MAX];
int cost[MAX];
vector<vector<int>> v(MAX, vector<int>());
int n, m, dest;
void topologySort()
{
	queue<int> q;
	for (int i = 1; i <= n; i++)
	{
		if (!indegree[i])
		{
			q.push(i);
		}
	}
	while(!q.empty())
	{
		int x = q.front();
		q.pop();
		for (int j = 0; j < v[x].size(); j++)
		{
			int y = v[x][j];
			if(sum[y] < sum[x] + cost[y])
			{
				sum[y] = sum[x] + cost[y];
			}
			indegree[y]--;
			if (indegree[y]==0)
			{
				q.push(y);
			}
		}
	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t;
	cin >> t;
	while (t--)
	{
		cin >> n >> m;
		for (int i = 1; i <= n; i++)
		{
			int t;
			cin >> t;
			cost[i] = t;
			sum[i] = cost[i];
		}
		for (int i = 0; i < m; i++)
		{
			int a, b;
			cin >> a >> b;
			v[a].push_back(b);
			indegree[b]++;
		}
		cin >> dest;
		topologySort();
		cout << sum[dest]<<'\n';

		v.assign(MAX, vector<int>(0));
		memset(cost, 0, MAX);
		memset(indegree, 0, MAX);
		memset(sum, 0, MAX);
	}
}