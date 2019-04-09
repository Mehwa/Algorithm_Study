/*
	2019.04.09


*/

#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

int N, L, R;
int map[50][50];
int uni[50][50];
int u[2500];
int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };

void input() {
	memset(uni, 0, sizeof(uni));
	memset(map, 0, sizeof(map));
	memset(u, 0, sizeof(u));
	cin >> N >> L >> R;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			cin >> map[r][c];
		}
	}
}

void bfs(int sr, int sc, int uid) {
	queue<pair<int, int>> q;
	q.push({ sr, sc });
	uni[sr][sc] = uid;
	int cnt = 1, pop = map[sr][sc];
	while (q.size()) {
		for (int size = q.size(); size--;) {
			pair<int, int> cur = q.front(); q.pop();
			for (int i = 0; i < 4; i++) {
				int nr = cur.first + dr[i], nc = cur.second + dc[i];
				if (nr < 0 || nr >= N || nc < 0 || nc >= N || uni[nr][nc]) continue;
				int diff = abs(map[cur.first][cur.second] - map[nr][nc]);
				if (diff < L || diff > R) continue;
				uni[nr][nc] = uid;
				q.push({ nr, nc });
				pop += map[nr][nc];
				cnt++;
			}
		}
	}
	u[uid] = pop / cnt;
}

void update() {
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			map[r][c] = u[uni[r][c]];
		}
	}
}

int solve() {
	int cnt = 0, total = N * N;
	while(1) {
		int uid = 1;
		memset(uni, 0, sizeof(uni));
		for (int r = 0; r < N; r++) {
			for (int c = 0; c < N; c++) {
				if (!uni[r][c]) {
					bfs(r, c, uid++);
				}
			}
		}
		update();
		if (uid - 1 == total) break;
		cnt++;
	}
	return cnt;
}

int main() {
	freopen("input16234.txt", "r", stdin);
	input();
	cout<<solve();
}