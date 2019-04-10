/*
	2019.04.10

*/

#include <iostream>
#include <algorithm>
using namespace std;

int N, M, H;
int map[31][11];
int result;

void input() {
	result = 4;
	cin >> N >> M >> H;
	while(M--){
		int r, c;
		cin >> r >> c;
		map[r][c] = 1;
	}
}

bool check() {
	for (int i = 1; i <= N; i++) { //c
		int c = i;
		for (int r = 1; r <= H; r++) {
			if (map[r][c - 1] == 1) c--; //왼쪽 이동
			else if (map[r][c] == 1) c++; //오른쪽 이동
		}
		if (c != i) return false;
	}
	return true;
}

void dfs(int d, int sr) {
	if (d >= result) return;
	if (d == 3) return;
	for (int r = sr; r <= H; r++) {
		for (int c = 1; c <= N - 1; c++) {
			if (map[r][c] || map[r][c - 1] || map[r][c + 1]) continue; //사다리 이미 존재
			map[r][c] = 1; //사다리 설치
			if (check()) {
				result = min(result, d + 1);
				map[r][c] = 0;
				return;
			}
			dfs(d + 1, r);
			map[r][c] = 0;
		}
	}
}

int main() {
	freopen("input15684.txt", "r", stdin);
	input();
	if (check()) cout << 0;
	else {
		dfs(0, 1);
		if (result == 4) cout << -1;
		else cout << result;
	}
}