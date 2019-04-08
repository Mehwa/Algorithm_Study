/*
	2019.04.03
	https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWIeW7FakkUDFAVH&categoryId=AWIeW7FakkUDFAVH&categoryType=CODE
	각 row, col에 대해 오르막길, 내리막길 처리하고 높이 차가 2 이상 나는 곳은 예외 처리 해준다.
	내리막길에서 범위 벗어나는 걸 체크 안해서 디버깅 오래 걸림
*/

#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int T, N, X;
int map[20][20];

void input() {
	memset(map, 0, sizeof(map));
	cin >> N >> X;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			cin >> map[r][c];
		}
	}
}

int col(int c) {
	int ph = map[0][c];
	int same = 1;
	for (int r = 1; r < N; r++) {
		if (map[r][c] == ph) { same++; continue; }
		else if (abs(map[r][c] - ph) > 1) return 0;
		else if (map[r][c] == ph - 1) {
			ph = map[r][c];
			for (int i = 1; i < X; i++) {
				if (r + i >= N) return 0;
				if (map[r + i][c] != ph) return 0;
			}
			r += X - 1;
			same = 0;
		}
		else if (map[r][c] == ph + 1) {
			if (same < X) return 0;
			same = 1;
		}
		ph = map[r][c];
	}
	return 1;
}

int row(int r) {
	int ph = map[r][0];
	int same = 1;
	for (int c = 1; c < N; c++) {
		if (map[r][c] == ph) { same++; continue; }
		else if (abs(map[r][c] - ph) > 1) return 0;
		else if (map[r][c] == ph - 1) {
			ph = map[r][c];
			for (int i = 1; i < X; i++) {
				if (c + i >= N) return 0;
				if (map[r][c + i] != ph) return 0;
			}
			c += X - 1;
			same = 0;
		}
		else if (map[r][c] == ph + 1) {
			if (same < X) return 0;
			same = 1;
		}
		ph = map[r][c];
	}
	return 1;
}

int airtrip() {
	int rt = 0;
	for (int r = 0; r < N; r++) { // For Row
		rt += row(r);
	}
	for (int c = 0; c < N; c++) { // For Col
		rt += col(c);
	}
	return rt;
}


int main() {
	freopen("input4014.txt", "r", stdin);
	cin >> T;
	for (int t = 1; t <= T; t++) {
		input();
		cout << "#" << t << " " << airtrip() << endl;
	}
}