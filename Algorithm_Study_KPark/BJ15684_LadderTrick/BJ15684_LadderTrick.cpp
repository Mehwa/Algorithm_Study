#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

int N, M, H;
int map[32][12];
int result;

void input() {
	cin >> N >> M >> H;
	for (int i = 0; i < M; i++) {
		int r, c;
		cin >> r >> c;
		map[r][c] = 1;
	}
}

bool ladder(int c) {
	int cc = c;
	for (int r = 1; r <= H; r++) {
		int left = map[r][cc - 1];
		int right = map[r][cc];

		if (left)  cc--;
		if (right) cc++;
	}
	if (cc != c) return false;
	return true;
}

bool check() {
	for (int c = 1; c <= N; c++) {
		if (!ladder(c)) return false;
	}
	return true;
}

bool chooseDFS(int d, int a, int cr) {
	if (d == a) {
		if (check()) return true;
		return false;
	}
	for (int r = cr; r <= H; r++) {
		for (int c = 1; c < N; c++) {
			if (map[r][c - 1] || map[r][c] || map[r][c + 1]) continue;
			map[r][c] = 1;
			if (chooseDFS(d + 1, a, r)) return true;
			map[r][c] = 0;
		}
	}
	return false;
}

int main() {
	freopen("input.txt", "r", stdin);
	result = -1;
	input();
	for (int i = 0; i < 4; i++) {
		if (chooseDFS(0, i, 1)) {
			result = i;
			break;
		}
	}
	cout << result << endl;
}