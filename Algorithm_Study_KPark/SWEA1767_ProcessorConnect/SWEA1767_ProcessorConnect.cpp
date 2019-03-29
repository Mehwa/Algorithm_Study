#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

struct p {
	int r, c, dir;
};

int T, N;
bool map[12][12];
int dist[12][12];
vector<p> pp;
int cp, max_cp; //# of Connected p
int sd, min_sd; //sum of dist

int dr[] = { -1, 0, 1, 0 }; //N, E, S, W
int dc[] = { 0, 1, 0, -1 };

void input() {
	max_cp = 0, cp = 0, sd = 0, min_sd = 987654321;
	memset(map, 0, sizeof(map));
	pp.clear();
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			if (map[i][j] && (i == 0 || j == 0 || i == N - 1 || j == N - 1)) {
				cp++;
				continue;
			}
			if (map[i][j]) pp.push_back({ i, j, 0 });
		}
	}
}

int calDist(p s) {
	queue<pair<int, int>> q;
	q.push({ s.r, s.c });
	dist[s.r][s.c] = 0;
	while (!q.empty()) {
		pair<int, int> cur = q.front(); q.pop();
		int nr = cur.first + dr[s.dir], nc = cur.second + dc[s.dir];
		if (nr < 0 || nr >= N || nc < 0 || nc >= N) return dist[cur.first][cur.second];
		if (map[nr][nc] || dist[nr][nc]) return 0; //can not connect
		dist[nr][nc] = dist[cur.first][cur.second] + 1;
		q.push({ nr, nc });
	}
}

void dfs(int d) {
	if (d == pp.size()) {
		if (cp > max_cp) {
			max_cp = cp;
			min_sd = sd;
		}
		else if (cp == max_cp) min_sd = min(min_sd, sd);
		return;
	}
	int ret = -1;
	for (int i = 0; i < 4; i++) {
		int tmp[12][12];
		memcpy(tmp, dist, sizeof(dist));
		pp[d].dir = i;
		ret = calDist(pp[d]);
		if (ret == 0) { //exclude can not connect case
			memcpy(dist, tmp, sizeof(dist));
			continue; 
		}
		cp++, sd += ret;
		dfs(d + 1);
		cp--, sd -= ret;
		memcpy(dist, tmp, sizeof(dist));
	}
	if (ret == 0) dfs(d + 1); //if p can not be connected to all dir
}

int main() {
	freopen("input.txt", "r", stdin);
	cin >> T;
	for (int t = 1; t <= T; t++) {
		input();
		dfs(0);
		cout << "#" << t << " " << min_sd << endl;
	}
}