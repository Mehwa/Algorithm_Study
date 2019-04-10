/*
	2019.04.10

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int T, N, K, max_h, result;
int map[8][8];
bool visit[8][8];
vector<pair<int, int>> h;
int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };

void input() {
	memset(map, 0, sizeof(map));
	memset(visit, false, sizeof(visit));
	result = 0, max_h = 0;
	h.clear();
	cin >> N >> K;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			cin >> map[r][c];
			max_h = max(max_h, map[r][c]);
		}
	}
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			if (map[r][c] == max_h) h.push_back({ r, c });
		}
	}
}

void dfs(int cr, int cc, int d, bool curved) {
	visit[cr][cc] = true;
	for (int i = 0; i < 4; i++) {
		int nr = cr + dr[i], nc = cc + dc[i];
		if (nr < 0 || nr >= N || nc < 0 || nc >= N || visit[nr][nc]) continue;
		if (map[nr][nc] >= map[cr][cc] && !curved && abs(map[nr][nc] - map[cr][cc]) <= K - 1) { //다음 지점 높이가 현재보다 크거나 같으면
			int tmp = map[nr][nc];
			map[nr][nc] = map[cr][cc] - 1;
			dfs(nr, nc, d + 1, true);
			map[nr][nc] = tmp;
		}
		if (map[nr][nc] < map[cr][cc]) { // 다음 지점 높이가 현재보다 작으면
			dfs(nr, nc, d + 1, curved);
		}
		else { //더이상 갈 곳 없으면
			result = max(result, d);
		}
	}
	visit[cr][cc] = false;
}

void solve() {
	for (int i = 0; i < h.size(); i++) {
		dfs(h[i].first, h[i].second, 1, false);
	}
}

int main() {
	freopen("input1949.txt", "r", stdin);
	cin >> T;
	for (int t = 1; t <= T; t++) {
		input();
		solve();
		cout << "#" << t << " " << result << endl;
	}
}