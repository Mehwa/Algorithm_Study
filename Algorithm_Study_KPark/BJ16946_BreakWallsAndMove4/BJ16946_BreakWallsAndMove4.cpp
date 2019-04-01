/*
 * Author: kpark
 * Date: 2019.03.31
 * Algorithm: BFS
 * Problem: https://www.acmicpc.net/problem/16946
*/

#include <iostream>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

int N, M;
int map[1000][1000];
int result[2][1000][1000]; //group, # of cells
bool visit[1000][1000];

int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };

void input() {
	scanf("%d %d\n", &N, &M);
	for (int r = 0; r < N; r++) {
		string line;
		getline(cin, line);
		for (int c = 0; c < M; c++) {
			map[r][c] = line[c] - '0';
		}
	}
}

void bfs(int sr, int sc, int g) {
	queue<pair<int, int>> q;
	queue<pair<int, int>> nq;
	q.push({ sr, sc });
	nq.push({ sr, sc });
	visit[sr][sc] = true;
	while (!q.empty()) {
		pair<int, int> cur = q.front(); q.pop();
		for (int i = 0; i < 4; i++) {
			int nr = cur.first + dr[i], nc = cur.second + dc[i];
			if (nr < 0 || nr >= N || nc < 0 || nc >= M || map[nr][nc] || visit[nr][nc]) continue;
			q.push({ nr, nc });
			nq.push({ nr, nc });
			visit[nr][nc] = true;
		}
	}
	int size = nq.size();
	while (!nq.empty()) {
		for (int i = 0; i < size; i++) {
			pair<int, int> cur = nq.front(); nq.pop();
			result[0][cur.first][cur.second] = g;
			result[1][cur.first][cur.second] = size;
		}
	}
}

void solve() {
	int g = 1;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < M; c++) {
			if (!map[r][c] && !visit[r][c]) bfs(r, c, g++);
		}
	}
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < M; c++) {
			if (map[r][c]) {
				vector<int> groups;
				for (int i = 0; i < 4; i++) {
					int nr = r + dr[i], nc = c + dc[i];
					if (nr < 0 || nr >= N || nc < 0 || nc >= M || map[nr][nc] == 1) continue;
					auto it = find(groups.begin(), groups.end(), result[0][nr][nc]);
					if (it != groups.end()) continue;
					map[r][c] += result[1][nr][nc];
					groups.push_back(result[0][nr][nc]);
				}
			}
		}
	}
}

void output() {
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < M; c++) {
			cout << map[r][c] % 10;
		}
		cout << endl;
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	input();
	solve();
	output();
}