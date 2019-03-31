/*
 * Author: kpark
 * Date: 2019.03.31
 * Algorithm: BFS
 * Problem: https://www.acmicpc.net/problem/2206
*/

#include <iostream>
#include <queue>
#include <string>
#include <algorithm>
#include <cstring>

using namespace std;

int N, M;
int map[1000][1000];
int dist[2][1000][1000];

int dr[] = { 1, -1, 0, 0 };
int dc[] = { 0, 0, 1, -1 };

struct pos {
	int h, r, c;
};

void input() {
	scanf("%d %d\n", &N, &M);
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
	q.push({ 0, sr, sc});
	dist[0][sr][sc] = 1;
	while (!q.empty()) {
		pos cur = q.front(); q.pop();
		if (cur.r == N - 1 && cur.c == M - 1) {
			return dist[cur.h][cur.r][cur.c];
		}
		for (int i = 0; i < 4; i++) {
			int nr = cur.r + dr[i], nc = cur.c + dc[i];
			if (nr < 0 || nr >= N || nc < 0 || nc >= M) continue;
		
			if (map[nr][nc] && cur.h == 0 && !dist[1][nr][nc]) { //wall
				dist[1][nr][nc] = dist[cur.h][cur.r][cur.c] + 1;
				q.push({ 1, nr, nc });
			}
			if (!map[nr][nc] && !dist[cur.h][nr][nc]) { //not wall
				dist[cur.h][nr][nc] = dist[cur.h][cur.r][cur.c] + 1;
				q.push({ cur.h, nr, nc });
			}
		}
	}
	return -1;
}

int main() {
	freopen("input.txt", "r", stdin);
	input();
	cout << (bfs(0, 0)) << endl;
}