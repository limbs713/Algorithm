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

	vector<int> v(n+1);
	for (int i = 1; i <= n; i++) {
		cin >> temp;
		v[i] = v[i - 1] + temp;
	}

	for (int i = 0; i < m; i++) {
		int k, j;
		cin >> k >> j;
		cout << v[j] - v[k-1] <<'\n';
	}
}