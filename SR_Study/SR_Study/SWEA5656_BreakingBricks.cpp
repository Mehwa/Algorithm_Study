/*
	2019.04.02
	https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRQm6qfL0DFAUo&categoryId=AWXRQm6qfL0DFAUo&categoryType=CODE
	맵 업데이트 할 때, 큐 사용하는 것과 배열 사용하는 것이 속도 차이가 6배 이상 났다. 498 ms < 3000ms+
	블록 깨지는 것을 처음에 BFS에 리커전을 더해서 구현했는데, 간단히 BFS 방식으로 구현하는 것이 더 빠르다.
*/


#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

struct brick {
	int s;
	bool broken;
};
struct pos {
	int r, c, impact;
};

int T, N, W, H, result, init_block;
brick map[15][12];
bool visit[15][12];
int ball[12];
int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };

void input() {
	result = 987654321;
	init_block = 0;
	cin >> N >> W >> H;
	for (int r = 0; r < H; r++) {
		for (int c = 0; c < W; c++) {
			cin >> map[r][c].s;
			map[r][c].broken = false;
			if (map[r][c].s) init_block++;
		}
	}
}

int updateMap() {
	int brk = 0;
	for (int c = 0; c < W; c++) {
		int remain[15];
		int idx = 0;
		for (int r = H - 1; r >= 0; r--) {
			if (!map[r][c].broken) {
				remain[idx++] = map[r][c].s;
			}
			else if (map[r][c].broken && map[r][c].s) {
				brk++;
			}
			map[r][c].s = 0;
			map[r][c].broken = false;
		}
		int h = H - 1;
		for(int i = 0; i < idx; i++){
			map[h--][c].s = remain[i];
		}
		
		/*queue<int> q;
		for (int r = H; r--;) {
			if (!map[r][c].broken) {
				q.push(map[r][c].s);
			}
			else if (map[r][c].broken && map[r][c].s) {
				brk++;
			}
			map[r][c].s = 0;
			map[r][c].broken = false;
		}
		int h = H - 1;
		while (!q.empty()) {
			map[h--][c].s = q.front(); q.pop();
		}*/
	}
	return brk;
}

void breakBrick(int sr, int sc) {
	map[sr][sc].broken = true;
	queue<pos> q;
	q.push({ sr, sc, map[sr][sc].s });
	visit[sr][sc] = true;
	while (q.size()) {
		for (int size = q.size(); size--;) {
			pos cur = q.front(); q.pop();
			if (cur.impact == 1) continue;
			for (int i = 0; i < 4; i++) {
				for (int j = 1; j < cur.impact; j++) {
					int nr = cur.r + dr[i] * j, nc = cur.c + dc[i] * j;
					if (nr < 0 || nr >= H || nc < 0 || nc >= W || visit[nr][nc]) continue;
					visit[nr][nc] = true;
					q.push({ nr, nc, map[nr][nc].s});
					map[nr][nc].broken = true;
				}
			}
		}
	}
}

void solve() {
	int brk = 0;
	for (int i = 0; i < N; i++) {
		memset(visit, false, sizeof(visit));
		for (int h = 0; h < H; h++) {
			if (map[h][ball[i]].s) {
				breakBrick(h, ball[i]);
				brk += updateMap();
				break;
			}
		}
	}
	result = min(result, init_block - brk);
}

bool chooseBalls(int d) {
	if (d == N) {
		brick tmp[15][12];
		memcpy(tmp, map, sizeof(map));
		solve();
		if (result == 0) return false;
		memcpy(map, tmp, sizeof(map));
		return true;
	}
	for (int i = 0; i < W; i++) {
		ball[d] = i;
		if (!chooseBalls(d + 1)) return false;
	}
	return true;
}

int main() {
	freopen("input.txt", "r", stdin);
	cin >> T;
	for (int t = 1; t <= T; t++) {
		input();
		chooseBalls(0);
		cout << "#" << t << " " << result << endl;
	}
}