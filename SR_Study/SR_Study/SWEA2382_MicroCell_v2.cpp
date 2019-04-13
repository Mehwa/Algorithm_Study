#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
int T, N, M, K;
int map[100][100];
struct CELL { int r, c, n, d; };
CELL mc[1000];
int nmc, result;
int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };
int dd[] = { 1, 0, 3, 2 };
void input() {
	result = 0, nmc = 0;
	memset(mc, 0, sizeof(mc));
	memset(map, -1, sizeof(map));
	cin >> N >> M >> K;
	for (int i = 0; i < K; i++) {
		cin >> mc[nmc].r >> mc[nmc].c >> mc[nmc].n >> mc[nmc].d;
		mc[nmc].d--;
		nmc++;
	}
}
void move() {
	for (int i = 0; i < nmc; i++) {
		int nr = mc[i].r + dr[mc[i].d], nc = mc[i].c + dc[mc[i].d];
		if (nr == 0 || nr == N - 1 || nc == 0 || nc == N - 1) { //경계
			mc[i].n /= 2;
			mc[i].d = dd[mc[i].d];
			mc[i].r = nr, mc[i].c = nc;  //* 경계로도 이동은 해야됨
			//map[nr][nc] = i;
			continue;
		}
		if (map[nr][nc] != -1) { //다른 군집 존재
			mc[map[nr][nc]].n += mc[i].n;
			mc[i].n = 0;
			continue;
		}
		map[nr][nc] = i;
		mc[i].r = nr, mc[i].c = nc;
	}
}
void dead() {
	int new_idx = 0;
	for (int i = 0; i < nmc; i++) {
		if (mc[i].n == 0) continue;
		map[mc[i].r][mc[i].c] = -1;
		mc[new_idx++] = mc[i];
	}
	nmc = new_idx;
}
bool comp(CELL a, CELL b) { return a.n > b.n; }
void sim() {
	while (M--) {
		sort(mc, mc + nmc, comp);
		move();
		dead();
	}
}
int sum() {
	int rt = 0;
	for (int i = 0; i < nmc; i++) {
		rt += mc[i].n;
	}
	return rt;
}
int main() {
	freopen("input2382.txt", "r", stdin);
	cin >> T;
	for (int t = 1; t <= T; t++) {
		input();
		sim();
		cout << "#" << t << " " << sum() << endl;
	}
}