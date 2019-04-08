/*
	2019.04.04
	https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRF8s6ezEDFAUo&categoryId=AWXRF8s6ezEDFAUo&categoryType=CODE
	시작위치부터 다음 칸에 따라 웜홀이면 해당 위치로, 블록이면 속성에 따라 방향을 바꾸고 이동하고, 빈칸이면 그냥 이동하며
	블랙홀을 만나거나 시작 위치로 돌아오면 최대값 갱신하고 리턴한다
	블록일 때 방향 전환 쉽게 하기 위해 각 블록 id와 현재 dir 상태에 따른 다음 dir을 block[][]에 저장해 두고 사용했다.
	범위 벗어나는 것 (벽)을 따로 구분하지 않고 사각형인 5를 넣어 해결했다.
	시작 위치와 방향에 대한 완전 탐색할 때, 시작 점이 빈칸 아니거나 해당 방향으로 다음칸 이동했을 때 벽인 경우만 제외 했는데,
	시작점부터 앞으로 가며 빈칸인 공간은 전부 답이 같게 나오므로, 처음에 시작점부터 처음 빈칸이 아닌 곳을 만날때까지 모두 visit[][][]=true 처리해서 해당 칸은 다시 탐색 안하게 하면 더 빠를 것 같다.
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
	if (nval == -1 || nr == sr && nc == sc) { // 블랙홀 or 시작점
		result = max(result, d); //블랙홀 제외
		return;
	}
	else if (6 <= nval && nval <= 10) { //웜홀
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
	else { //빈칸
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