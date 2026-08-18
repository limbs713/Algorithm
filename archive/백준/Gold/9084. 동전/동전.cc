#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int t;
	cin >> t;
	while (t--)
	{
		int dp[10001];
		int coin[21];
		int n,k;
		cin >> n;
		
		memset(dp, 0, sizeof dp);
		for (int i = 1; i <= n; i++)
		{
			cin >> coin[i];
		}
		cin >> k;

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

		cout << dp[k]<<'\n';
	}
	return 0;


}
