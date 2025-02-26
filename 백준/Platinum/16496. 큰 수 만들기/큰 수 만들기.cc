#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct cmp {
	bool operator()(string a, string b) {
		
		return a + b < b + a;
	}
};

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	priority_queue <string, vector<string>, cmp> pq;

	int n, input;
	cin >> n;

	for (int i = 0; i < n; i++)
	{
		cin >> input;
		string s = to_string(input);
		pq.push(s);
	}

	if (pq.top() == "0")
	{
		cout << 0;
		return 0;
	}

	string ans;

	while(pq.size()!=0)
	{
		ans += pq.top();
		pq.pop();
	}

	cout << ans;
}