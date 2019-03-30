#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

int N;
int map[20][20];
int dist[20][20];
struct shark {
	int r, c, s, a;
};
shark s;

int dr[] = { -1, 0, 0, 1 };
int dc[] = { 0, -1, 1, 0 };

void input() {
	cin >> N;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			cin >> map[r][c];
			if (map[r][c] == 9) s.r = r, s.c = c, s.s = 2, s.a = 0, map[r][c] = 0;
		}
	}
}

int bfs(int sr, int sc) {
	int result = 0;
	pair<int, int> min_pos = { 21, 21 };
	memset(dist, 0, sizeof(dist));
	queue<pair<int, int>> q;
	dist[sr][sc] = 1;
	q.push({ sr, sc });
	while (q.size() && result == 0) {
		for (int size = q.size(); size--;) { //for each distance
			pair<int, int> cur = q.front(); q.pop();
			int nr = cur.first, nc = cur.second;
			if (map[nr][nc] && map[nr][nc] < s.s) { // smaller fish
				min_pos = min(min_pos, { nr, nc });
				s.r = min_pos.first, s.c = min_pos.second;
				result = dist[min_pos.first][min_pos.second] - 1;
				
			}
			for (int i = 0; i < 4; i++) {
				int nr = cur.first + dr[i], nc = cur.second + dc[i];
				if (nr < 0 || nr >= N || nc < 0 || nc >= N || dist[nr][nc] || map[nr][nc] > s.s) continue;
				dist[nr][nc] = dist[cur.first][cur.second] + 1;
				q.push({ nr, nc });
			}
		}
		if (result > 0) { //eat
			map[min_pos.first][min_pos.second] = 0;
			s.a++;
			if (s.a == s.s) s.s++, s.a = 0; //fish grows
			return result;
		}
	}
	return result;
}

int main() {
	freopen("input.txt", "r", stdin);
	input();
	int count = 0, rt = 1;
	while (rt) {
		rt = bfs(s.r, s.c);
		count += rt;
	}
	cout << count << endl;
}