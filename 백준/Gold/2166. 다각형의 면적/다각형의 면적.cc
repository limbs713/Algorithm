#include<bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main()
{
	fastio;
	int n;
	cin >> n;
	vector<long long> x(n);
	vector<long long> y(n);
	for (int i = 0; i < n; i++) {
		cin >> x[i] >> y[i];
	}
	x.push_back(x[0]);
	y.push_back(y[0]);
	long double s1 = 0;
	for (int i = 0; i < n; i++) {
		s1 += x[i] * y[i + 1];
		s1 -= x[i + 1] * y[i];
	}

	cout << fixed << setprecision(1) << abs(s1) * 0.5;
}