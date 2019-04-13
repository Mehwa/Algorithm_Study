#include <iostream>
using namespace std;
int T, N, result;
int map[16][16];
bool visit[16][16];
int dr[] = { 0, 1, 1 };
int dc[] = { 1, 0, 1 };
int dd[3][3] = { {0, 2, -1}, {1, 2, -1}, {0, 1, 2} };
void input() {
	cin >> N;
	result = 0;
	for (int r = 0; r < N; r++)
		for (int c = 0; c < N; c++)
			cin >> map[r][c];
}
bool IsWay(int r, int c, int d) {
	if (map[r][c]) return false;
	if(d==2 && (map[r-1][c] || map[r][c-1])) return false;
	return true;
}
void dfs(int cr, int cc, int cd) {
	if (cr == N - 1 && cc == N - 1) {
		result++;
		return;
	}
	for (int i = 0; i < 3; i++) {
		int nd = dd[cd][i];
		if (nd == -1) continue;
		int nr = cr + dr[nd], nc = cc + dc[nd];
		if (nr < 0 || nr >= N || nc < 0 || nc >= N || visit[nr][nc] || !IsWay(nr, nc, nd)) continue;
		visit[nr][nc] = true;
		dfs(nr, nc, nd);
		visit[nr][nc] = false;
	}
}
int main() {
	freopen("input17070.txt", "r", stdin);
	input();
	dfs(0, 1, 0);
	cout << result;
}