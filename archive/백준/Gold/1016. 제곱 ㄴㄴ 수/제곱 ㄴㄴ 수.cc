#include<bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int arr[1100001];
int ans[1000001];
int main()
{
	fastio;
	long long mn, mx;
	cin >> mn >> mx;

	long long sqrt_max = sqrt(mx);
	long long cnt = mx - mn + 1;

	for (long long i = 2; i <= sqrt_max; i++) {
		long long curr = i * i;
		long long plus = curr;
		curr = (mn / curr) * curr;
		if (mn > curr)
			curr += plus;
		while (curr <= mx) {
			if (mn > curr)
				break;
			if (ans[curr - mn + 1] == 0) {
				ans[curr - mn + 1] = 1;
				cnt--;
			}
			curr += plus;
		}
	}

	cout << cnt;
}
