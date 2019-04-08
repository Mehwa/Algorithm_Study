/*
	2019.04.08
	https://www.acmicpc.net/problem/16236
	
*/
#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

int N;
int map[20][20];
int dist[20][20];
int dr[] = { -1, 0, 0, 1 };
int dc[] = { 0, -1, 1, 0 };
struct SHARK {
	int r, c, s, a, t;
};
SHARK bs;
struct POS {
	int d, r, c;
};
struct comp {
	bool operator()(POS a, POS b) {
		if (a.d == b.d) {
			if (a.r == b.r) return a.c > b.c;
			return a.r > b.r;
		}
		return a.d > b.d;
	}
};

void input() {
	cin >> N;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			cin >> map[r][c];
			if (map[r][c] == 9) {
				bs.r = r, bs.c = c, bs.s = 2, bs.a = 0, bs.t = 0;
				map[r][c] = 0;
			}
		}
	}
}

bool bfs(int sr, int sc) {
	memset(dist, 0, sizeof(dist));
	priority_queue<POS, vector<POS>, comp> pq;
	dist[sr][sc] = 1;
	pq.push({ 1, sr, sc });
	while (pq.size()) {
		for (int size = pq.size(); size--;) {
			POS cur = pq.top(); pq.pop();
			for (int i = 0; i < 4; i++) {
				int nr = cur.r + dr[i], nc = cur.c + dc[i], nd = cur.d + 1;
				if (nr < 0 || nr >= N || nc < 0 || nc >= N || dist[nr][nc] || map[nr][nc] > bs.s) continue;
				dist[nr][nc] = nd;
				pq.push({ nd, nr, nc });
			}
		}
		priority_queue<POS, vector<POS>, comp> npq = pq;
		for (int size = npq.size(); size--;) {
			POS cur = npq.top(); npq.pop();
			if (map[cur.r][cur.c] != 0 && map[cur.r][cur.c] < bs.s) { //먹을 수 있는 물고기
				map[cur.r][cur.c] = 0;
				bs.a++;
				if (bs.a == bs.s) bs.s++, bs.a = 0;
				bs.r = cur.r, bs.c = cur.c, bs.t += cur.d - 1;
				return true;
			}
		}
	}
	return false;
}

int main() {
	freopen("input16236.txt", "r", stdin);
	input();
	while(1) {
		if (!bfs(bs.r, bs.c)) break;
	}
	cout << bs.t << "\n";
}