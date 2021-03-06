#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

int T, N, K;
int h[8][8];
bool visited[8][8];
int dist[8][8];
int highest = 0;
vector<pair<int, int> > peak;
int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

void input() {
	highest = 0;
	peak.clear();
	cin >> N >> K;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> h[i][j];
			highest = max(highest, h[i][j]);
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (h[i][j] == highest)
				peak.push_back(make_pair(i, j));
		}
	}
}

int dfs(int cx, int cy, bool curved) {
	visited[cx][cy] = true;
	int d = 0;
	for (int i = 0; i < 4; i++) {
		int nx = cx + dx[i];
		int ny = cy + dy[i];
		if (!visited[nx][ny] && 0 <= nx && nx < N && 0 <= ny && ny < N) {
			if (h[nx][ny] < h[cx][cy]) {
				dist[nx][ny] = dist[cx][cy] + 1;
				d = max(d, dfs(nx, ny, curved));
			}
			else {
				if (!curved && h[nx][ny] < h[cx][cy] + K) {
					int c = abs(h[nx][ny] - h[cx][cy]) + 1;
					h[nx][ny] -= c;
					dist[nx][ny] = dist[cx][cy] + 1;
					d = max(d, dfs(nx, ny, !curved));
					h[nx][ny] += c;
				}
			}
		}
	}
	visited[cx][cy] = false;
	return max(d ,dist[cx][cy]);
}

int searchLongestTracking() {
	int result = 0;
	for (int i = 0; i < peak.size(); i++) {
		memset(dist, 0, sizeof(dist));
		int d = dfs(peak[i].first, peak[i].second, false);
		result = max(result, d + 1);
	}
	return result;
}

int main()
{
	freopen("input.txt", "r", stdin);
	cin >> T; 
	for (int t = 1; t <= T; t++) {
		input();
		cout << "#" << t << " " << searchLongestTracking() << endl;
	}
}