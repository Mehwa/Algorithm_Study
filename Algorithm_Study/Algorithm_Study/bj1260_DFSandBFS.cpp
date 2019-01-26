#include "pch.h"
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int N, M, V;

void printAdjList(vector<vector<int> > &adjList) {
	for (int i = 0; i < adjList.size(); i++) {
		for (int j = 0; j < adjList[i].size(); j++) {
			cout << i << " " << adjList[i][j] << endl;
		}
	}
}

void dfs(vector<vector<int> > &adjList, vector<bool> &visited, int cur) {
	printf("%d ", cur);
	visited[cur] = true;
	for (int i = 0; i < adjList[cur].size(); i++) {
		int next = adjList[cur][i];
		if (!visited[next]) {
			dfs(adjList, visited, next);
		}
	}
}

void dfsAll(vector<vector<int> > &adjList, int initNode) {
	vector<bool> visited(adjList.size(), false);
	dfs(adjList, visited, initNode);
	for (int i = 1; i < adjList.size(); i++) {
		if (!visited[i])
			dfs(adjList, visited, i);
	}
}

void bfs(vector<vector<int> > &adjList, int initNode) {
	vector<bool> visited(adjList.size(), false);
	queue<int> q;
	q.push(initNode);
	visited[initNode] = true;
	printf("%d ", initNode);
	//for (int i = 1; i < adjList.size(); i++) {
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		for (int j = 0; j < adjList[cur].size(); j++) {
			int next = adjList[cur][j];
			if (!visited[next]) {
				printf("%d ", next);
				visited[next] = true;
				q.push(next);
			}
		}
	}
}

void bf1260_DFSandBFS()
{
	vector<vector<int> > adjList;

	cin >> N >> M >> V;
	//cout << "N:" << N << " M:" << M << " V:" << V << endl;

	adjList.resize(N + 1);

	for (int i = 0; i < M; i++) {
		int x = 0, y = 0;
		cin >> x >> y;
		adjList[x].push_back(y);
		adjList[y].push_back(x);
	}
	for (int i = 1; i < adjList.size(); i++) {
		sort(adjList[i].begin(), adjList[i].end());
	}

	dfsAll(adjList, V);
	printf("\n");
	bfs(adjList, V);
}