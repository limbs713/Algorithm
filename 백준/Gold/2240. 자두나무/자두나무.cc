#include <bits/stdc++.h>
using namespace std;

int dp[2][1001][31]; // 몇 초일 때 , 몇 번 나무에 있을 때 , 몇 번 움직였을 때의 최대값
int a[1001];
int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	int t,w;
	cin >> t >> w;
	for (int i = 1; i <= t; i++)
		cin >> a[i];
	dp[0][0][0] = 0;
	dp[1][0][0] = 0;
	for (int i = 1; i <= t; i++)
	{
		if (a[i] == 1)
		{
			dp[0][i][0] = 1 + dp[0][i - 1][0];
		}
	}
	
	for (int i = 1; i <= w; i++)
	{
		for (int j = 1; j <= t; j++)
		{
			if (a[j] == 1)
			{
				dp[0][j][i] = max(dp[0][j - 1][i] + 1, dp[1][j - 1][i - 1] + 1);
				dp[1][j][i] = max(dp[1][j - 1][i], dp[0][j - 1][i - 1]);
			}
			else
			{
				dp[1][j][i] = max(dp[1][j - 1][i] + 1, dp[0][j - 1][i - 1] + 1);
				dp[0][j][i] = max(dp[0][j - 1][i], dp[1][j - 1][i - 1]);
			}
		}
	}

	cout << max(dp[0][t][w], dp[1][t][w]);
}