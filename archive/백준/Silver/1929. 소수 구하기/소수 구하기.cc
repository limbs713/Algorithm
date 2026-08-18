#include<bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main()
{
	fastio;
	int n,m;
	cin >> n >> m;

	vector<int> v(m + 1, 1);
	v[1] = 0;
	for (int i = 2; i <= sqrt(m); i++)
	{
		if (v[i] == 0) continue;
		for (int j = 2; i * j <= m; j++) {
			v[i * j] = 0;
		}
	}

	for (int i = n; i <= m; i++) {
		if (v[i] == 1) {
			cout << i << '\n';
		}
	}
}