#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

int N, L, R;
int a[50][50];
int visit[50][50];
int ppp[2500]; //pp:# of poeple of group i
int ccc[2500]; //cc: # of ally of group i

int dr[] = { 0, 0, -1, 1 };
int dc[] = { -1, 1, 0, 0 };

void input() {
	cin >> N >> L >> R;
 	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			cin >> a[r][c];
		}
	}
}

bool allyBFS(int sr, int sc, int k) { //k: ally id
	int pp = a[sr][sc], cc = 1; //pp:# of poeple, cc: # of ally
	queue<pair<int, int>> q;
	q.push({ sr, sc });
	visit[sr][sc] = k;
	while (!q.empty()) {
		pair<int, int> cur = q.front(); q.pop();
		for (int i = 0; i < 4; i++) {
			int nr = cur.first + dr[i], nc = cur.second + dc[i];
			if (nr < 0 || nr >= N || nc < 0 || nc >= N || visit[nr][nc]) continue;
			int diff = abs(a[nr][nc] - a[cur.first][cur.second]);
			if (diff < L || diff > R) continue;
			q.push({ nr, nc });
			visit[nr][nc] = k;
			cc++, pp += a[nr][nc];
		}
	}
	ppp[k] = pp;
	ccc[k] = cc;
	if (k == N*N) return false; //no gate open
	return true;
}

void move() {
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			int k = visit[r][c];
			a[r][c] = ppp[k] / ccc[k];
		}
	}
}

bool ally() {
	int k = 1;
	bool result = true;
	memset(visit, 0, sizeof(visit));
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			if (!visit[r][c]) {
				result = allyBFS(r, c, k++);
			}
		}
	}
	move();
	return result;
}

int main() {
	freopen("input.txt", "r", stdin);
	input();
	int count = 0;
	while (ally()) {
		count++;
	}
	cout << count << endl;
}