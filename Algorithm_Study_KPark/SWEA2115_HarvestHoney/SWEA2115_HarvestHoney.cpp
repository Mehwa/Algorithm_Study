#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

int T, N, M, C;
int map[10][10];
vector<int> a_v, b_v;
int dfs_result;
bool visit[5];

void input() {
	memset(map, 0, sizeof(map));
	cin >> N >> M >> C;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> map[i][j];
}

bool valid(int ax, int ay, int bx, int by) {
	if (ax + M > N || bx + M > N || (ay == by && ax + M > bx))
		return false;
	return true;
}

int calDFS(vector<int> &v, int d, int sum, int sqaure) {
	if (d > M)
		return 0;
	for (int i = 0; i < v.size(); i++) {
		int n = v[i];
		if (!visit[i]) {
			if (sum + n <= C) {
				visit[i] = true;
				dfs_result = max(dfs_result, sqaure + n * n);
				calDFS(v, d + 1, sum + n, sqaure + n * n);
				visit[i] = false;
			}
		}	
	}
}

int cal(int ax, int ay, int bx, int by) {
	a_v.clear();
	b_v.clear();
	int result = 0;
	if (!valid(ax, ay, bx, by))
		return -1;
	for (int i = 0; i < M; i++) {
		a_v.push_back(map[ay][ax + i]);
		b_v.push_back(map[by][bx + i]);
	}
	dfs_result = 0;
	calDFS(a_v, 0, 0, 0);
	result += dfs_result;
	dfs_result = 0;
	calDFS(b_v, 0, 0, 0);
	result += dfs_result;
	return result;
}

int search() {
	int result = 0;
	for (int ay = 0; ay < N; ay++) {
		for (int ax = 0; ax < N; ax++) {
			for (int by = ay; by < N; by++) {
				for (int bx = 0; bx < N; bx++) {
					result = max(result, cal(ax, ay, bx, by));
				}
			}
		}
	}
	return result;
}

int main()
{
	freopen("input.txt", "r", stdin);
	cin >> T;
	for (int t = 1; t <= T; t++) {
		input();
		cout << "#" << t << " " << search() << endl;
	}
}