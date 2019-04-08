/*
	2019.04.03
	https://www.acmicpc.net/problem/16918
	2초부터 시작해서 짝수 시간에는 폭탄을 설치하고 (현재시간+3) 홀수 시간에는 시간이 지난 폭탄이 터진다.
	주의할 점은 주변 폭탄 터뜨릴 때, 현재 시간에 터져야 할 폭탄을 바로 0으로 만들면 해당 폭탄 주변 폭탄이 안터진다.
	따라서 현재 시간에 터져야 할 폭탄은 그 폭탄이 터질 차례가 되면 터뜨리도록 한다.
*/

#include <iostream>

using namespace std;

int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0,-1, 1 };

int map[200][200]; // map에 폭탄이 터지는 시간 저장

int R, C, N;

void input() {
	cin >> R >> C >> N;
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

void solve() {
	int time = 2;
	while (time <= N) {
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
	solve();
	output();
}