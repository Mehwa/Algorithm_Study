/*
	2019.04.11

*/
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

struct CCTV { int r, c, k, d; };
int N, M, result, remain, ntv, ntv5;
int map[8][8];
CCTV tv[8], tv5[8];
int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };
vector<vector<vector<int>>> tvk = { {{0}},
{{0}, {1}, {2}, {3}}, //k=1
{{0, 1}, {0, 1}, {2, 3}, {2, 3}}, //k=2
{{0, 2}, {1, 3}, {1, 2}, {0, 3}}, //k=3
{{0, 2, 3}, {1, 2, 3}, {0, 1, 2}, {0, 1, 3}}, //k=4
{{0, 1, 2, 3}, {0, 1, 2, 3}, {0, 1, 2, 3}, {0, 1, 2, 3}} //k=5
};

void input() {
	cin >> N >> M;
	remain = 0, ntv = 0, ntv5 = 0;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < M; c++) {
			cin >> map[r][c];
			if (map[r][c] == 0) remain++;
			if (1 <= map[r][c] && map[r][c] <= 4) {
				tv[ntv].r = r, tv[ntv].c = c, tv[ntv].k = map[r][c], tv[ntv].d = 0;
				ntv++;
			}
			if (map[r][c] == 5) {
				tv5[ntv5].r = r, tv5[ntv5].c = c, tv5[ntv5].k = map[r][c], tv5[ntv5].d = 0;
				ntv5++;
			}
		}
	}
	result = remain;
}

int search(int sr, int sc, int k, int d) {
	int cnt = 0;
	vector<int> dd = tvk[k][d];
	for (int i = 0; i < dd.size(); i++) {
		int cr = sr, cc = sc;
		int nd = dd[i];
		while (1) {
			int nr = cr + dr[nd], nc = cc + dc[nd];
			if (nr < 0 || nr >= N || nc < 0 || nc >= M || map[nr][nc] == 6) break;
			if (map[nr][nc] == 0) {
				map[nr][nc] = 9;
				cnt++;
			}
			cr = nr, cc = nc;
		}
	}
	return cnt;
}

void dfs(int d) {
	if (d == ntv) {
		int tmap[8][8];
		int cnt = 0;
		memcpy(tmap, map, sizeof(map));
		for (int i = 0; i < ntv; i++) {
			CCTV ctv = tv[i];
			cnt += search(ctv.r, ctv.c, ctv.k, ctv.d);
		}
		result = min(result, remain - cnt);
		memcpy(map, tmap, sizeof(map));
		return;
	}
	for (int i = 0; i < 4; i++) {
		tv[d].d = i;
		dfs(d + 1);
	}
}

int main() {
	freopen("input15683.txt", "r", stdin);
	input();
	//5번 cctv 감시영역 모두 표시
	for (int i = 0; i < ntv5; i++) {
		CCTV ctv = tv5[i];
		remain -= search(ctv.r, ctv.c, ctv.k, ctv.d);
	}
	dfs(0);
	cout << result;
}