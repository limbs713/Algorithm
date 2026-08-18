#include <bits/stdc++.h>
using namespace std;

int arr[3];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	double price[3];
	double weight[3];
	double gaseongbi[3];

	for (int i = 0; i < 3; i++)
	{
		cin >> price[i] >> weight[i];
		if (price[i] >= 500)
		{
			gaseongbi[i] = weight[i] * 10 / ((price[i] * 10) - 500);
		}
		else
			gaseongbi[i] = weight[i] / price[i] ;
	}

	double mx = -1;
	char ans;
	for (int i=0; i<3;i++)
	{
		if (mx > gaseongbi[i])
			continue;
		else
		{
			mx = gaseongbi[i];
			switch (i)
			{
			case 0: ans = 'S';
				break;
			case 1: ans = 'N'; 
				break;
			case 2: ans = 'U';
				break;
			}
		}
	}
	cout << ans;
}
