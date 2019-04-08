/*
	2019.04.04
	https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRF8s6ezEDFAUo&categoryId=AWXRF8s6ezEDFAUo&categoryType=CODE
	������ġ���� ���� ĭ�� ���� ��Ȧ�̸� �ش� ��ġ��, ����̸� �Ӽ��� ���� ������ �ٲٰ� �̵��ϰ�, ��ĭ�̸� �׳� �̵��ϸ�
	��Ȧ�� �����ų� ���� ��ġ�� ���ƿ��� �ִ밪 �����ϰ� �����Ѵ�
	����� �� ���� ��ȯ ���� �ϱ� ���� �� ��� id�� ���� dir ���¿� ���� ���� dir�� block[][]�� ������ �ΰ� ����ߴ�.
	���� ����� �� (��)�� ���� �������� �ʰ� �簢���� 5�� �־� �ذ��ߴ�.
	���� ��ġ�� ���⿡ ���� ���� Ž���� ��, ���� ���� ��ĭ �ƴϰų� �ش� �������� ����ĭ �̵����� �� ���� ��츸 ���� �ߴµ�,
	���������� ������ ���� ��ĭ�� ������ ���� ���� ���� �����Ƿ�, ó���� ���������� ó�� ��ĭ�� �ƴ� ���� ���������� ��� visit[][][]=true ó���ؼ� �ش� ĭ�� �ٽ� Ž�� ���ϰ� �ϸ� �� ���� �� ����.
*/

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int T, N, result;
int map[102][102];
int sr, sc;
struct WH {
	int r1, c1, r2, c2;
};
WH wh[5];

int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };
int block[6][4] = { {0}, {1, 3, 0, 2}, {3, 0, 1, 2}, {2, 0, 3, 1}, {1, 2, 3, 0}, {1, 0, 3, 2} };

void input() {
	result = 0;
	memset(map, 0, sizeof(map));
	memset(wh, 0, sizeof(wh));
	cin >> N;
	for (int r = 0; r <= N + 1; r++) {
		for (int c = 0; c <= N + 1; c++) {
			if (r == 0 || c == 0 || r == N + 1 || c == N + 1) {
				map[r][c] = 5; continue;
			}
			cin >> map[r][c];
			if (6 <= map[r][c] && map[r][c] <= 10) {
				int idx = map[r][c] - 6;
				if(wh[idx].r1==0)
					wh[idx].r1 = r, wh[idx].c1 = c;
				else
					wh[idx].r2 = r, wh[idx].c2 = c;
			}
		}
	}
}

void play(int cr, int cc, int dir, int d) {
	int nr = cr + dr[dir], nc = cc + dc[dir];
	int nval = map[nr][nc];
	if (nval == -1 || nr == sr && nc == sc) { // ��Ȧ or ������
		result = max(result, d); //��Ȧ ����
		return;
	}
	else if (6 <= nval && nval <= 10) { //��Ȧ
		int idx = nval - 6;
		if (nr == wh[idx].r1 && nc == wh[idx].c1)
			nr = wh[idx].r2, nc = wh[idx].c2;
		else
			nr = wh[idx].r1, nc = wh[idx].c1;
		play(nr, nc, dir, d);
	}
	else if (1 <= nval && nval <= 5) { //block
		dir = block[nval][dir];
		play(nr, nc, dir, d + 1);
	}
	else { //��ĭ
		play(nr, nc, dir, d);
	}
}

void solve() {
	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			for (int d = 0; d < 4; d++) {
				if (map[r][c] == 0) {
					int nr = r + dr[d], nc = c + dc[d];
					if (nr == 0 || nc == 0 || nr == N + 1 || nc == N + 1) continue;
					sr = r, sc = c;
					play(r, c, d, 0);
				}
			}
		}
	}
}

int main() {
	freopen("input5650.txt", "r", stdin);
	cin >> T;
	for (int t = 1; t <= T; t++) {
		input();
		solve();
		cout << "#" << t << " " << result << endl;
	}
}