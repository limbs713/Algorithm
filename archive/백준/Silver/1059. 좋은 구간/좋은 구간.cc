#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int l;
	cin >> l;
	vector<int> arr(l);
	for (int i = 0; i < l; i++)
	{
		int temp;
		cin >> temp;
		arr.push_back(temp);
	}
	sort(arr.begin(), arr.end());
	int n, left, right;
	cin >> n;
	for (auto a : arr)
	{
		if (n > a) {
			left = a;
			continue;
		}
		else
		{
			right = a;
			break;
		}
	}
	int cnt = 0;
	for (int i = left + 1; i <= n; i++)
	{
		for (int j = n; j < right; j++)
		{
			if (i == j)	continue;
			cnt++;
		}
	}

	cout << cnt;
}