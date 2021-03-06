#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

int N, max_h = 0;
int map[101][101];
bool visited[101][101];
int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

void input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			max_h = max(map[i][j], max_h);
		}
	}
}

void dfs(int cx, int cy, int h) {
	visited[cx][cy] = true;
	for (int i = 0; i < 4; i++) {
		int nx = cx + dx[i];
		int ny = cy + dy[i];
		if (0 <= nx && nx < N && 0 <= ny && ny < N && !visited[nx][ny] && map[nx][ny] > h)
			dfs(nx, ny, h);
	}
}

void bfs(int sx, int sy, int h) {
	queue<pair<int, int> > q;
	q.push(make_pair(sx, sy));
	visited[sx][sy] = true;
	while (!q.empty()) {
		pair<int, int> cur = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int nx = cur.first + dx[i];
			int ny = cur.second + dy[i];
			if (0 <= nx && nx < N && 0 <= ny && ny < N && !visited[nx][ny] && map[nx][ny] > h) {
				q.push(make_pair(nx, ny));
				visited[nx][ny] = true;
			}
		}
	}
}

int searchSafeArea(int h) {
	int safeArea = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j] > h && !visited[i][j]) {
				bfs(i, j, h);
				//dfs(i, j, h);
				safeArea++;
			}
		}

	}
	return safeArea;
}

int searchMaxSafeArea() {
	int safeArea = 0;
	for (int h = 0; h <= max_h; h++) {
		memset(visited, false, sizeof(visited));
		safeArea = max(searchSafeArea(h), safeArea);
	}
	return safeArea;
}

int main()
{
	input();
	cout<<searchMaxSafeArea();
}