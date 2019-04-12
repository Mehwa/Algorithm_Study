/*
	2019.04.12

*/
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
int N, M, result;
char map[10][10];
int dd[10];
struct POS { int r, c; };
POS R, B, E;
int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };
void input() {
	result = 11;
	cin >> N >> M;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < M; c++) {
			cin >> map[r][c];
			if (map[r][c] == 'R') { R.r = r, R.c = c; };
			if (map[r][c] == 'B') { B.r = r, B.c = c; };
			if (map[r][c] == 'O') { E.r = r, E.c = c; };
		}
	}
}
POS move(int sr, int sc, int d, char c) {
	int cr = sr, cc = sc;
	map[cr][cc] = '.';
	while (1) {
		int nr = cr + dr[d], nc = cc + dc[d];
		if (map[nr][nc] == 'O') return { -1, -1 };
		if (map[nr][nc] != '.') {
			map[cr][cc] = c; return { cr, cc };
		}
		cr = nr, cc = nc;
	}
}
void dfs(int d, POS rr, POS bb) {
	if (d >= result) return;
	if (d == 11) return;
	for (int i = 0; i < 4; i++) {
		char tmap[10][10]; //* 전역변수로 했다 틀림
		memcpy(tmap, map, sizeof(map));
		POS tr = rr, tb = bb;
		rr = move(rr.r, rr.c, i, 'R');
		bb = move(bb.r, bb.c, i, 'B');
		rr= move(rr.r, rr.c, i, 'R');
		bb = move(bb.r, bb.c, i, 'B');
		if (bb.r == -1 && bb.c == -1) {
			rr = tr, bb = tb;
			memcpy(map, tmap, sizeof(map));
			continue;
		}
		if (rr.r == -1 && rr.c == -1) {
			result = min(result, d + 1);
			return;
		}
		dfs(d + 1, rr, bb);
		rr = tr, bb = tb;
		memcpy(map, tmap, sizeof(map));
	}
}
//void dfs(int d) {
//	if (d == 10) {
//		char tmap[10][10]; //* 전역변수로 했다 틀림
//		memcpy(tmap, map, sizeof(map));
//		POS tr = R, tb = B;
//		for (int i = 0; i < 10; i++) {
//			if (i + 1 >= result) break;
//			R = move(R.r, R.c, dd[i], 'R');
//			B = move(B.r, B.c, dd[i], 'B');
//			R = move(R.r, R.c, dd[i], 'R');
//			B = move(B.r, B.c, dd[i], 'B');	
//			if (B.r == -1 && B.c == -1) { //* 동시에 들어가는거
//				break;
//			}
//			if (R.r == -1 && R.c == -1) {
//				result = min(result, i + 1);
//				break;
//			}
//		}
//		R = tr, B = tb;
//		memcpy(map, tmap, sizeof(map));
//		return;
//	}
//	for (int i = 0; i < 4; i++) { //* 방향을 순서대로만 탐색하면 틀림
//		dd[d] = i;
//		dfs(d + 1);
//	}
//}
int main() {
	freopen("input13460.txt", "r", stdin);
	input();
	dfs(0, R, B);
	//dfs(0);
	if (result == 11) cout << -1;
	else cout << result;
}