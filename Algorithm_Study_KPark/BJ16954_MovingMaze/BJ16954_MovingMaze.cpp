#include <iostream>
#include <cstring>

using namespace std;

int map[8][8];
int dr[] = {-1, -1, 0, 1, 1, 1, 0, -1, 0}; //N NE E SE S SW W NW no
int dc[] = {0, 1, 1, 1, 0, -1, -1, -1, 0};
bool result = false;

void input() {
	char c;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			cin >> c;
			if (c == '#') map[i][j] = 1;
			else map[i][j] = 0;
		}
	}
}

void updateMap() {
	for (int r = 7; r >= 0; r--) {
		for (int c = 0; c < 8; c++) {
			if (r == 7) { map[r][c] = 0; continue; }
			if (map[r][c]) { map[r + 1][c] = 1; map[r][c] = 0; }
		}
	}
}

bool dfs(int cr, int cc) {
	if (map[cr][cc]) return false;
	for (int i = 0; i < 9; i++) {
		int nr = cr + dr[i], nc = cc + dc[i];
		if (0 <= nr && nr < 8 && 0 <= nc && nc < 8 && !map[nr][nc]) {
			if (nr == 0) return true; //if(nr==0&&nc==7) cuz, wall getting down, don't need to check column
			int tmp_map[8][8];
			memcpy(tmp_map, map, sizeof(map));
			updateMap();
			if (dfs(nr, nc)) return true;
			memcpy(map, tmp_map, sizeof(map));
		}
	}
	return false;
}

int main() {
	freopen("input.txt", "r", stdin);
	input();
	if (dfs(7, 0)) cout << 1 << endl;
	else cout << 0 << endl;
}