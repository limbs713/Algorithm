#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

bool check(int target) {
	for (int i = 2; i <= sqrt((double)target); i++) {
		if (target % i == 0)
			return false;
	}

	return true;
}
int main() {
	fastio;
	int n;
	cin >> n;
	vector<vector<int>> v(n+1, vector<int>());
	v[1].push_back(2);
	v[1].push_back(3);
	v[1].push_back(5);
	v[1].push_back(7);

	for (int i = 2; i <= n; i++) {
		for (auto& a : v[i - 1]) {
			int target = a*10;
			for (int j = 0; j < 10; j++)
			{
				if (check(target + j)) {
					v[i].push_back(target + j);
				}
			}
		}
	}
	
	for (auto& a : v[n]) {
		cout << a << '\n';
	}
}
