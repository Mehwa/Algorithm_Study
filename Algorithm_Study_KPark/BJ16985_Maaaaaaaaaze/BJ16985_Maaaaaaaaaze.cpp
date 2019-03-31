/*
 * Author: kpark
 * Date: 2019.03.21
 * Algorithm: DFS
 * Problem: https://www.acmicpc.net/problem/16985
*/

#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

int result;
int map[5][5][5];
int new_map[5][5][5];
int dist[5][5][5];
int visit[5];
int dx[] = { -1, 1, 0, 0, 0, 0 };
int dy[] = { 0, 0, -1, 1, 0, 0 };
int dz[] = { 0, 0, 0, 0, -1, 1 };
int in[1][3] = { {0, 0, 0}};
int out[1][3] = { {4, 4, 4}};

struct xyz {
	int z, y, x;
};

void input() {
	result = 987654321;
	for (int z = 0; z < 5; z++)
		for (int y = 0; y < 5; y++)
			for (int x = 0; x < 5; x++)	
				cin >> map[z][y][x];
}

int calDistBFS(int start[], int end[]) {
	memset(dist, 0, sizeof(dist));
	queue<xyz> q;
	dist[start[0]][start[1]][start[2]] = 1;
	q.push({ start[0], start[1], start[2] });
	while (!q.empty()) {
		xyz cur = q.front();
		q.pop();
		for (int i = 0; i < 6; i++) {
			int nx = cur.x + dx[i];
			int ny = cur.y + dy[i];
			int nz = cur.z + dz[i];
			if (nx < 0 || ny < 0 || nz < 0 || nx >= 5 || ny >= 5 || nz >= 5) continue;
			if (nz == end[0] && ny == end[1] && nx == end[2]) {
					return dist[cur.z][cur.y][cur.x];
			}
			if (new_map[nz][ny][nx] && !dist[nz][ny][nx]) {
				q.push({ nz, ny, nx });
				dist[nz][ny][nx] = dist[cur.z][cur.y][cur.x] + 1;
			}
		}
	}
	return 987654321;
}

void rotate(int z, int nr) {
	if (nr == 0) return;
	int ny[] = { 4, 3, 2, 1, 0 };
	for (int n = 0; n < nr; n++) {
		int tmp[5][5];
		for (int y = 0; y < 5; y++)
			for (int x = 0; x < 5; x++)
				tmp[x][ny[y]] = new_map[z][y][x];
		memcpy(new_map[z], tmp, sizeof(new_map[z]));
	}
}

void rotateDFS(int cur, int d) {
	if (d == 5) {
		if (new_map[in[0][0]][in[0][0]][in[0][2]] && new_map[out[0][0]][out[0][1]][out[0][2]])
			result = min(calDistBFS(in[0], out[0]), result);
		return;
	}
	for (int i = 0; i < 4; i++) {
			int tmp[5][5];
			memcpy(tmp, new_map[d], sizeof(new_map[d]));
			rotate(d, i);
			rotateDFS(i, d + 1);
			memcpy(new_map[d], tmp, sizeof(new_map[d]));
	}
}

void stackupDFS(int cur, int d) {
	if (d == 5) {
		rotateDFS(0, 0);
		return;
	}
	for (int i = 0; i < 5; i++) {
		if (!visit[i]) {
			memcpy(new_map[d], map[i], sizeof(map[i]));
			visit[i] = true;
			stackupDFS(i, d + 1);
			visit[i] = false;
		}
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	input();
	stackupDFS(0, 0);
	if (result == 987654321) cout << -1 << endl;
	else cout << result << endl;
}