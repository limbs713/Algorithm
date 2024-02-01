#include<bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main()
{
	fastio;
	int n,m,k,x;
	cin >> n >> m >> k >> x;
		
	vector<vector<int>> v(n + 1, vector<int>());
	vector<int> d(n + 1, 2E9);

	int a, b;
	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		v[a].push_back(b);
	}

	priority_queue<pair<int, int>> pq;
	pq.push({ x,0 });
	d[x] = 0;
	while (!pq.empty()) {
		int curr = pq.top().first;
		int distance = -pq.top().second;
		pq.pop();
		if (d[curr] < distance) continue;

		for (auto& a : v[curr]) {
			if (distance + 1 < d[a]) {
				d[a] = distance + 1;
				pq.push({ a,-(distance + 1)});
			}
		}
	}
	bool check = false;

	for (int i = 0; i <= n; i++) {
		if (d[i] == k) {
			check = true;
			cout << i << '\n';
		}
	}

	if (!check)
		cout << -1;
}