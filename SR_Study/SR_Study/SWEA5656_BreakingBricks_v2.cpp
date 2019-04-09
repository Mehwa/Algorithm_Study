/*
	2019.04.09


*/

#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int T, N, W, H;
int map[15][12];
int tmap[15][12];
int bb[4];
bool e[15][12];
int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };
int total, exploded, result;

void input() {
	total = 0, exploded = 0, result = 987654321;
	memset(map, 0, sizeof(map));
	memset(e, false, sizeof(e));
	cin >> N >> W >> H;
	for (int r = 0; r < H; r++) {
		for (int c = 0; c < W; c++) {
			cin >> map[r][c];
			if (map[r][c]) total++;
		}
	}
}

void update() {
	for (int c = 0; c < W; c++) {
		int tmp[15];
		int idx = 0;
		for (int r = H - 1; r >= 0; r--) {
			if (e[r][c] && tmap[r][c]) exploded++; //*
			if (!e[r][c] && tmap[r][c]) {
				tmp[idx++] = tmap[r][c];
			}
			tmap[r][c] = 0;
			e[r][c] = false;
		}
		int h = H - 1;
		for (int r = 0; r < idx; r++) {
			tmap[h--][c] = tmp[r];
		}
	}
}

void bomb(int sr, int sc) {
	int dist = tmap[sr][sc] - 1;
	e[sr][sc] = true;
	while (dist > 0) {
		for (int i = 0; i < 4; i++) {
			int nr = sr + dr[i] * dist, nc = sc + dc[i] * dist;
			if (nr < 0 || nr >= H || nc < 0 || nc >= W) continue;
			if (tmap[nr][nc] > 1 && !e[nr][nc])	bomb(nr, nc); //이미 터진거 제외 //*
			if (tmap[nr][nc] == 1) e[nr][nc] = true; //*
		}
		dist--;
	}
}

void drop(int w) {
	int h = 0;
	for (int r = 0; r < H; r++) {
		if (tmap[r][w] > 0) { h = r; break; }
	}
	bomb(h, w);
}

void dfs(int d) {
	if (d == N || total == exploded) {
		exploded = 0;
		memcpy(tmap, map, sizeof(map));
		for (int i = 0; i < N; i++) {
			drop(bb[i]); update();
		}
		result = min(result, total - exploded); //이미 다 부서졌으면 탐색 그만해라
		return;
	}
	for (int i = 0; i < W; i++) {
		bb[d] = i;
		dfs(d + 1);
	}
}

int main() {
	freopen("input5656.txt", "r", stdin);
	cin >> T;
	for (int t = 1; t <= T; t++) {
		input();
		dfs(0);
		cout << "#" << t << " " << result << "\n";
	}
}