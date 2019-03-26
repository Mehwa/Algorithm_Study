/*
 * Solver: kpark
 * Data: 2019.03.26
 * Algorithm: DFS
 * Problem: https://www.acmicpc.net/problem/15683
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

struct cctv {
	int r, c, k, dir;
};

int N, M;
int map[8][8];
int new_map[8][8];
vector<cctv> cc;
int dr[] = { -1, 0, 1, 0 }; // N E S W
int dc[] = { 0, 1, 0, -1 };
int ans;

void input() {
	ans = 987654321;
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			if (0 < map[i][j] && map[i][j] < 6) cc.push_back({ i, j, map[i][j], 0 });
		}
	}
}

int blindArea() {
	int result = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			if (new_map[i][j] == 0) result++;
	return result;
}

void search(int r, int c, int dir) {
	queue<pair<int, int>> q;
	q.push({ r, c });
	while (!q.empty()) {
		pair<int, int> cur = q.front(); q.pop();
		int nr = cur.first + dr[dir], nc = cur.second + dc[dir];
		if (nr < 0 || nr >= N || nc < 0 || nc >= M || map[nr][nc]==6) break;
		else {
			new_map[nr][nc] = -1;
			q.push({ nr, nc });
		}
	}
}

void vision() {
	for (int i = 0; i < cc.size(); i++) {
		if (cc[i].k == 1) search(cc[i].r, cc[i].c, cc[i].dir);
		else if (cc[i].k == 2) {
			search(cc[i].r, cc[i].c, cc[i].dir);
			search(cc[i].r, cc[i].c, (cc[i].dir + 2) % 4);
		}
		else if (cc[i].k == 3) {
			search(cc[i].r, cc[i].c, cc[i].dir);
			search(cc[i].r, cc[i].c, (cc[i].dir + 1) % 4);
		}
		else if (cc[i].k == 4) {
			search(cc[i].r, cc[i].c, cc[i].dir);
			search(cc[i].r, cc[i].c, (cc[i].dir + 1) % 4);
			search(cc[i].r, cc[i].c, (cc[i].dir + 2) % 4);
		}
		else {
			search(cc[i].r, cc[i].c, cc[i].dir);
			search(cc[i].r, cc[i].c, (cc[i].dir + 1) % 4);
			search(cc[i].r, cc[i].c, (cc[i].dir + 2) % 4);
			search(cc[i].r, cc[i].c, (cc[i].dir + 3) % 4);
		}
	}
}

void dfs(int d) {
	if (d == cc.size()) {
		memcpy(new_map, map, sizeof(new_map));
		vision();
		ans = min(ans, blindArea());
		return;
	}
	for (int i = 0; i < 4; i++) { //dir
		cctv cur = cc[d];
		cc[d].dir = i;
		dfs(d + 1);
		cc[d].dir = cur.dir;
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	input();
	dfs(0);
	cout << ans << endl;
}