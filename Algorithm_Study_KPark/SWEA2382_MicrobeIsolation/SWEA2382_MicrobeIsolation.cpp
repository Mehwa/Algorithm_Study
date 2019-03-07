#include <iostream>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

int T, N, M, K;
int map[100][100];
int nn[1000];
int dr[4] = { -1, 1, 0, 0 };
int dc[4] = { 0, 0, -1, 1 };
int nd[4] = { 1, 0, 3, 2 };

typedef struct CELL {
	int id, r, c, d;
};

struct compare{
	bool operator()(const CELL &a, const CELL &b) {
		return nn[a.id] < nn[b.id];
	}
};

priority_queue <CELL, vector<CELL>, compare> pq;
priority_queue <CELL, vector<CELL>, compare> npq;

void input() {
	priority_queue <CELL, vector<CELL>, compare> emptypq;
	swap(pq, emptypq);
	memset(map, 0, sizeof(map));
	memset(nn, 0, sizeof(nn));
	cin >> N >> M >> K;
	for (int i = 1; i <= K; i++) {
		int r, c, n, d;
		cin >> r >> c >> n >> d;
		nn[i] = n;
		pq.push({i, r, c, d - 1 });
	}
}

void sim() {
	for (int i = 1; i <= M; i++) {
		priority_queue <CELL, vector<CELL>, compare> emptypq;
		swap(npq, emptypq);
		memset(map, 0, sizeof(map));
		while (!pq.empty()) {
			CELL cur = pq.top();
			pq.pop();
			int nr = cur.r + dr[cur.d];
			int nc = cur.c + dc[cur.d];
			if (nr == 0 || nr == N - 1 || nc == 0 || nc == N - 1) { //border
				nn[cur.id] /= 2;
				if (nn[cur.id] > 0) {
					map[nr][nc] = cur.id;
					npq.push({ cur.id, nr, nc, nd[cur.d] });
				}
			}
			else if (map[nr][nc] && nn[map[nr][nc]] > nn[cur.id]) { // already occupied && next cell bigger
				nn[map[nr][nc]] += nn[cur.id];
				nn[cur.id] = 0;
			}
			else { // move
				map[nr][nc] = cur.id;
				npq.push({cur.id, nr, nc, cur.d });
			}
		}
		pq = npq;
	}
}

int count() {
	int result = 0;
	for (int i = 0; i <= K; i++)
		result += nn[i];
	return result;
}


int main()
{
	freopen("input.txt", "r", stdin);
	cin >> T;
	for (int t = 1; t <= T; t++) {
		input();
		sim();
		cout << "#" << t << " " << count() << endl;
	}
}
