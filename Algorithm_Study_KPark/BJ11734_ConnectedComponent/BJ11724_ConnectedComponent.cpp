#include <iostream>
#include <queue>

using namespace std;

int N, M;
bool visited[1001] = { false };
bool adjList[1001][1001];

void input() {
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		int x = 0, y = 0;
		cin >> x >> y;
		adjList[x][y] = true;
		adjList[y][x] = true;
	}
}

void printInput() {
	cout << "N:" << N << "M:" << M << endl;
	for (int i = 0; i <= N; i++) {
		for (int j = 0; j <= N; j++)
			cout << adjList[i][j] << " ";
		cout << endl;
	}
}

bool bfs(int start) {
	if (visited[start]) //already visited node
		return false;
	queue<int> q;
	q.push(start);
	visited[start] = true;
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		for (int i = 1; i <= N; i++) {
			if (adjList[cur][i] && !visited[i]) {
				q.push(i);
				visited[i] = true;
			}
		}
	}
	return true;
}

int countConnectedComponent() {
	int count = 0;
	for (int i = 1; i <= N; i++) {
		if (bfs(i))
			count++;
	}
	return count;
}

int main()
{
	input();
	//printInput();
	cout << countConnectedComponent() << endl;
}
