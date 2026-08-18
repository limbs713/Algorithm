#include <iostream>
#include <cstring>
#include <queue>
#define fastio cin.tie(0) ->sync_with_stdio(0)
using namespace std;
//red,blue의 y,x 좌표 순
int dp[11][11][11][11];
char board[11][11];
int dx[4] = {-1,1,0,0};
int dy[4] = {0,0,-1,1};

struct Locate {
	int y;
	int x;
};

Locate move(Locate ball, int move_idx, Locate rival) {
	int next_x = ball.x;
	int next_y = ball.y;
	while (1) {
		int temp_x = next_x + dx[move_idx];
		int temp_y = next_y + dy[move_idx];
		char next = board[temp_y][temp_x];
		// 상대편 볼이 어딨는 지 알아야 함.
		// 앞선 공이 red이고 hole에 있는 상황 예외 처리 필요함
		if (next == 'O')
		{
			ball.x = temp_x;
			ball.y = temp_y;
			return ball;
		}
		else if (next == '#' || rival.x == temp_x && rival.y == temp_y) {
			break;
		}
		// next == '.'
		else {
			next_x = temp_x;
			next_y = temp_y;
		}
	}

	ball.x = next_x;
	ball.y = next_y;

	return ball;
}

bool order(Locate red, Locate blue, int move_idx) {
	if (move_idx == 0) {
		return red.x < blue.x;
	}
	else if (move_idx == 1) {
		return red.x > blue.x;
	}
	else if (move_idx == 2)
	{
		return red.y < blue.y;
	}
	else {
		return red.y > blue.y;
	}
}

int main() {
	fastio;
	memset(dp, -1, sizeof dp);
	int n, m;
	cin >> n >> m;

	Locate red;
	Locate hole;
	Locate blue;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> board[i][j];
			if (board[i][j] == 'O') {
				hole.x = j;
				hole.y = i;
			}
			else if (board[i][j] == 'R') {
				red.x = j;
				red.y = i;
			}
			else if (board[i][j] == 'B') {
				blue.x = j;
				blue.y = i;
			}
		}
	}

	//red blue 순
	queue<pair<Locate, Locate>> q;
	dp[red.y][red.x][blue.y][blue.x] = 0;
	q.push({ red,blue });
	while (!q.empty()) {
		Locate curr_r = q.front().first;
		Locate curr_b = q.front().second;
		q.pop();

		//좌우상하 순서로 진행
		for (int i = 0; i < 4; i++) {
			Locate first;
			Locate second;

			// 누가 더 특정 방향에 대해 앞서있는 지 결정
			bool flag = order(curr_r, curr_b, i);
			// red, blue 순
			if (flag) {
				first = curr_r;
				second = curr_b;

				first = move(first, i, second);
				second = move(second, i, first);
				// 뒤의 구슬이 블루일 때 홀에 들어가면 바로 continue;
				if (second.x == hole.x && second.y == hole.y)
					continue;
				// 둘 다 제자리라면 continue
				if (first.x == curr_b.x && first.y == curr_b.y && second.x == curr_r.x && second.y == curr_r.y)
					continue;

				// 만약 이동한 좌표의 dp가  -1이 아니라면 갱신하지 않음 + queue에 안 넣음
				int next_dp = dp[first.y][first.x][second.y][second.x];
				int curr_dp = dp[curr_r.y][curr_r.x][curr_b.y][curr_b.x];
				if (next_dp != -1 && next_dp < curr_dp + 1)
					continue;

				dp[first.y][first.x][second.y][second.x] = curr_dp + 1;
				// 앞선 구슬이 레드일 때 홀에 들어가면 갱신 후 queue에 push하지 않음.
				if (first.x == hole.x && first.y == hole.y)
					continue;

				q.push({ first,second });
			}
			// blue, red 순
			else {
				first = curr_b;
				second = curr_r;

				first = move(first, i, second);
				// 앞선 구슬이 블루일 때 홀에 들어가면 바로 continue;
				if (first.x == hole.x && first.y == hole.y)
					continue;
				second = move(second, i, first);
				// 둘 다 제자리라면 continue
				if (first.x == curr_b.x && first.y == curr_b.y && second.x == curr_r.x && second.y == curr_r.y)
					continue;

				// 만약 이동한 좌표의 dp가  -1이 아니라면 갱신하지 않음 + queue에 안 넣음
				int next_dp = dp[second.y][second.x][first.y][first.x];
				int curr_dp = dp[curr_r.y][curr_r.x][curr_b.y][curr_b.x];
				if (next_dp != -1 && next_dp < curr_dp + 1)
					continue;

				dp[second.y][second.x][first.y][first.x] = curr_dp + 1;

				// 뒤의 구슬이 레드일 때 홀에 들어가면 갱신 후 queue에 push하지 않음.
				if (second.x == hole.x && second.y == hole.y)
					continue;

				q.push({ second,first });
			}
		}
	}

	int ans = 2e9;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (dp[hole.y][hole.x][i][j] == -1)
				continue;
			ans = min(ans, dp[hole.y][hole.x][i][j]);
		}
	}

	if (ans > 10)
		cout << -1;
	else
		cout << ans;
}