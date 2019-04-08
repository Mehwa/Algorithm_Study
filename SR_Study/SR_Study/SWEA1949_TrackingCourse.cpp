/*
	2019.04.04
	https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5PoOKKAPIDFAUq&categoryId=AV5PoOKKAPIDFAUq&categoryType=CODE
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
	result = 0;
	max_h = 0;
	memset(map, 0, sizeof(map));
	h.clear();
	cin >> N >> K;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			cin >> map[r][c];
			max_h = max(map[r][c], max_h);
		}
	}
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			if (map[r][c] == max_h) h.push_back({ r, c });
		}
	}
}

int dfs(int cr, int cc, int d, bool curved) {
	visit[cr][cc] = true;
	int rt = 0;
	for (int i = 0; i < 4; i++) {
		int nr = cr + dr[i], nc = cc + dc[i];
		if (nr < 0 || nr >= N || nc < 0 || nc >= N || visit[nr][nc]) continue;
		if (map[cr][cc] > map[nr][nc]) {
			rt = max(rt, dfs(nr, nc, d + 1, curved));
		}
		else{
			if (!curved && map[nr][nc] - K < map[cr][cc] && map[cr][cc] - 1 >= 0) {
				int tmp = map[nr][nc];
				map[nr][nc] = map[cr][cc] - 1;
				rt = max(rt, dfs(nr, nc, d + 1, true));
				map[nr][nc] = tmp;
			}
		}
	}
	visit[cr][cc] = false;
	return max(rt, d);
}

int main() {
	freopen("input1949.txt", "r", stdin);
	cin >> T;
	for (int t = 1; t <= T; t++) {
		input();
		for (int i = 0; i < h.size(); i++) {
			result = max(result, dfs(h[i].first, h[i].second, 1, false));
		}
		cout << "#" << t << " " << result << endl;
	}
}