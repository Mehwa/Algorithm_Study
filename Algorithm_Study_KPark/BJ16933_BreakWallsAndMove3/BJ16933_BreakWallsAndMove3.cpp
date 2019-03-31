/*
 * Author: kpark
 * Date: 2019.03.31
 * Algorithm: BFS
 * Problem: https://www.acmicpc.net/problem/16933
*/

#include <iostream>
#include <queue>
#include <string>
#include <algorithm>
#include <cstring>

using namespace std;

int N, M, K;
int map[1000][1000];
int dist[11][1000][1000];

int dr[] = { 1, -1, 0, 0 };
int dc[] = { 0, 0, 1, -1 };

struct pos {
	int h, r, c;
};

void input() {
	scanf("%d %d %d\n", &N, &M, &K);
	for (int r = 0; r < N; r++) {
		string line;
		getline(cin, line);
		for (int c = 0; c < line.size(); c++) {
			map[r][c] = line[c] - '0';
		}
	}
}

int bfs(int sr, int sc) {
	queue<pos> q;
	q.push({ 0, sr, sc });
	dist[0][sr][sc] = 1;
	bool day = true;
	while (q.size()) {
		for (int size = q.size(); size--;) {
			pos cur = q.front(); q.pop();
			if (cur.r == N - 1 && cur.c == M - 1) {
				return dist[cur.h][cur.r][cur.c];
			}
			bool stay = false;
			for (int i = 0; i < 4; i++) {
				int nr = cur.r + dr[i], nc = cur.c + dc[i];
				if (nr < 0 || nr >= N || nc < 0 || nc >= M) continue;
				if (map[nr][nc] && cur.h < K && !dist[cur.h + 1][nr][nc]) { //wall
					if (day) {
						dist[cur.h + 1][nr][nc] = dist[cur.h][cur.r][cur.c] + 1;
						q.push({ cur.h + 1, nr, nc });
					}
					else { //stay at the night
						stay = true;
					}
				}
				if (!map[nr][nc] && !dist[cur.h][nr][nc]) { //not wall
					dist[cur.h][nr][nc] = dist[cur.h][cur.r][cur.c] + 1;
					q.push({ cur.h, nr, nc });
				}
			}
			if (stay) {
				dist[cur.h][cur.r][cur.c]++;
				q.push(cur);
			}
		}
		day = !day;
	}
	return -1;
}

int main() {
	freopen("input.txt", "r", stdin);
	input();
	cout << (bfs(0, 0)) << endl;
}