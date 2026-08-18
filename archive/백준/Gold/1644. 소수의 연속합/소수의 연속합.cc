#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int n;
	cin >> n;
	vector<int> v(n + 1);
	for (int i = 2; i <= n; i++)
		v[i] = i;
	for (int i = 2; i <= n; i++)
	{
		for (int j = 2 * i; j <= n; j+=i)
		{
			if (v[j] == 0)	continue;
			v[j] = 0;
		}
	}
	int m = 0;
	vector<int> arr;
	for (int i = 2; i <= n; i++)
	{
		if (v[i])
		{
			arr.push_back(v[i]);
			m++;
		}
	}
	int ans = 0;
	int cnt = 0;
	int st = 0, en = 0;
	while (en <= m)
	{
		if (en == m && ans < n)
			break;
		if (ans >= n)
		{
			ans -= arr[st++];
		}
		else if (ans < n)
		{
			ans += arr[en++];
		}

		if (ans == n)
		{
			cnt++;
		}
	}
	cout << cnt;
}