	#include <bits/stdc++.h>
	using namespace std;

	int main() {
		ios::sync_with_stdio(0); cin.tie(0);
		int t;
	
		cin >> t;

		while (t--)
		{
			int n,cnt=0;
			cin >> n;
			int arr[1001];
			bool check[1001];
			memset(check, false, sizeof check);
			for (int i = 1; i <= n; i++)
			{
				cin >> arr[i];
			}

			for (int i = 1; i <= n; i++)
			{
				if (!check[i])
				{
					int curr = arr[i];
					check[i] = true;
					while (!check[curr])
					{
						check[curr] = true;
						curr = arr[curr];
					}
					cnt++;
				}
				else
				{
					continue;
				}
			}
			cout << cnt<<'\n';
		}
	}
