/*
 * Author: kpark
 * Date: 2019.03.21
 * Algorithm: BFS
 * Problem: https://www.acmicpc.net/problem/16948
*/

#include <iostream>
#include <queue>

using namespace std;

struct rc { int r, c; };

int N, r1, c1, r2, c2;
int dr[] = { -2, -2, 0, 0, 2, 2 };
int dc[] = { -1, 1, -2, 2, -1, 1 };

int map[200][200];
int dist[200][200];

int bfs() {
	queue<rc> q;
	dist[r1][c1] = 1;
	q.push({ r1, c1 });
	while (!q.empty()) {
		rc cur = q.front(); q.pop();
		for (int i = 0; i < 6; i++) {
			int nr = cur.r + dr[i];
			int nc = cur.c + dc[i];
			if (0 <= nr && nr < N && 0 <= nc && nc < N && !dist[nr][nc]) {
				if (nr == r2 && nc == c2) return dist[cur.r][cur.c];
				q.push({ nr, nc });
				dist[nr][nc] = dist[cur.r][cur.c] + 1;
			}
		}
	}
	return -1;
}

int main() {
	freopen("input.txt", "r", stdin);
	cin >> N >> r1 >> c1 >> r2 >> c2;
	cout << bfs() << endl;
}