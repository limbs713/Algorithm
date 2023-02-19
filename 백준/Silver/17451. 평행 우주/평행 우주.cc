#include <bits/stdc++.h>
using namespace std;

int arr[300001];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> arr[i];
	}

	long long curr = arr[n];

	for (int i = n-1; i != 0; i--)
	{
		if (arr[i] >= curr)
			curr = arr[i];
		else
		{
			if (curr % arr[i] == 0)
				continue;
			else
			curr = arr[i] * ((curr/arr[i]) + 1);
		}
	}

	cout << curr;
}
