/*
	2019.04.03
*/

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

int T, N, M, R, C, L;
int map[50][50];
bool visit[50][50];

int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };

vector<vector<int>> t = { {0}, {0, 1, 2, 3}, {0, 1}, {2, 3}, {0, 3}, {1, 3}, {1, 2}, {0, 2} };

void input() {
	memset(map, 0, sizeof(map));
	memset(visit, false, sizeof(visit));
	cin >> N >> M >> R >> C >> L;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < M; c++) {
			cin >> map[r][c];
		}
	}
}

bool IsWay(int cr, int cc, int nr, int nc, int d) {
	int ctt = map[cr][cc]; //turnel type
	int ntt = map[nr][nc];
	int nd[] = { 1, 0, 3, 2 };
	for (int i = 0; i < t[ctt].size(); i++) {
		if (t[ctt][i] == d) {
			for (int j = 0; j < t[ntt].size(); j++) {
				if (t[ntt][j] == nd[d]) return true;
			}
		}
	}
	return false;
}

int bfs(int sr, int sc) {
	int cnt = 1;
	queue < pair<int, int>> q;
	q.push({ sr, sc });
	visit[sr][sc] = true;
	while (q.size()) {
		if (!--L) break;
		for (int size = q.size(); size--;) {
			pair<int, int> cur = q.front(); q.pop();
			for (int i = 0; i < 4; i++) {
				int nr = cur.first + dr[i], nc = cur.second + dc[i];
				if (nr < 0 || nr >= N || nc < 0 || nc >= M || visit[nr][nc] || !map[nr][nc]) continue;
				if (!IsWay(cur.first, cur.second, nr, nc, i)) continue;
				q.push({ nr, nc });
				visit[nr][nc] = true;
				cnt++;
			}
		}
	}
	return cnt;
}

int main() {
	freopen("input1953.txt", "r", stdin);
	cin >> T;
	for (int t = 1; t <= T; t++) {
		input();
		cout << "#" << t << " " << bfs(R, C) << endl;
	}
}