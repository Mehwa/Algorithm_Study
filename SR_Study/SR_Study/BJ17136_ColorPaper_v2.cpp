#include <iostream>
#include <algorithm>
using namespace std;
int result = 30, total = 0;
int map[10][10];
int b[6] = { 0, 0, 0, 0, 0, 0 };
struct POS { int r, c; };
void input() {
	for (int r = 0; r < 10; r++) {
		for (int c = 0; c < 10; c++) {
			cin >> map[r][c];
			if (map[r][c]) total++;
		}
	}
}
bool IsPossible(int sr, int sc, int i) {
	for (int r = sr; r < sr + i; r++) {
		for (int c = sc; c < sc + i; c++) {
			if (r < 0 || r >= 10 || c < 0 || c >= 10 || !map[r][c]) return false;
		}
	}
	return true;
}
void setPaper(int sr, int sc, int i, int val) {
	for (int r = sr; r < sr + i; r++) {
		for (int c = sc; c < sc + i; c++) {
			map[r][c] = val;
		}
	}
}
POS next_pos(int sr) {
	for (int r = sr; r < 10; r++) {
		for (int c = 0; c < 10; c++) {
			if (map[r][c]) return { r, c };
		}
	}
	return { -1, -1 };
}
void dfs(int d, int sr, int sc, int remain) {
	if (remain == 0) {
		result = min(result, d);
		return;
	}
	for (int i = 1; i <= 5; i++) {
		if (b[i] == 5) continue;
		if (!IsPossible(sr, sc, i)) continue;
		setPaper(sr, sc, i, 0);
		b[i]++;
		POS np = next_pos(sr);
		dfs(d + 1, np.r, np.c, remain - i * i);
		b[i]--;
		setPaper(sr, sc, i, 1);
	}
}
int main() {
	freopen("input17136.txt", "r", stdin);
	input();
	POS init = next_pos(0);
	dfs(0, init.r, init.c, total);
	if(result!=30) cout << result;
	else cout << -1;
}