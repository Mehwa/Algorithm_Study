/*
	2019.04.11

*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int T, N;
int map[20][20];
bool visit[20][20];
vector<int> cafe;
int result, SR, SC;
int dr[] = { 1, 1, -1, -1 }; //우하, 우좌, 상좌, 상우
int dc[] = { 1, -1, -1, 1 };

void input() {
	result = -1;
	cin >> N;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			cin >> map[r][c];
		}
	}
}

bool already(int cid) {
	for (int i = 0; i < cafe.size(); i++) {
		if (cid == cafe[i]) return true;
	}
	return false;
}

void dfs(int cr, int cc, int t) {
	for (int i = 0; i < 2; i++) {
		if (cr==SR && cc==SC && i == 1) continue; //처음에는 직진만
		if (t == 3 && i == 1) continue; //3번 턴 이후에는 직진만
		int nr = cr + dr[t + i], nc = cc + dc[t + i];
		if (t + i == 3 && nr == SR && nc == SC) {
			result = max(result, (int)cafe.size());
			return;
		}
		if (nr < 0 || nr >= N || nc < 0 || nc >= N || visit[nr][nc] || already(map[nr][nc])) continue;
		visit[nr][nc] = true;
		cafe.push_back(map[nr][nc]);
		dfs(nr, nc, t + i);
		cafe.pop_back();
		visit[nr][nc] = false;
	}
}

int main() {
	freopen("input2105.txt", "r", stdin);
	cin >> T;
	for (int t = 1; t <= T; t++) {
		input();
		for (int r = 0; r < N; r++) {
			for (int c = 1; c < N - 1; c++) {
				memset(visit, false, sizeof(visit));
				cafe.clear();
				SR = r, SC = c;
				visit[SR][SR] = true, cafe.push_back(map[SR][SC]);
				dfs(r, c, 0);
			}
		}
		cout << "#" << t << " " << result << endl;
	}
}