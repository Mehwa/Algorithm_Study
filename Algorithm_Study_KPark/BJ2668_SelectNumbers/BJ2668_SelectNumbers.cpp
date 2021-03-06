#include <iostream>	
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

int N;
int list[101];
int visited[101];
vector<int> result;

void input() {
	cin >> N;
	for (int i = 1; i <= N; i++)
		cin >> list[i];
}

void initVisit() {
	memset(visited, 0, sizeof(visited));
	for (int i = 0; i < result.size(); i++)
		visited[result[i]] = 2;
}

bool dfs(int start, int cur) {
	visited[cur] = 1;
	int next = list[cur];
	if (next == start) { //cycle
		for (int i = 1; i <= N; i++) {
			if (visited[i]==1)
				result.push_back(i);
		}
		return 0;
	}
	if (!visited[next])
		dfs(start, next);
	return 0;
}

void searchDFS() {
	for (int i = 1; i <= N; i++) {
		initVisit();
		dfs(i, i);
	}
}

int main()
{
	input();
	searchDFS();
	sort(result.begin(), result.end());
	//result.erase(unique(result.begin(), result.end()), result.end());
	cout << result.size() << endl;
	for (int i = 0; i < result.size(); i++)
		cout << result[i] << endl;
}