#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

int T, N, M, R, C, L;
int dy[4] = { 0, 1, 0, -1 };
int dx[4] = { -1, 0, 1, 0 };
vector<vector<int>> t = { {0}, {0, 1, 2, 3}, {0, 2}, {1, 3}, {0, 1}, {1, 2}, {2, 3}, {0, 3} };
int dist[50][50];
int map[50][50];
int result;

void input() {

	result = 0;
	memset(map, 0, sizeof(map));
	memset(dist, 0, sizeof(dist));
	cin >> N >> M >> R >> C >> L;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}
}

bool IsWay(int nx, int ny, int d) {
	if (!map[nx][ny])
		return false;
	int reverse = (d + 2) % 4;
	int t_type = map[nx][ny];
	for (int i = 0; i < t[t_type].size(); i++) {
		if (t[t_type][i] == reverse)
			return true;
	}
	return false;
}

void bfs() {
	queue<pair<int, int>> q;
	result = 1;
	dist[R][C] = 1;
	q.push(make_pair(R, C));
	while (!q.empty()) {
		pair<int, int> cur = q.front();
		q.pop();

		if (dist[cur.first][cur.second] == L)
			break;

		int t_type = map[cur.first][cur.second];
		for (int i = 0; i < t[t_type].size(); i++) {
			int d = t[t_type][i];
			int nx = cur.first + dx[d];
			int ny = cur.second + dy[d];
			if (0 <= nx && nx < N && 0 <= ny && ny < M && !dist[nx][ny] && IsWay(nx, ny, d)) {
				dist[nx][ny] = dist[cur.first][cur.second] + 1;
				q.push(make_pair(nx, ny));
				result++;
			}
		}
	}
}

int main()
{
	freopen("input.txt", "r", stdin);
	cin >> T;
	for (int t = 1; t <= T; t++) {
		input();
		bfs();
		cout << "#" << t << " " << result << endl;
	}
}