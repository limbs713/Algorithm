#include <bits/stdc++.h>
using namespace std;

int dp[10001];
int coin[101];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int n, k;
	cin >> n >> k;

	for (int i = 1; i <= n; i++)
	{
		cin >> coin[i];
	}

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= k; j++)
		{
			if (coin[i] < j)
			{
				dp[j] += dp[j - coin[i]];
			}
			else if (coin[i] == j)
			{
				dp[j]++;
			}
		}
	}

	cout << dp[k];
	return 0;


}
