#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n;
	int s=0;
	int e = 0;
	int sum = 0;
	int ans = 0;
	cin >> n;

	while (s <= n && e <= n) {
		if (sum < n) {
			sum += ++e;
		}
		else if (sum > n) {
			sum -= s++;
		}
		else {
			ans++;
			sum += ++e;
		}
	}

	cout << ans;
}