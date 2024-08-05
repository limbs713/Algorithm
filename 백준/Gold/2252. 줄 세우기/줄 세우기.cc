#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;
long long n, m;
long long ans = 2e9;


int main()
{
	fastio;
	int n, m;
	cin >> n >> m;

	vector<int> v(n+1);
	vector<vector<int>> edge(n + 1);

	int a, b;
	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		v[b]++;
		edge[a].push_back(b);
	}

	queue<int> q;
	for (auto iter = v.begin()+1; iter != v.end(); iter++) {
		if (*iter == 0) {
			q.push(iter - v.begin());
		}
	}


	while (!q.empty()) {
		int curr = q.front();
		q.pop();
		cout << curr << " ";

		for (auto iter = edge[curr].begin(); iter != edge[curr].end(); iter++) {
			if (--v[*iter] == 0) {
				q.push(*iter);
			}
		}
	}

	return 0;
}
