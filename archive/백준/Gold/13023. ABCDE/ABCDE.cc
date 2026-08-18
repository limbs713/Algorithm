#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;
vector<vector<int>> v;
unordered_set <int> s;
int n, m;

bool check(int curr, int cnt) {
	if (cnt == 5) {
		return true;
	}

	for (auto& a : v[curr]) {
		if (s.find(a) == s.end()) {
			s.insert(a);

			if (check(a, cnt+1)) {
				return true;
			}
			s.erase(a);
		}
	}

	return false;
}
int main() {
	fastio;
	cin >> n >> m;
	int from, to;
	v.assign(n, vector<int>());
	for (int i = 0; i < m; i++) {
		cin >> from >> to;
		v[from].push_back(to);
		v[to].push_back(from);
	}

	for (int i = 0; i < n; i++)
	{
		s.insert(i);
		if (check( i, 1)) {

			cout << 1;
			return 0;
		}
		s.erase(i);
	}

	cout << 0;
}
