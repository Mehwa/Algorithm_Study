/*
 * Author: kpark
 * Data: 2019.03.20
 * Algorithm: DFS
 * Problem: https://www.acmicpc.net/problem/17070
*/

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int N;
int dr[] = { 0, 1, 1 }; // ¡æ, ¡é, ¢Ù
int dc[] = { 1, 0, 1 };
vector<int> nd[3] = { {0, 2}, {1, 2}, {0, 1, 2} };
int visit[18][18];
int map[18][18];
int result;

void input() {
	result = 0;
	memset(map, 1, sizeof(map));
	cin >> N;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			cin >> map[i][j];
}

bool IsWay(int r, int c, int d) {
	if (map[r][c]) return false;
	if ((d == 2) && (map[r][c - 1] || map[r - 1][c])) return false;
	return true;
}

void dfs(int cr, int cc, int cd) {
	visit[cr][cc] = true;
	for(int i = 0; i < nd[cd].size(); i++){
		int nr = cr + dr[nd[cd][i]];
		int nc = cc + dc[nd[cd][i]];
		if (!visit[nr][nc] && IsWay(nr, nc, nd[cd][i])) {
			if (nr == N && nc == N) {result++; return;}
			dfs(nr, nc, nd[cd][i]);
			visit[nr][nc] = false;
		}
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	input();
	dfs(1, 2, 0);
	cout << result << endl;
}