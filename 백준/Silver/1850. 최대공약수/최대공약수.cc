#include<bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main()
{
	fastio;
	long long n, m;
	cin >> n >> m;
	long long temp = max(n, m);
	n = min(n, m);
	m = temp;


	temp = m % n;
	while (temp != 0) {
		m = n;
		n = temp;
		temp = m % n;
	}
	while(n--)
	cout << 1;
}