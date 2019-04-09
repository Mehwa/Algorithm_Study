/*
	2019.04.09
	

*/

#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int T, N;
int map[12][12];
int n_core, max_core, min_line;
int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };
struct CORE {
	int r, c;
};
CORE cc[12];

void input() {
	memset(map, 0, sizeof(map));
	memset(cc, 0, sizeof(cc));
	cin >> N;
	n_core = 0, max_core = 0, min_line = 987654321;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			cin >> map[r][c];
			if (map[r][c] && r != 0 && c != 0 && r != N - 1 && c != N - 1) {
				cc[n_core].r = r, cc[n_core].c = c;
				n_core++;
			}
		}
	}
}

int possible(int sr, int sc, int d) {
	bool rt = true;
	int nr = sr, nc = sc;
	while (1) {
		nr = nr + dr[d], nc = nc + dc[d];
		if (nr < 0 || nr >= N || nc < 0 || nc >= N) break;
		if (map[nr][nc]) {
			rt = false;
			break;
		}
	}
	return rt;
}

int connectLine(int sr, int sc, int d, int val) {
	int nr = sr, nc = sc;
	int length = 0;
	while (1) {
		nr = nr + dr[d], nc = nc + dc[d];
		if (nr < 0 || nr >= N || nc < 0 || nc >= N) break;
		map[nr][nc] = val;
		length++;
	}
	return length;
}

void dfs(int d, int connected, int length) {
	if (d == n_core) {
		if (connected > max_core) {
			max_core = connected;
			min_line = length;
		}
		else if (connected == max_core) {
			min_line = min(min_line, length);
		}
		return;
	}
	for (int i = 0; i < 4; i++) {
		if (!possible(cc[d].r, cc[d].c, i)) continue;
		int line = connectLine(cc[d].r, cc[d].c, i, 1);
		dfs(d + 1, connected + 1, length + line);
		connectLine(cc[d].r, cc[d].c, i, 0);
	}
	dfs(d + 1, connected, length); // 네 방향 모두 연결 못하면
}

int main() {
	freopen("input1767.txt", "r", stdin);
	cin >> T;
	for (int t = 1; t <= T; t++) {
		input();
		dfs(0, 0, 0);
		cout << "#" << t << " " << min_line << "\n";
	}
}