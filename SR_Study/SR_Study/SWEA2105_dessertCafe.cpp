/*
	2019.04.04
	https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5VwAr6APYDFAWu&categoryId=AV5VwAr6APYDFAWu&categoryType=CODE
*/
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

int T, N;
int map[20][20];
bool visit[20][20];
vector<int> cafe;
int SR, SC, result;
bool possible;

int dr[] = { 1, 1, -1, -1 };
int dc[] = { 1, -1, -1, 1 };

void input() {
	possible = false;
	memset(map, 0, sizeof(map));
	result = 0;
	//memset(visit, false, sizeof(visit));
	//cafe.clear();
	cin >> N;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			cin >> map[r][c];
		}
	}
}

bool IsExist(int val) {
	for (int i = 0; i < cafe.size(); i++) {
		if (cafe[i] == val) return true;
	}
	return false;
}

void dfs(int cr, int cc, int dir, int rr) {
	if (rr == 4) return;
	if (cr == SR && cc == SC && rr == 3) {
		result = max(result, (int)cafe.size());
		possible = true;
		return;
	}
	for (int i = 0; i < 2; i++) {
		if (rr == 3 && i == 1) continue; //세번 꺾은 이후에는 직진만 함
		int nd = (dir + i) % 4;
		int nr = cr + dr[nd], nc = cc + dc[nd]; 
		if (nr < 0 || nr >= N || nc < 0 || nc >= N || visit[nr][nc] || IsExist(map[nr][nc])) continue;
		visit[nr][nc] = true;
		cafe.push_back(map[nr][nc]);
		if (i == 0) dfs(nr, nc, nd, rr); //직진
		else dfs(nr, nc, nd, rr + 1); //오른쪽 회전
		cafe.pop_back();
		visit[nr][nc] = false;
	}
}
void solve() {
	for (int r = 0; r < N; r++) {
		for (int c = 1; c < N - 1; c++) {
			SR = r, SC = c;
			dfs(r, c, 0, 0);
		}
	}
}

int main() {
	freopen("input2105.txt", "r", stdin);
	cin >> T;
	for (int t = 1; t <= T; t++) {
		input();
		solve();
		if(possible) cout << "#" << t << " " << result << endl;
		else cout << "#" << t << " " << -1 << endl;
	}
}