#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

vector<vector<pair<int, int>>> v;
unordered_set <int> s;
int mx = 0;
int mx_node;

void check(int curr, int sum) {
	s.insert(curr);
	for (auto& a : v[curr]) {
		if (s.find(a.first) == s.end()) {
			check(a.first, sum + a.second);
		}
	}
	if (sum > mx) {
		mx_node = curr;
		mx = sum;
	}
	s.erase(curr);
}

int main() {
	fastio;
	int n;
	cin >> n;
	v.assign(n+1,vector<pair<int,int>>());

	int node, temp, val;
	for (int i = 0; i < n; i++) {
		cin >> node;
		while (cin >> temp) {
			if(temp == -1)
				break;
			cin >> val;
			v[node].push_back({ temp,val });
		}
	}

	check(1, 0);
	check(mx_node, 0);
	cout << mx;
}
