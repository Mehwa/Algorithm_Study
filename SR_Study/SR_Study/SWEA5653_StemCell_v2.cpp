/*
	2019.04.09


*/

#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

struct CELL {
	int r, c, l, s, d; // 좌표, 생명력, 번식시간, 죽는시간
	bool alive;
};
//struct DCELL {
//	int r, c, id;
//};
bool comp(CELL a, CELL b) { return a.l > b.l; }
int T, N, M, K;
int cn, dcn; //살아 있는 셀 개수, 죽은 셀 개수
CELL cells[2500];
CELL ncells[2500];
//DCELL dcells[2500];
int map[350][350];
int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };

void input() {
	memset(map, 0, sizeof(map));
	//memset(dcells, 0, sizeof(dcells));
	memset(ncells, 0, sizeof(ncells));
	memset(cells, 0, sizeof(cells));
	cin >> N >> M >> K;
	cn = 0, dcn = 0;
	for (int r = 149; r < N + 149; r++) {
		for (int c = 149; c < M + 149; c++) {
			cin >> map[r][c];
			if (!map[r][c]) continue;
			cells[cn].r = r, cells[cn].c = c, cells[cn].l = map[r][c];
			cells[cn].s = map[r][c] + 1, cells[cn].d = map[r][c] * 2;
			cells[cn].alive = true;
			cn++;
		}
	}
}

void sim() {
	int time = 0;
	while (K--) { 
		time++;
		int size = cn;
		sort(cells, cells + cn, comp); //생명력 높은 순으로 sort
		for (int i = 0; i < size; i++) {
			CELL cur = cells[i];
			if (cur.s == time) { //번식 시간
				for (int i = 0; i < 4; i++) {
					int nr = cur.r + dr[i], nc = cur.c + dc[i];
					if (map[nr][nc]) continue;
					map[nr][nc] = cur.l;
					cells[cn].r = nr, cells[cn].c = nc, cells[cn].l = cur.l;
					cells[cn].s = time + cells[cn].l + 1, cells[cn].d = time + cells[cn].l * 2;
					cells[cn].alive = true;
					cn++;
				}
			}
			if (cur.d == time) { //죽는 시간
				cells[i].alive = false;
				//dcells[dcn].r = cur.r, dcells[dcn].c = cur.c, dcells[dcn].id = i;
				//dcn++;
			}
		}
		int new_cn = 0;
		for (int i = 0; i < cn; i++) {
			if (!cells[i].alive) continue;
			ncells[new_cn++] = cells[i];
		}
		memset(cells, 0, sizeof(cells));
		memcpy(cells, ncells, sizeof(ncells));
		cn = new_cn;

		//for (int i = 0; i < dcn; i++) { // 죽은 셀들 처리
		//	DCELL cur = dcells[i];
		//	//map[cur.r][cur.c] = -1;
		//	CELL tmp;
		//	tmp = cells[cn - 1];
		//	cells[cn - 1] = cells[dcells[i].id];
		//	cells[dcells[i].id] = tmp;
		//	cn--;
		//}
		//dcn = 0;
	}
}

int main() {
	freopen("input5653.txt", "r", stdin);
	cin >> T;
	for (int t = 1; t <= T; t++) {
		input();
		sim();
		cout << "#" << t << " " << cn << "\n";
	}
}