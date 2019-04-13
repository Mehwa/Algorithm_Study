#include <iostream>
using namespace std;
int N;
int map[101][101], ddc[4][1024];
struct DRAGONCURVE { int r, c, d, g; };
DRAGONCURVE DC[20];
int dr[] = { 0, -1, 0, 1 };
int dc[] = { 1, 0, -1, 0 };

void input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> DC[i].c >> DC[i].r >> DC[i].d >> DC[i].g;
	}
}
void getDC() {
	ddc[0][0] = 0, ddc[1][0] = 1, ddc[2][0] = 2, ddc[3][0] = 3; 
	int idx1 = 1, idx2 = 0, prev = 0;
	for (int gen = 1; gen < 11; gen++) {
		int size = 1 << (gen-1);
		idx2 = idx1 - 1;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < 4; j++) {
				ddc[j][idx1] = (ddc[j][idx2] + 1) % 4; //¿ÞÂÊ È¸Àü
			}
			idx1++, idx2--;
		}
	}
}
void drawDC(DRAGONCURVE cdc) {
	int cr = cdc.r, cc = cdc.c;
	map[cr][cc] = 1;
	int size = 1 << cdc.g;
	for (int i = 0; i < size; i++) {
		int nd = ddc[cdc.d][i];
		int nr = cr + dr[nd], nc = cc + dc[nd];
		map[nr][nc] = 1;
		cr = nr, cc = nc;
	}
}
int countDC() {
	int cnt = 0;
	for (int r = 0; r <= 100; r++) {
		for (int c = 0; c <= 100; c++) {
			if (map[r][c] && map[r + 1][c] && map[r][c + 1] && map[r + 1][c + 1]) cnt++;
		}
	}
	return cnt;
}
int main() {
	freopen("input15685.txt", "r", stdin);
	input();
	getDC();
	for(int i = 0; i < N; i++)
		drawDC(DC[i]);
	cout << countDC();
}