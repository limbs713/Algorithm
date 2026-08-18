#include<bits/stdc++.h>
using namespace std;
#define CRDNT pair<double, double>
map < CRDNT, CRDNT> parent;
map <CRDNT, int> sz;
CRDNT find(CRDNT x)
{
	if (parent[x] == x)	return x;
	return parent[x] = find(parent[x]);
}
void Union(CRDNT x, CRDNT y)
{
	 x = find(x);
	 y = find(y);
	if (sz[x] < sz[y])
	{
		parent[y] = x;
		sz[x] += sz[y];
	}
	else
	{
		parent[x] = y;
		sz[y] += sz[x];
	}
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n ;
	vector<pair<double,pair<CRDNT, CRDNT>>> v(n+1);
	vector<CRDNT> arr;

	for (int i = 0; i < n; i++)
	{
		double a, b;
		cin >> a >> b;
		arr.push_back({ a, b });
		sz[{a, b}] = 1;
		parent[{a,b}] = {a,b};
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i == j)	continue;
			double dist = pow(arr[i].second - arr[j].second, 2) + pow(arr[i].first - arr[j].first, 2);
			v.push_back({ sqrt(dist), { arr[i], arr[j] } });
		}
	}
	sort(v.begin(), v.end());
	double ans = 0;
	for (auto& x : v)
	{
			CRDNT rx = find(x.second.first);
			CRDNT ry = find(x.second.second);
			if (rx == ry)	continue;
			else
			{
				ans += x.first;
				Union(rx, ry);
			}
		
	}
	 cout << fixed<<setprecision(2)<<ans;
}

