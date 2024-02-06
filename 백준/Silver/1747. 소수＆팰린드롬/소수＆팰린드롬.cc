#include<bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int arr[1100001];

bool check(int x) {
	if (x < 0 || (x % 10 == 0 && x != 0)) { // 음수이거나 0이 아닌 0으로 끝나는 수일 경우...
		return false; // 거짓 반환
	}

	int x_rev = 0;
	while (x > x_rev) {
		x_rev = x_rev * 10 + x % 10;
		x /= 10;
	} // 반만 뒤집음

	return x == x_rev || x == x_rev / 10; // x의 길이가 짝수일 때 || 홀수일 때
}

int main()
{
	fastio;
	int n;
	cin >> n;

	for (int i = 2; i <= 1100000; i++)
		arr[i] = i;

	for (int i = 2; i <= 1100; i++)
	{
		if (arr[i] == 0)
			continue;
		for (int j = i*i; j <= 1100000; j +=i)
		{
			arr[j] = 0;
		}
	}

	for (int i = n; i <= 1100000; i++)
	{
		if (arr[i] == 0)
			continue;
		if (check(i))
		{
			cout << i;
			return 0;
		}		
	}
}