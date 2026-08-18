#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int func(int n, int y, int x)
{
	if (n == 1)	return 2 * y + x;
	else
	{
		int sz = 1 << n - 1, cnt = sz * sz;
		if (y < sz)
		{
			if (x < sz)
			{
				return func(n - 1, y, x);
			}
			else
			{
				return func(n - 1, y, x - sz) + cnt;
			}
		}
		else
		{
			if (x < sz)
				return func(n - 1, y - sz, x) + cnt * 2;
			else
				return func(n - 1, y - sz, x - sz) + cnt * 3;
		}
	}
}

int main()
{
	fastio;
	int n,r,c;
	cin >> n>>r>>c;

	cout<<func(n, r, c);
}
