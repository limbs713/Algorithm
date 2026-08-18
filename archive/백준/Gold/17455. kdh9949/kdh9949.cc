#include <bits/stdc++.h>
using namespace std;

const int SZ = 200002;
vector<int> arr[SZ];
int dp[SZ];
int ind[SZ];
int kdh[SZ];
int check[SZ];

int ch2int(char x) {
	return x == 'K' ? 0 : (x == 'D' ? 1 : 2);
}
bool cycle(int n)
{
	for (int i = 1; i <= n; i++)
	{
		if (check[i])
			continue;

		if (ind[i] != 0)
			return true;
	}

	return false;
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int n, m;
	cin >> n >> m;

	for (int i = 1; i <= n; i++)
	{
		char temp;
		cin >> temp;
		kdh[i] = ch2int(temp);
	}

	for (int i = 1; i <= m; i++)
	{
		int st, en;
		cin >> st >> en;
		if ((kdh[st] + 1) % 3 == kdh[en])
		{
			arr[st].push_back(en);
			ind[en]++;
		}
		if ((kdh[en] + 1) % 3 == kdh[st])
		{
			arr[en].push_back(st);
			ind[st]++;
		}
	}
	for (int t = 0; t < 2; t++)  //D -> H,  H -> K
	{
		for (int i = 1; i <= n; i++)
		{
			if (check[i])
				continue;

			if (ind[i] == 0 && kdh[i] != 0)
			{
				check[i] = 1; // search에서 제외
				for (auto k : arr[i])
				{
					ind[k]--;
				}
			}
		}
	}

	queue <int> q;

	for (int i = 1; i <= n; i++)
	{
		if (check[i])
			continue;
		if (ind[i] == 0)
		{
			q.push(i);
			dp[i]=1;
		}
	}

	while (!q.empty())
	{
		int curr = q.front();
		q.pop();
		for (auto i : arr[curr])
		{
			if (check[i])
				continue;

			dp[i] = max(dp[i], dp[curr] + 1);
			ind[i]--;
			if (ind[i] == 0)
				q.push(i);
		}
	}



	if (cycle(n))
		cout << -1;
	else
	{
		int mx = 0;
		for (int i = 1; i <= n; i++)
		{
			mx = max(mx, dp[i] / 3);
		}
		cout << (mx == 0 ? -1 : mx * 3);
	}
}
