#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int count[26];

int main() {
	fastio;
	int n;
	int m;
	int ans = 0;
	string s;

	cin >> n;
	cin >> m;
	cin >> s;

	int count[26] = {0,};
	int a, c, g, t;
	cin >> a >> c >> g >> t;
	
	int idx = 0;
	
	for (idx; idx < m; idx++) {
		count[s[idx] - 'A']++;
	}
	
	for(--idx; idx < n;idx++){
		if (count['A' - 'A'] >= a && count['C' - 'A'] >= c && count['T' - 'A'] >= t && count['G' - 'A'] >= g) {
			ans++;
		}
		count[s[idx - m +1] - 'A']--;
		count[s[idx +1] - 'A']++;
	}

	cout << ans;
}