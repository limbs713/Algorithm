#include <bits/stdc++.h>
using namespace std;

bool arr[3000001];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int n;
	int l, k, c;
	cin >> n;
	cin >> l >> k;
	cin >> c;
	int cnt = 0; // 현재 영향 끼치는 폭탄 수
	for (int i = 1; i <= n; i++)
	{
		int life;
		cin >> life;
		if (arr[i])
		{
			cnt--;
		}
		if (i <= l)
		{
			if (life + (cnt - i) * k <= 0)
			{
				continue;
			}
			else
			{
				if (c)
				{
					c--;
					cnt++;
					if(i+l<3000001)
					arr[i + l] = true;
				}
				else
				{
					cout << "NO";
					return 0;
				}
			}
		}
		else
		{
			if (life + (cnt - l) * k <= 0)
			{
				continue;
			}
			else
			{
				if (c)
				{
					c--;
					cnt++;
					if (i + l < 3000001)
					arr[i + l] = true;
				}
				else
				{
					cout << "NO";
					return 0;
				}
			}
		}
	}

	cout << "YES";
}
