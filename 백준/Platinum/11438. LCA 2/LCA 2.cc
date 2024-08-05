#include <iostream>
#include <cstring>
#include <string>
#include <math.h>
#include <vector>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;
vector<vector<int>> v;
int parent[100001][17];
int depth[100001];
int mx;
int n;

void dfs(int curr) {
	for (auto iter = v[curr].begin(); iter != v[curr].end(); iter++) {
		if (depth[*iter] == -1) {
			parent[*iter][0] = curr;
			depth[*iter] = depth[curr] + 1;
			dfs(*iter);
		}
	}
	return;
}

void connection() {
	for (int i = 1; i < mx; i++) {
		for (int j = 1; j <= n; j++) {
			parent[j][i] = parent[parent[j][i - 1]][i - 1];
		}
	}

	return;
}

int lca(int u, int v) {
	if (depth[u] < depth[v]) {
		swap(u, v);
	}

	int diff = depth[u] - depth[v];

	for (int i = 0; diff != 0; i++) {
		if (diff % 2 == 1) {
			u = parent[u][i];
		}

		diff /= 2;	
	}

	if (u != v) {
		for (int i = mx - 1; i >= 0; i--) {
			if (parent[u][i] != -1 && parent[u][i] != parent[v][i]) {
				u = parent[u][i];
				v = parent[v][i];
			}
		}
		u = parent[u][0];
	}

	return u;
}

int main()
{
	fastio;
	cin >> n;

	v.assign(n + 1,vector<int>());
	fill(depth, depth + n + 1, -1);
	memset(parent, -1, sizeof parent);
	depth[1] = 0;
	mx = ceil(log(n) / log(2));
	
	int a,b;
	for (int i = 0; i < n - 1; i++) {
		cin >> a >> b;
		v[a].push_back(b);
		v[b].push_back(a);
	}

	dfs(1);
	connection();
	int m;
	cin >> m;

	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		cout << lca(a, b) << "\n";
	}

	return 0;
}
