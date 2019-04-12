/*
	2019.04.12

*/
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
int T, N, result;
struct WH {
	int r1, c1, r2, c2;
};
WH wh[11];
int map[102][102];
int block[6][4] = { {0}, {2, 3, 1, 0}, {1, 3, 0, 2}, {3, 2, 0, 1}, {2, 0, 3, 1}, {2, 3, 0, 1} };
int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };

void input() {
	result = 0;
	memset(wh, 0, sizeof(wh)); //*
	cin >> N;	
	for (int r = 0; r <= N + 1; r++) {
		for (int c = 0; c <= N + 1; c++) {
			if (r == 0 || c == 0 || r == N + 1 || c == N + 1) map[r][c] = 5;
			else {
				cin >> map[r][c];
				if (6 <= map[r][c] && map[r][c] <= 10) {//wh
					int id = map[r][c];
					if (wh[id].r1 == 0 && wh[id].c1 == 0) {
						wh[id].r1 = r, wh[id].c1 = c;
					}
					else {
						wh[id].r2 = r, wh[id].c2 = c;
					}
				}
			}
		}
	}
}
int play(int sr, int sc, int sd) {
	int score = 0;
	int cr = sr, cc = sc, cd = sd; //* cc=sr
	while (1) {
		int nr = cr + dr[cd], nc = cc + dc[cd];
		if (map[nr][nc] == -1 || nr == sr && nc == sc) return score;
		else if (6 <= map[nr][nc] && map[nr][nc] <= 10) {
			int id = map[nr][nc];
			if (nr == wh[id].r1 && nc == wh[id].c1) cr = wh[id].r2, cc = wh[id].c2;
			else cr = wh[id].r1, cc = wh[id].c1;
		}
		else if (1 <= map[nr][nc] && map[nr][nc] <= 5) {
			int bid = map[nr][nc];
			cd = block[bid][cd]; score++;
			cr = nr, cc = nc; //*
		}
		else cr = nr, cc = nc; //*
		
	}
}
void sim() {
	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			if (map[r][c] == 0) {
				for (int i = 0; i < 4; i++) {
					result = max(result, play(r, c, i));
				}
			}
		}
	}
}
int main() {
	freopen("input5650.txt", "r", stdin);
	cin >> T;
	for (int t = 1; t <= T; t++) {
		input();
		sim();
		cout << "#" << t << " " << result << endl;
	}
}