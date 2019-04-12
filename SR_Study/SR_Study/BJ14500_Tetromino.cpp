/*
	2019.04.12

*/
#include <iostream>
#include <algorithm>
using namespace std;
#define NUM_BLOCKS 19
int N, M;
int map[500][500];
int block[NUM_BLOCKS][3] = {{1, 1, 1}, {2, 2, 2}, {1, 2, 3},
{2, 2, 1},{2, 3, 3},{1, 2, 2},{0, 1, 1},{2, 1, 2},
{1, 0, 1},{1, 1, 6},{2, 2, 7},{1, 1, 7},{2, 2, 4},
{1, 1, 2},{2, 2, 3},{2, 1, 1},{3, 2, 2},{2, 3, 2},
{1, 2, 1}
};
int dr[] = { -1, 0, 1, 0, -1, 1, 1, -1 };
int dc[] = { 0, 1, 0, -1, 1, 1, -1, -1 };
void input() {
	cin >> N >> M;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < M; c++) {
			cin >> map[r][c];
		}
	}
}
int score(int sr, int sc, int bid) {
	int sum = map[sr][sc];
	int cr = sr, cc = sc;
	for (int i = 0; i < 3; i++) {
		int nr = cr + dr[block[bid][i]], nc = cc + dc[block[bid][i]];
		if (nr < 0 || nr >= N || nc < 0 || nc >= M) return -1;
		cr = nr, cc = nc;
		sum += map[nr][nc];
	}
	return sum;
}
int solve() {
	int rt = 0;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < M; c++) {
			for (int b = 0; b < NUM_BLOCKS; b++) {
				rt = max(rt, score(r, c, b));
			}
		}
	}
	return rt;
}
int main() {
	freopen("input14500.txt", "r", stdin);
	input();
	cout << solve();
}