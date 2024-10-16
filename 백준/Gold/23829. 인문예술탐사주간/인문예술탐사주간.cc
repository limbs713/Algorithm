#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstdio>
#include <climits>
#define fastio cin.tie(0) -> sync_with_stdio(0)
using namespace std;
vector<int> arr;
vector<long long> sum;
int main() {
    fastio;
    int n, m;
    cin >> n >> m;
    arr.assign(n + 1, 0);
    sum.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    
    sort(arr.begin(), arr.end());

    for (int i = 1; i <= n; i++) {
        sum[i] = sum[i - 1] + arr[i];
    }
    long long curr;
    for (int i = 0; i < m; i++) {
        cin >> curr;
        auto iter = lower_bound(arr.begin(), arr.end(), curr);
        int idx = iter - arr.begin();
        long long ans = (sum[n] - sum[idx - 1]) - (curr * (n - idx + 1)) + curr * (idx - 1) - (sum[idx - 1]);
        cout << ans << '\n';
    }
    
}