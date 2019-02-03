#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int k, V, E;
vector<vector<int> > adjList;
vector<bool> group;
vector<bool> visited;

bool IsBiGraphBFS(int startNode) {
	queue<int> q;
	q.push(startNode);
	visited[startNode] = true;
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		for (int i = 0; i < adjList[cur].size(); i++) {
			int next = adjList[cur][i];
			if (visited[next] && group[cur] == group[next])
				return false;
			if (!visited[next]) {
				q.push(next);
				visited[next] = true;
				group[next] = !group[cur];
			}
		}
	}
	return true;
}

bool IsBiGraph() {
	for (int i = 1; i < adjList.size(); i++) {
		if (!IsBiGraphBFS(i))
			return false;
	}
	return true;
}

void printInput() {
	cout << endl << V << " " << E << endl;
	for (int i = 1; i < adjList.size(); i++) {
		for (int j = 0; j < adjList[i].size(); j++) {
			cout << adjList[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

int main()
{
	cin >> k;
	for (int i = 0; i < k; i++) {
		cin >> V >> E;
		adjList.clear();
		group.clear();	
		visited.clear();
		adjList.resize(V + 1);
		group.resize(V + 1, false);
		visited.resize(V + 1, false);
		for (int j = 0; j < E; j++) {
			int v1 = 0, v2 = 0;
			cin >> v1 >> v2;
			adjList[v1].push_back(v2);
			adjList[v2].push_back(v1);
		}
		//printInput();
		if (IsBiGraph())
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
}