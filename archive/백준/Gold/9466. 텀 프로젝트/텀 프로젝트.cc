#include<bits/stdc++.h>
using namespace std;
int arr[100001];
int ans;
bool dp[100001];
bool check[100001];
void dfs(int curr)
{
	dp[curr] = true;
	int next = arr[curr];
	if (!dp[next])
	{
		dfs(next);
	}
	else if (!check[next])
	{
		ans++;
		for (int i = next; i != curr; i = arr[i])
			ans++;
	}
	check[curr] = true;
	
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int t;
	cin >> t;
	while (t--)
	{
		int n;
		cin >> n;
		ans = 0;
		for (int i = 1; i <= n; i++)
			cin >> arr[i];
		for (int i = 1; i <= n; i++)
		{
			if(!dp[i])
			dfs(i);
		}
		cout << n-ans << '\n';
		memset(dp, false, sizeof dp);
		memset(check, false, sizeof check);
	}
}

