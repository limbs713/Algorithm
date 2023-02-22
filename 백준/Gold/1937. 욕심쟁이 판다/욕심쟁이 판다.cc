	#include <bits/stdc++.h>
	using namespace std;
	int dx[4] = { -1,1,0,0 };
	int dy[4] = {0,0,-1,1 };
	int arr[505][505];
	int dp[505][505];
	int n;

	int bfs(int x, int y)
	{
		if (dp[x][y] != 0) return dp[x][y];
		dp[x][y] = 1;
		for (int i = 0; i < 4; i++)
		{
			if (x + dx[i]<1 || x + dx[i]>n || y + dy[i] < 1 || y + dy[i] >n)
				continue;
			if (arr[x][y] < arr[x + dx[i]][y+dy[i]])
			{
				dp[x][y] = max(dp[x][y], bfs(x + dx[i], y + dy[i])+1);
	
			}
		}
		return dp[x][y];
	}

	int main() {
		ios::sync_with_stdio(0); cin.tie(0);
		cin >> n;
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				cin >> arr[i][j];
			}
		}
		int mx = 0;

		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				mx = max(mx, bfs(i, j));
			}
		}

		cout << mx;
	}
