#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <stack>
#define fastio cin.tie(0) ->sync_with_stdio(0)
using namespace std;


int main() {
	fastio;
	int n;
	cin >> n;
	vector<int> v;
	vector<int> idx(n);
	vector<int> arr(n);
	int temp;
	cin >> temp;
	arr[0] =temp;
	v.push_back(temp);
	idx.push_back(0);
	for (int i = 1; i < n; i++) {
		cin >> temp;
		arr[i]= temp;
		if (v.back() < temp) {
			v.push_back(temp);
			idx[i] = v.size() -1 ;
		}
		else {
			auto it = lower_bound(v.begin(), v.end(), temp);
			idx[i]= it - v.begin();
			*it = temp;
		}
	}

	cout << v.size() << '\n';
	stack <int> s;
	int sz = v.size()-1;
	for (int i = n - 1; i >= 0; i--) {
		if (sz == idx[i]) {
			s.push(arr[i]);
			sz--;
		}
	}

	while(!s.empty()) {
		cout << s.top() << ' ';
		s.pop();
	}
}