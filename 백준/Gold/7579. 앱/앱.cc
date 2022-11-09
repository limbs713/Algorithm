#include<bits/stdc++.h>
using namespace std;
long long dp[101][100001];
int n, k;

void solve()
{
	cin >> n >> k;
	int v[101];
	int w[101];
	int sum = 0;
	for (int i = 1; i <= n; i++)
		cin >> w[i];
	for (int i = 1; i <= n; i++)
	{
		cin >> v[i];
		sum += v[i];	
	}
	// dp[][] = 메모리 값 (상한선이 너무 커서 parameter로는 힘듬)
	for (int i = 1; i <= n; i++) // 활성화 되는 앱 갯수
	{
		for (int j = 0; j <= sum; j++) //	소모되는 비용의 값
		{
			if (j - v[i] >= 0) dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - v[i]] + w[i]);
			else dp[i][j] = dp[i - 1][j];
		}
	}
		
	for (int j = 0; j <= sum; j++)
	{
		if (dp[n][j] >= k) { cout << j; break; }
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	solve();
}