#include <iostream>
#include <queue>

using namespace std;

int N;
bool adjList[101][101] = { false };
bool path[101][101] = { false };
bool visited[101] = { false };

void input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> adjList[i][j];
		}
	}
}

void printInput() {
	cout << "N:" << N << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << adjList[i][j] << " ";
		}
		cout << endl;
	}
}

void output() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << path[i][j] << " ";
		}
		cout << endl;
	}
}

void pathFindingBFS(int start) {
	queue<int> q;
	q.push(start);
	//visited[start] = true;  ==>mind the start node, only the case there is circle path[start][start] = 1
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		path[start][cur] = true;
		for (int i = 0; i < N; i++) {
			if (adjList[cur][i] && !visited[i]) {
				q.push(i);
				visited[i] = true;
			}
		}
	}
	if (!visited[start]) // ==>mind the start node, only the case there is circle path[start][start] = 1
		path[start][start] = false;
}

void pathFinding() {
	for (int i = 0; i < N; i++) {
		pathFindingBFS(i);
		for(int j = 0; j < N; j++)
			visited[j] = false;
	}
}

int main()
{
	input();
	//printInput();
	pathFinding();
	output();
}