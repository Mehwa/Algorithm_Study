/*
	2019.04.11

*/
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int N, result;
int map[20][20], tmap[20][20];
int m[5];
void input() {
	result = 0;
	cin >> N;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			cin >> map[r][c];
		}
	}
}

void updateR(int r) { // 오른쪽으로 땡겨준다
	int tmp[20];
	int idx = 0;
	for (int c = N - 1; c >= 0; c--) {
		if (tmap[r][c] == 0) continue;
		tmp[idx++] = tmap[r][c];
		tmap[r][c] = 0;
	}
	int idx2 = N - 1;
	for (int i = 0; i < idx; i++) {
		tmap[r][idx2--] = tmp[i];
	}
}

void moveR() {
	for (int r = 0; r < N; r++) {
		updateR(r); //* 땡기고 합치고 땡겨야한다.
		for (int c = N - 1; c > 0; c--) {
			if (tmap[r][c] == tmap[r][c - 1]) { //현재 == 다음
				tmap[r][c] += tmap[r][c - 1];
				tmap[r][c - 1] = 0;
			}
		}
		updateR(r);
	}
}

void updateL(int r){
	int tmp[20];
	int idx = 0;
	for (int c = 0; c <= N - 1; c++) {
		if (tmap[r][c] == 0) continue;
		tmp[idx++] = tmap[r][c];
		tmap[r][c] = 0;
	}
	int idx2 = 0;
	for (int i = 0; i < idx; i++) {
		tmap[r][idx2++] = tmp[i];
	}
}
void moveL() {
	for (int r = 0; r < N; r++) {
		updateL(r);
		for (int c = 0; c < N - 1; c++) {
			if (tmap[r][c] == tmap[r][c + 1]) {
				tmap[r][c] += tmap[r][c + 1];
				tmap[r][c + 1] = 0;
			}
		}
		updateL(r);
	}
}
void updateU(int c) {
	int tmp[20];
	int idx = 0;
	for (int r = 0; r <= N - 1; r++) {
		if (tmap[r][c] == 0) continue;
		tmp[idx++] = tmap[r][c];
		tmap[r][c] = 0;
	}
	int idx2 = 0;
	for (int i = 0; i < idx; i++) {
		tmap[idx2++][c] = tmp[i];
	}
}
void moveU() {
	for (int c = 0; c < N; c++) {
		updateU(c);
		for (int r = 0; r < N - 1; r++) {
			if (tmap[r][c] == tmap[r + 1][c]) {
				tmap[r][c] += tmap[r + 1][c];
				tmap[r + 1][c] = 0;
			}
		}
		updateU(c);
	}
}
void updateD(int c) {
	int tmp[20];
	int idx = 0;
	for (int r = N - 1; r >= 0; r--) {
		if (tmap[r][c] == 0) continue;
		tmp[idx++] = tmap[r][c];
		tmap[r][c] = 0;
	}
	int idx2 = N - 1;
	for (int i = 0; i < idx; i++) {
		tmap[idx2--][c] = tmp[i];
	}
}
void moveD() {
	for (int c = 0; c < N; c++) {
		updateD(c);
		for (int r = N - 1; r > 0; r--) {
			if (tmap[r][c] == tmap[r - 1][c]) {
				tmap[r][c] += tmap[r - 1][c];
				tmap[r - 1][c] = 0;
			}
		}
		updateD(c);
	}
}

int score() {
	int max_score = 0;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			max_score = max(max_score, tmap[r][c]);
		}
	}
	return max_score;
}

void dfs(int d) {
	if (d == 5) {
		memcpy(tmap, map, sizeof(map));
		for (int i = 0; i < 5; i++) {
			if (m[i] == 0) moveU();
			else if (m[i] == 1) moveD();
			else if (m[i] == 2) moveL();
			else moveR();
		}
 		result = max(result, score());
		return;
	}
	for (int i = 0; i < 4; i++) {
		m[d] = i;
		dfs(d + 1);
	}
}

int main() {
	freopen("input12100.txt", "r", stdin);
	input();
	dfs(0);
	cout << result;
}