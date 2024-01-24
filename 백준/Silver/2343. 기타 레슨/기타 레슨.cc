#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n;
	int m;
	int mx = 0;
	int mn = 0;
	cin >> n >> m;
	vector<int> v(n);
	for (int i = 0; i < n; i++) {
		cin >> v[i];
		mn = max(mn, v[i]);
		mx += v[i];
	}

	while (mn < mx) {
		int mid = (mn + mx) / 2;
		int count_m = m;
		int sum = 0;
		for (int i = 0; i < n;i++) {
			sum += v[i];
			if (i != n-1 && sum + v[i+1] > mid) {
				count_m--;
				sum = 0;
				continue;
			}
			if (i == n - 1 && sum <= mid) {
				count_m--;
				sum = 0;
			}
		}
		if (sum > 0) {
			mn = mid + 1;
			continue;
		}
		if (count_m < 0)
		{
			mn = mid + 1;
		}
		else
		{
			mx = mid;
		}

	}

	cout << mx;
}
