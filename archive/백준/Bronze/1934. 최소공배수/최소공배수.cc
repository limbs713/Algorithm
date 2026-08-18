#include<bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;


int main()
{
	fastio;
	int n;
	cin >> n;

	while (n--) {
		int a, b;
		cin >> a >> b;
		if (a % b == 0 || b % a == 0) {
			cout << max(a, b) << '\n';
			continue;
		}

		int A = a;
		int B = b;
		int temp = a % b;
		while (temp != 0) {
			a = b;
			b = temp;
			temp = a % b;
		}

		cout << A * B / b <<'\n';
	}
}