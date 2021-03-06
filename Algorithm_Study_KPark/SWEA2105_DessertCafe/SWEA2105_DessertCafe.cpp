#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

int T, N;
int result;
int dx[4] = { 1, 1, -1, -1 }; //↘ ↙ ↖ ↗ 
int dy[4] = { 1, -1, -1, 1 };//↘ ↙ ↖ ↗
vector<int> path;
int map[20][20];
bool visited[20][20];

void input() {
	result = -1;
	memset(visited, false, sizeof(visited));
	memset(map, 0, sizeof(map));
	path.clear();
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}
}

bool IsPassed(int d) {
	for (int i = 0; i < path.size(); i++) {
		if (d == path[i])
			return true;
	}
	return false;
}

void dfs(int sx, int sy, int cx, int cy, int dir, int nTurn) {
	visited[cx][cy] = true;
	path.push_back(map[cx][cy]);

	for (int i = 0; i < 4; i++) {
		if (sx == cx && sy == cy && i != 0) continue; //first step: go to South East only (↘)
		if (nTurn == 3 && i != 3) continue; //After two turn: go to North East only (↖)

		int nx = cx + dx[i];
		int ny = cy + dy[i];
		if (nx == sx && ny == sy && path.size() > 3) { //cycle
			result = max(result, (int)path.size());
		}
		if (0 <= nx && nx < N && 0 <= ny && ny < N && !visited[nx][ny] && !IsPassed(map[nx][ny]) && nTurn < 4) {
			if (dir != i) //turn
				dfs(sx, sy, nx, ny, i, nTurn + 1);
			else
				dfs(sx, sy, nx, ny, i, nTurn);
			path.pop_back();
			visited[nx][ny] = false;
		}
	}
}

void dfsAll() {
	for (int i = 0; i < N; i++) {
		for (int j = 1; j < N-1; j++) {
			path.clear();
			memset(visited, false, sizeof(visited));
			dfs(i, j, i, j, 0, 0);
		}
	}
}

int main()
{
	freopen("input.txt", "r", stdin);
	cin >> T;
	for (int t = 1; t <= T; t++) {
		input();
		dfsAll();
		cout << "#" << t << " " << result << endl;
	}
}
