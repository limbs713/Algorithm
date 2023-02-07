#include <bits/stdc++.h>
using namespace std;
bool num[10];

int search_up(int n)
{
	int cnt = 0;
	int mv;
	bool check;
	do
	{
		check = true;
		mv = n;
		if (n ==100)
			break;
		int size = 0;
		do
		{
			if (num[mv % 10])
			{
				mv /= 10;
				size++;
			}
			else
			{
				check = false;
				n++;
				cnt++;
				break;
			}
		} while (mv);
		if (check)	cnt += size;
		if (n > 1000004) break;
	} while (!check);
	return cnt;
}

int search_down(int n)
{
	int cnt = 0;
	int mv;
	bool check;
	do
	{
		check = true;
		mv = n;

		if (100 == mv)
			break;
		int size = 0;
		do
		{
			if (num[mv % 10])
			{
				mv /= 10;
				size++;
			}
			else
			{
				check = false;
				n--;
				cnt++;
				break;
			}
		} while (mv);
		if (check)	cnt += size;
		if (n < -500004)	break;
	} while (!check);
	return cnt;
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int n;
	cin >> n;
	int remote;
	cin >> remote;

	memset(num, true, sizeof num);

	for (int i = 0; i < remote; i++)
	{
		int temp;
		cin >> temp;
		num[temp] = false;
	}
	cout << min(abs(100-n), min(search_up(n), search_down(n)));
	return 0;
}
