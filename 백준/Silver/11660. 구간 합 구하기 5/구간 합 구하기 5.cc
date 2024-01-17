#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int count[26];

int main() {
	fastio;
	int n;
	int m;
	int temp;

	cin >> n;
	cin >> m;

	vector<vector<int>> v(n+1,vector<int>(n+1));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> temp;
			v[i][j] = v[i][j - 1] + temp;
		}
	}

	for (int i = 0; i < m; i++) {
		int i1, i2, j1, j2;
		cin >> i1 >> i2 >> j1 >> j2;
		int max_x = max(i1, j1);
		int max_y = max(i2, j2);
		int min_x = min(i1, j1);
		int min_y = min(i2, j2);
		int ans = 0;
		for (int j = min_x; j <= max_x; j++) {
			ans += v[j][max_y] - v[j][min_y - 1];
		}

		cout << ans << '\n';
	}
}