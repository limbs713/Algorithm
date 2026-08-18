#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;


bool cmp(int a, int b) {
    // 둘 다 양수거나 음수인 경우
    if ((a >= 0 && b >= 0) ) {
        return a > b;
    }
	else if (a < 0 && b < 0)
	{
		return a < b;
	}
    // a가 음수이고 b가 양수인 경우
    else if (a < 0 && b >= 0) {
        return false;
    }
    // a가 양수이고 b가 음수인 경우
    else {
        return true;
    }
}

int main() {
	fastio;
	int n,zero=0;
	cin >> n;
	vector<int> v(n);
	vector<int> ans;

	for (int i = 0; i < n; i++) {
		cin >> v[i];
		if (v[i] == 0)
			zero++;
	}

	sort(v.begin(), v.end(),cmp);

	for (int i = 0; i < n; i++) {
		if (i == n - 1) {
			ans.push_back(v[i]);
			break;
		}
		if (v[i] == 0)
		{
			if (i + zero < n && (n - i - zero) % 2 != 0) {
				n--;
			}
			zero--;
		}
		else if (i+1 < n && v[i] + v[i+1] < v[i]*v[i+1])
		{
			ans.push_back(v[i] * v[i + 1]);
			i = i + 1;
		}
		else
			ans.push_back(v[i]);
	}
	int sum = 0;
	for (auto& a : ans) {
		sum += a;
	}

	cout << sum;
}
