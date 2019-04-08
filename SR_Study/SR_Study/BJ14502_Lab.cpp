/*
	2019.04.08
	https://www.acmicpc.net/problem/14502
	무식하게 완전탐색으로 가능한 모든 지역에 벽을 세우고
	각 경우의 수에서 BFS로 바이러스 퍼질 수 있는 지역을 계산하여 안전영역을 구하고 최대 값을 찾는다.
*/

#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

int N, M;
int map[8][8];
int tmap[8][8];
bool visit[8][8];
int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };
pair<int, int> v[10];
int total_v = 0, remain = 0, result = 0;

void input() {
	cin >> N >> M;
	remain = N * M;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < M; c++) {
			cin >> map[r][c];
			if (map[r][c] == 2) {
				v[total_v].first = r, v[total_v].second = c;
				total_v++;
			}
			if (map[r][c] == 1) remain--;
		}
	}
}

int bfs(int sr, int sc) {
	int cnt = 1;
	queue<pair<int, int>> q;
	visit[sr][sc] = true;
	q.push({ sr, sc });
	while (!q.empty()) {
		pair<int, int> cur = q.front(); q.pop();
		for (int i = 0; i < 4; i++) {
			int nr = cur.first + dr[i], nc = cur.second + dc[i];
			if (nr < 0 || nr >= N || nc < 0 || nc >= M || visit[nr][nc] || tmap[nr][nc]) continue;
			q.push({ nr, nc });
			tmap[nr][nc] = 2;
			visit[nr][nc] = true;
			cnt++;
		}
	}
	return cnt;
}

int safe(int r1, int c1, int r2, int c2, int r3, int c3) {
	memset(visit, false, sizeof(visit));
	memcpy(tmap, map, sizeof(map));
	tmap[r1][c1] = 1;
	tmap[r2][c2] = 1;
	tmap[r3][c3] = 1;	
	int nv = 0;
	for (int i = 0; i < total_v; i++) {
		if (!visit[v[i].first][v[i].second]) nv += bfs(v[i].first, v[i].second);
	}
	return remain - nv - 3;
}

void choose() {
	for (int r1 = 0; r1 < N; r1++) {
		for (int c1 = 0; c1 < M; c1++) {
			if (map[r1][c1]) continue;
			for (int r2 = r1; r2 < N; r2++) {
				for (int c2 = 0; c2 < M; c2++) {
					if (map[r2][c2]) continue;
					if (r1 == r2 && c1 == c2) continue;
					for (int r3 = r2; r3 < N; r3++) {
						for (int c3 = 0; c3 < M; c3++) {
							if (map[r3][c3]) continue;
							if (r1 == r3 && c1 == c3) continue;
							if (r2 == r3 && c2 == c3) continue;
							int area = safe(r1, c1, r2, c2, r3, c3);
							result = max(result, area);
						}
					}
				}
			}
		}
	}
}

int main() {
	freopen("input14502.txt", "r", stdin);
	input();
	choose();
	cout << result << endl;
}