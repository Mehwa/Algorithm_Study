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
			int nnd = cur.d;
			if (nn[cur.id] == 0) continue;
			if (nr == 0 || nr == N - 1 || nc == 0 || nc == N - 1) { //border
				nn[cur.id] /= 2;
				nnd = nd[cur.d];
			}
			else if (map[nr][nc]) { // already occupied && next cell bigger
				nn[map[nr][nc]] += nn[cur.id]; //주의!: pq에서 중간에 값 바꾼다고 순서 바꿔주지 않는다.
				nn[cur.id] = 0;
				continue;
			}
			map[nr][nc] = cur.id;
			npq.push({ cur.id, nr, nc, nnd });
		}
		while (!npq.empty()) { //pq sort를 해주기 위해 일일이 하나씩 빼서 넣어준다
			pq.push(npq.top());
			npq.pop();
		}
	}
}

int count() {
	int result = 0;
	for (int i = 1; i <= K; i++)
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
