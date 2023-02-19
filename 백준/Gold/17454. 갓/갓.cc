#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	
	int t;
	cin >> t;
	while (t--)
	{
		int dh, ds, hd, hs, sd, sh;
		cin >> dh >> ds;
		cin >> hd >> hs;
		cin >> sd >> sh;
		/*for (int i = 1; hd * i <= INT32_MAX && hs * i <= INT32_MAX; i++)
		{
			for (int j = 1; sd * j <= INT32_MAX && sh * j <= INT32_MAX; j++)
			{
				long long a = hd * i + sd * j; //동현
				long long b = dh + sh * j; // 현수 
				long long c = hs * i + ds; // 승원

				if (a > b && a > c)
				{
					check = true;
					break;
				}
				else continue;
			}
			if (check)
				break;
		}
		*/
		if ((hs-hd)*(sh-sd)<sd*hd)
			cout << "GOD" << '\n';
		else
			cout << "KDH" << '\n';
	}
}
