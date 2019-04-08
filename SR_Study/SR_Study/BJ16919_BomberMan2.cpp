/*
	2019.04.03
	https://www.acmicpc.net/problem/16919
	쉬운줄 알았는데 예외 때문에 매우 어려웠다.
	폭탄이 설치되고 터지는 과정이 4를 주기로 반복되므로, N을 %4 한 값 만큼만 돌린다.
	주의할 점이 예외적으로 1초에만 반복이 안되는 경우가 있다. 
	따라서 2~5가 반복된다고 생각하고 문제를 풀면 된다.
	즉, 일반적으로 A 짝수(가득참) B 짝수 A ... 이지만
	예외적으로 C 짝수 A 짝수 B 짝수 A 짝수 B ... 인 경우가 있다.
	ex) 0 . . .
	    . 0 0 .
		0 . . .
*/

#include <iostream>

using namespace std;

int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0,-1, 1 };

int map[200][200]; // map에 폭탄이 터지는 시간 저장

int R, C, opt_n;
long long N;

void input() {
	cin >> R >> C >> N;
	opt_n = N % 4;
	if (opt_n == 1) opt_n = 5;
	for (int r = 0; r < R; r++) {
		for (int c = 0; c < C; c++) {
			char a;
			cin >> a;
			if (a == 'O') map[r][c] = 3;
		}
	}
}

void output() {
	for (int r = 0; r < R; r++) {
		for (int c = 0; c < C; c++) {
			if (map[r][c]) cout << 'O';
			else cout << ".";
		}
		cout << endl;
	}
}
void output2() {
	for (int r = 0; r < R; r++) {
		for (int c = 0; c < C; c++) {
			cout << 'O';
		}
		cout << endl;
	}
}

void solve() {
	int time = 2;
	while (time <= opt_n) {
		if (time % 2 == 0) { //set up
			for (int r = 0; r < R; r++) {
				for (int c = 0; c < C; c++) {
					if (!map[r][c]) map[r][c] = time + 3;
				}
			}
		}
		else { // explosion
			for (int r = 0; r < R; r++) {
				for (int c = 0; c < C; c++) {
					if (!map[r][c]) continue;
					if (map[r][c] <= time) {
						map[r][c] = 0;
						for (int i = 0; i < 4; i++) {
							int nr = r + dr[i], nc = c + dc[i];
							if (nr < 0 || nr >= R || nc < 0 || nc >= C || map[nr][nc] == time) continue;
							map[nr][nc] = 0;
						}
					}
				}
			}
		}
		time++;
	}
}

int main() {
	freopen("input16918.txt", "r", stdin);
	input();
	if (N == 1) output();
	else if (N % 2 == 0) output2();
	else {
		solve();
		output();
	}
}