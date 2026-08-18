	#include <bits/stdc++.h>
	#define fastio cin.tie(0)->sync_with_stdio(0)
	using namespace std;
	struct cmp {
		bool operator() (int a, int b)
		{
			return a > b;
		}
	};
	int main()
	{
		fastio;
		int t;
		priority_queue <int> L;
		priority_queue <int, vector<int>, cmp> R;
		cin >> t;

		int n; cin >> n;
		L.push(n);
		std::cout << L.top() << '\n';
	
		for (int i = 1; i < t; i++)
		{
			cin >> n;
		
			if (i % 2 == 0)
				L.push(n);	
			else
				R.push(n);
			
			if (L.top() > R.top())
			{
				R.push(L.top());
				L.pop();
			}

			while (L.size() < R.size())
			{
				L.push(R.top());
				R.pop();
			}
			std::cout << L.top() << '\n';
		}
	}