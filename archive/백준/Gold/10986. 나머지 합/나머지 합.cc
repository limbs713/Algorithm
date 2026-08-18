#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n, m, temp;
	long long ans = 0;
	cin >> n;
	cin >> m;
	vector<int> s(n+1);
	vector<long long> c(m);

	for (int i = 1; i <= n; i++) {
		cin >> temp;
		s[i] = (s[i - 1] + temp % m) % m;
	}

	for (int i = 0; i <= n; i++) {
		c[s[i]]++;
	}

	for (int j = 0; j < m; j++) {
		if (c[j] > 1) {
			ans += c[j] * (c[j] - 1) / 2;
		}
	}

	cout << ans;
}