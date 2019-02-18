#include <iostream>
#include <vector>
#include <deque>

using namespace std;

int T, N, E;
vector<vector<int> > adjList;
vector<int> v;
vector<bool> visited;
deque<int> trace, result;
int max_b = 0;
typedef struct Edge {
	int a, b, c;
};
vector<Edge> e;

void init() {
	max_b = 0;
	e.clear();
	v.clear();
	visited.clear();
	adjList.clear();
	trace.clear();
}

void input() {
	init();
	cin >> N >> E;
	adjList.resize(N + 1);
	v.resize(N + 1);
	visited.resize(N + 1, false);
	for (int i = 1; i <= N; i++) {
		cin >> v[i];
	}
	for (int i = 0; i < E; i++) {
		Edge ein;
		cin >> ein.a >> ein.b >> ein.c;
		e.push_back(ein);
		adjList[ein.a].push_back(ein.b);
	}
}

int cost(int a, int b) {
	for (int i = 0; i < e.size(); i++) {
		if (e[i].a == a && e[i].b == b) {
			return e[i].c;
		}
	}
}

int exploreCaveDFS(int cur, int benefit) {
	trace.push_back(cur);
	visited[cur] = true;
	for (int i = 0; i < adjList[cur].size(); i++) {
		int next = adjList[cur][i];
		if (!visited[next]) {
			exploreCaveDFS(next, benefit + v[next] - cost(cur, next));
			trace.pop_back();
		}
	}
	if (benefit >= max_b) {
		max_b = benefit;
		result = trace;
	}
	visited[cur] = false;
	return 0;
}

int main()
{
	//freopen("sample.in", "r", stdin);
	//freopen("smallMisc.in", "r", stdin);
	freopen("randomLargeSparse.in", "r", stdin);
	cin >> T;
	for (int t = 1; t <= T; t++) {
		input();
		exploreCaveDFS(1, v[1]);
		cout << max_b << " " << result.size() << endl;
		while(!result.empty()){
			cout << result.front() << " ";
			result.pop_front();
		}
		cout << endl;
	}
}