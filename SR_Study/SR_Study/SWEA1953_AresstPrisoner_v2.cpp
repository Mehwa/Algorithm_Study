/*
	2019.04.09


*/

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

int T, N, M, R, C, L;
int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };
int nd[] = { 1, 0, 3, 2 };
vector<vector<int>> t = { {0}, {0, 1, 2, 3}, {0, 1}, {2, 3}, {0, 3}, {1, 3}, {1, 2}, {0, 2} };
int map[50][50];
int dist[50][50];

void input() {
	cin >> N >> M >> R >> C >> L;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < M; c++) {
			cin >> map[r][c];
		}
	}
}

bool IsWay(int cr, int cc, int nr, int nc, int d) {
	bool rt1 = false, rt2 = false;
	int cid = map[cr][cc], nid = map[nr][nc];
	for (int i = 0; i < t[cid].size(); i++) {
		if (t[cid][i] == d) { rt1 = true;  break; }
	}
	for (int i = 0; i < t[nid].size(); i++) {
		if (t[nid][i] == nd[d]) { rt2 = true;  break; }
	}
	return (rt1 && rt2);
}

int bfs(int sr, int sc) {
	memset(dist, 0, sizeof(dist));
	int result = 1;
	queue<pair<int, int>> q;
	q.push({ sr, sc });
	dist[sr][sc] = 1;
	while (q.size()&&--L) {
		for (int size = q.size(); size--;) {
			pair<int, int> cur = q.front(); q.pop();
			for (int i = 0; i < 4; i++) {
				int nr = cur.first + dr[i], nc = cur.second + dc[i];
				if (nr < 0 || nr >= N || nc < 0 || nc >= M || dist[nr][nc] || !map[nr][nc]) continue;
				if (!IsWay(cur.first, cur.second, nr, nc, i)) continue;
				q.push({ nr, nc });
				dist[nr][nc] = dist[cur.first][cur.second] + 1;
				result++;
			}
		}
	}
	return result;
}

int main() {
	freopen("input1953.txt", "r", stdin);
	cin >> T;
	for (int t = 1; t <= T; t++) {
		input();
		cout << "#" << t << " " << bfs(R, C) << "\n";
	}
}