#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t;
	cin >> t;
	int n;
	cin >> n;
	vector<int> arr_n(n);
	for (int i = 0; i < n; i++)
		cin >> arr_n[i];
	int m;
	cin >> m;
	vector<int> arr_m(m);
	for (int i = 0; i < m; i++)
		cin >> arr_m[i];

	vector <long long> partial_a, partial_b;
	for (int i = 0; i < n; i++)
	{
		int sum = 0;
		for (int j = i; j < n; j++)
		{
			sum += arr_n[j];
			partial_a.push_back(sum);
		}
	}
	for (int i = 0; i < m; i++)
	{
		int sum = 0;
		for (int j = i; j < m; j++)
		{
			sum += arr_m[j];
			partial_b.push_back(sum);
		}
	}

	sort(partial_a.begin(), partial_a.end());
	sort(partial_b.begin(), partial_b.end());
	long cnt = 0;

	for (int i = 0; i < partial_a.size(); i++)
	{
		if (binary_search(partial_b.begin(), partial_b.end(), t - partial_a[i]))
		{
			auto lo = lower_bound(partial_b.begin(), partial_b.end(), t - partial_a[i]);
			auto hi = upper_bound(partial_b.begin(), partial_b.end(), t - partial_a[i]);
			cnt += hi - lo;
		}
	}
	cout << cnt;
}