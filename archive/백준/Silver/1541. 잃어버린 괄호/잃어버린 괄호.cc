#include<bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main()
{
	fastio;
	char c;
	int temp = 0;
	int sum = 0;
	int temp_sum = 0;
	bool minus = false;
	while (cin >> c) {
		if (isdigit(c)) {
			temp *= 10;
			temp += c - '0';
		}
		else
		{
			if (c == '-')
			{
				if (minus)
				{
					temp_sum += temp;
					sum += -temp_sum;
					temp_sum = 0;
					temp = 0;
				}
				else {
					minus = true;
					sum += temp;
					temp = 0;
				}
			}
			else
			{
				if (minus)
				{
					temp_sum += temp;
					temp = 0;
				}
				else {
					sum += temp;
					temp = 0;
				}
			}
		}
	}

	if (minus)
	{
		temp_sum += temp;
		sum += -temp_sum;
	}
	else {
		sum += temp;
	}

	cout << sum;
}