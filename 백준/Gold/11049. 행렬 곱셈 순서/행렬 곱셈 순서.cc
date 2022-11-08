#include <bits/stdc++.h>
using namespace std;
int n;
int dp[501][501]; // first = 행렬이 몇 개 곱해졌는지 계산 편하게 하려고 -1, second 몇번째 index인지
pair<int, int> matrix[501][501];

int solve(int r, int c)
{
	//base case
	if (r == 1)
	{
		return dp[r][c] = 0;
	}
	if (dp[r][c] != -1)
		return dp[r][c];
	else
	{
		int mn = 2e9;
		for (int i = 1; i <r; i++)
		{
			int curr;
			curr = solve(r-i, c) + solve(i, r+c-i);
			int amop = matrix[r-i][c].first * matrix[r-i][c].second * matrix[i][r+c-i].second;
			curr += amop;
			mn = min(mn, curr);
		}
	
		matrix[r][c] = make_pair(matrix[1][c].first, matrix[1][c + r - 1].second);
		return dp[r][c] = mn;
	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n;

	for (int i = 1; i <= n; i++)
		cin >> matrix[1][i].first >> matrix[1][i].second;
	
	memset(dp, -1, sizeof dp);
	cout << solve(n , 1);
}