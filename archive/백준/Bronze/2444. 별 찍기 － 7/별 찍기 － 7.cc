#include <bits/stdc++.h>
using namespace std;

int main() {
		ios::sync_with_stdio(0); cin.tie(0);

		int n;
		cin >> n;
		int h = 2 * n - 1;
		for (int i = 1; i <= h; i++) {
			// 왼쪽 공백
			for (int j = 0; j < abs(n - i); j++)
				cout << ' ';
			// 가운데 별
			int star = n - abs(n - i);
			for (int j = 0; j < 2 * star -1; j++)
				cout << '*';
			cout << '\n';
		}

}
