/*
	2019.04.10

*/

#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

char map[12][6];
int group[12][6];
int N = 12, M = 6, min_r;
int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };
vector<int> ex; //터질 그룹 저장

void input() {
	bool first = true;
	ex.clear();
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < M; c++) {
			cin >> map[r][c];
			if (first && map[r][c] != '.') {
				min_r = r;
				first = false;
			}
		}
	}
}
bool bfs(int sr, int sc, int gid) {
	int cnt = 1;
	queue<pair<int, int>> q;
	q.push({ sr, sc });
	group[sr][sc] = gid;
	while (!q.empty()) {
		pair<int, int> cur = q.front(); q.pop();
		for (int i = 0; i < 4; i++) {
			int nr = cur.first + dr[i], nc = cur.second + dc[i];
			if (nr < 0 || nr >= N || nc < 0 || nc >= M || group[nr][nc] || map[cur.first][cur.second] != map[nr][nc]) continue;
			q.push({ nr, nc });
			group[nr][nc] = gid;
			cnt++;
		}
	}
	if (cnt >= 4) {
		ex.push_back(gid); return true;
	}
}
bool findGroup() {
	bool rt = false;
	int gid = 1;
	memset(group, 0, sizeof(group));
	for (int r = min_r; r < N; r++) {
		for (int c = 0; c < M; c++) {
			if (!group[r][c] && map[r][c] != '.') {
				if(bfs(r, c, gid++)) rt = true;
			}
		}
	}
	return rt;
}
void explode() {
	for (int r = min_r; r < N; r++) {
		for (int c = 0; c < M; c++) {
			for (int k = 0; k < ex.size(); k++) {
				if (group[r][c] == ex[k]) map[r][c] = '.';
				min_r = min(min_r, r);
			}
		}
	}
	ex.clear();
}
void updateMap() {
	for (int c = 0; c < M; c++) {
		char tmp[12];
		int h = 0;
		for (int r = N - 1; r >= min_r; r--) {
			tmp[h++] = map[r][c];
			map[r][c] = '.';
		}
		int idx = N - 1;
		for (int i = 0; i < h; i++) {
			if (tmp[i] == '.') continue;
			map[idx--][c] = tmp[i];
		}
	}
}
int solve() {
	int cnt = 0;
	while (1) {
		if (!findGroup()) break;
		explode();
		updateMap();
		cnt++;
	}
	return cnt;
}

int main() {
	freopen("input11559.txt", "r", stdin);
	input();
	cout << solve();
}