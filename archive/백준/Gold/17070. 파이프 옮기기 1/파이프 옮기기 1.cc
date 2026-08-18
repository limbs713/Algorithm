#include <bits/stdc++.h>
using namespace std;

int n;
int dp[17][17][3]; /* r번째 행, c번째 열에서 특정 형태로 올 수 있는 경우의 수
0 = 가로 , 1 = 대각선, 2 = 세로*/
int sweet_home[17][17];

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			cin >> sweet_home[i][j];
		}
	}
	dp[1][2][0] = 1;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 3; j <= n; j++)
		{
			if (sweet_home[i][j] != 1)
			{
				dp[i][j][0] = dp[i][j-1][1] + dp[i][j - 1][0];
				dp[i][j][2] = dp[i - 1][j][2] + dp[i - 1][j][1];
			}
			if(sweet_home[i][j] != 1 && sweet_home[i][j-1] != 1 && sweet_home[i-1][j] != 1)
				dp[i][j][1] = dp[i - 1][j - 1][2] + dp[i - 1][j - 1][1] + dp[i - 1][j - 1][0];
			
		}
	}
	
	cout << dp[n][n][0] + dp[n][n][1] + dp[n][n][2];
}