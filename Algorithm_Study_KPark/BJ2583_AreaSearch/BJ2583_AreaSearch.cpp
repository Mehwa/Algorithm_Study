#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

//input
int N, M, K;
bool map[102][102] = { false };
bool visited[102][102] = { false };

int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

//output
vector<int> areaList;

void input() {
	cin >> M >> N >> K;
	for (int i = 0; i < K; i++) {
		int bl_x = 0, bl_y = 0, tr_x = 0, tr_y = 0;
		cin >> bl_x >> bl_y >> tr_x >> tr_y;
		for (int x = bl_x + 1; x <= tr_x; x++)
			for (int y = bl_y + 1; y <= tr_y; y++)
				map[x][y] = true;
	}
}

void printInput() {
	for (int i = 0; i <= N + 1; i++) {
		for (int j = 0; j <= M + 1; j++) {
			cout << map[i][j];
		}
		cout << endl;
	}
}

void transform() {
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			map[i][j] = !map[i][j];
}

int bfs(int start_x, int start_y) {
	int area = 0;
	queue<pair<int, int> > q;
	q.push(make_pair(start_x, start_y));
	visited[start_x][start_y] = true;
	while (!q.empty()) {
		pair<int, int> cur = q.front();
		q.pop();
		area++;
		for (int i = 0; i < 4; i++) {
			int next_x = cur.first + dx[i];
			int next_y = cur.second + dy[i];
			if (map[next_x][next_y] && !visited[next_x][next_y]) {
				q.push(make_pair(next_x, next_y));
				visited[next_x][next_y] = true;
			}
		}
	}
	return area;
}

void searchArea() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (!visited[i][j] && map[i][j]) {
				int area = bfs(i, j);
				areaList.push_back(area);
			}
		}
	}
	sort(areaList.begin(), areaList.end());
}

void output() {
	cout << areaList.size() << endl;
	for (int i = 0; i < areaList.size(); i++)
		cout << areaList[i] << " ";
}

int main()
{
	input();
	transform();
	//printInput();
	searchArea();
	output();
}
