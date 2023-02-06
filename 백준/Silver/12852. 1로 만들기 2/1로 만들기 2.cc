#include <bits/stdc++.h>
using namespace std;

int dp[1000001];
int parent[1000001];

void printPath(int n) {
  if (n == 1) {
    cout << "1 ";
    return;
  }

  cout << n << " ";
  int p = parent[n];
  printPath(p);
}

int minSteps(int n) {
  if (n == 1) return 0;
  if (dp[n] != -1) return dp[n];

  int res = INT_MAX, min_idx = -1;
  if (n % 3 == 0) {
    int steps = minSteps(n/3);
    if (steps < res) {
      res = steps;
      min_idx = n/3;
    }
  }
  if (n % 2 == 0) {
    int steps = minSteps(n/2);
    if (steps < res) {
      res = steps;
      min_idx = n/2;
    }
  }
  int steps = minSteps(n-1);
  if (steps < res) {
    res = steps;
    min_idx = n-1;
  }

  parent[n] = min_idx;
  dp[n] = 1 + res;
  return dp[n];
}

int main() {
  memset(dp, -1, sizeof dp);
  int n;
  cin >> n;
  int steps = minSteps(n);
  cout << steps << endl;
  printPath(n);
  cout << endl;
  return 0;
}
