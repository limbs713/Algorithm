	#include <bits/stdc++.h>
	using namespace std;
	const int SZ = 100001;
	int limit[SZ];
	int prize[SZ];

	int main() {
		ios::sync_with_stdio(0); cin.tie(0);

		int n;
		cin >> n;

		for (int i = 0; i < n; i++)
		{
			cin >> limit[i] >> prize[i];
		}

		priority_queue<int> pq;
		pq.push(0);
		long long sum = 0;
		bool check = false;
		for (int i = 0; i < n; i++)
		{
			if (limit[i] < sum) // 상금 상한 초과
			{
				if (check) // 이미 한 번 뺐으
				{
				
					cout << "Zzz";
					return 0;  
				}
				else if(limit[i] < sum - pq.top())  // 빼도 넘으므로 현재 대회 참가 안함.
				{
					check = true;
				}
				else	// 최대값 빼면 안 넘음
				{ 
					if (pq.top() > prize[i])
					{
						sum -= pq.top();
						sum += prize[i];
						pq.pop();
						pq.push(prize[i]);
					}
					check = true;
				}
			}
			else
			{
				sum += prize[i];
				pq.push(prize[i]);
			}
		
		}

		cout << "Kkeo-eok";


	}
