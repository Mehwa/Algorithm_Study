/*
	2019.04.08
	

*/

#include <iostream>
#include <cstring>

using namespace std;

struct CMD {
	int mid, d;
};

int T, K;
int m[5][8];
bool v[5];
CMD cmd[20];

void input() {
	cin >> K;
	for (int i = 1; i <= 4; i++) {
		for (int j = 0; j < 8; j++) {
			cin >> m[i][j];
		}
	}
	for (int i = 0; i < K; i++) {
		cin >> cmd[i].mid >> cmd[i].d;
	}
}

void rotateR(int s) {
	int tmp = m[s][7];
	for (int i = 7; i > 0; i--) {
		m[s][i] = m[s][i - 1];
	}
	m[s][0] = tmp;
}
void rotateL(int s) {
	int prev = m[s][7];
	for (int i = 7; i > 0; i--) {
		int next = m[s][i - 1];
		m[s][i - 1] = prev;
		prev = next;
	}
	m[s][7] = prev;
}

void sim(int s, int d) { //시작 위치, 방향
	v[s] = true;
	int left = s - 1, right = s + 1;
	if (s < 4 && !v[right] && m[s][2] != m[right][6])
		sim(right, -d);
	if (s > 1 && !v[left] && m[s][6] != m[left][2])
		sim(left, -d);
	if (d == 1) rotateR(s);
	else rotateL(s);
}
int score() {
	return m[1][0] + m[2][0] * 2 + m[3][0] * 4 + m[4][0] * 8;
}

int main() {
	freopen("input4013.txt", "r", stdin);
	cin >> T;
	for (int t = 1; t <= T; t++) {
		input();
		for (int k = 0; k < K; k++) {
			memset(v, false, sizeof(v));
			sim(cmd[k].mid, cmd[k].d);
		}
		cout << "#" << t << " " << score() << "\n";
	}
}