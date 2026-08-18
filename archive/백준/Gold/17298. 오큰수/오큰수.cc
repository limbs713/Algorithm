#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int v[1000000];
int arr[1000000];
int main() {
	fastio;
	int n;
	stack <pair<int,int>> s;
	cin >> n;
	cin >> v[0];
	s.push({ v[0],0 });
	arr[0] = -1;
	for (int i = 1; i < n; i++) {
		cin >> v[i];

		if (s.top().first > v[i]) {
			s.push({v[i], i});
			arr[i] = -1;
			continue;
		}

		while (!s.empty() && s.top().first < v[i]) {
			arr[s.top().second] = v[i];
			s.pop();
		}

		s.push({v[i],i});
		arr[i] = -1;
	}
	for (int i = 0; i < n;i++) {
		cout << arr[i] << " ";
	}
}