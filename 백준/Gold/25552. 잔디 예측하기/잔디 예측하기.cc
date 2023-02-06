#include <iostream>
#include <queue>
#include <vector>
using namespace std;
vector<vector<char>> v1;
vector<vector<char>> v2;
int n, m, d;

bool bfs(int row, int col, int idx) {
	bool flag= false;
  if (v1[row][col] == 'O') {
    return true;
  }
  if (idx == d) {
    return false;
  }
  if (row)
    flag=bfs(row - 1, col, idx + 1); //상
  if (flag)	return true;
  if (row < n - 1)
    flag = bfs(row + 1, col, idx + 1); //하
  if (flag)
    return true;
  if (col)
    flag = bfs(row, col - 1, idx + 1); //좌
  if (flag)
    return true;
  if (col < m - 1)
    flag = bfs(row, col + 1, idx + 1); //우
  if (flag)
    return true;
	else
	return false;
}

int main() {

  cin >> n >> m;

  v1.assign(n, vector<char>(m));
  v2.assign(n, vector<char>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> v1[i][j];
    }
  }

  cin >> d;
 
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> v2[i][j];
    }
  }

  bool flag= true;
  while (flag) { // flag가 false라면 업데이트가 끝남
	flag=false;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (v2[i][j] == 'O' && v1[i][j] != v2[i][j]) {
          flag = bfs(i, j, 0);
          if (flag)
            v1[i][j] ='O';
        }
      }
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (v2[i][j] == v1[i][j]) {
        continue;
      } else {
        cout << "NO" << '\n';
        return 0;
      }
    }
  }
  cout << "YES" << '\n';
}