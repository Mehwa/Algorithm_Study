/*
	2019.04.03
	https://www.acmicpc.net/problem/16919
	������ �˾Ҵµ� ���� ������ �ſ� �������.
	��ź�� ��ġ�ǰ� ������ ������ 4�� �ֱ�� �ݺ��ǹǷ�, N�� %4 �� �� ��ŭ�� ������.
	������ ���� ���������� 1�ʿ��� �ݺ��� �ȵǴ� ��찡 �ִ�. 
	���� 2~5�� �ݺ��ȴٰ� �����ϰ� ������ Ǯ�� �ȴ�.
	��, �Ϲ������� A ¦��(������) B ¦�� A ... ������
	���������� C ¦�� A ¦�� B ¦�� A ¦�� B ... �� ��찡 �ִ�.
	ex) 0 . . .
	    . 0 0 .
		0 . . .
*/

#include <iostream>

using namespace std;

int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0,-1, 1 };

int map[200][200]; // map�� ��ź�� ������ �ð� ����

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