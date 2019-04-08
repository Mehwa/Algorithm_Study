#include <iostream>
#include <queue>
#include <vector>
#include <cstring>

using namespace std;

int T, M, N, K;
int map[350][350];
int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };
struct CELL {
	int r, c, l, t;
	bool active;
};

struct comp { //sort by life
	bool operator()(CELL &a, CELL &b) {
		return a.l < b.l;
	}
};

priority_queue<CELL, vector<CELL>, comp> pq;
priority_queue<CELL, vector<CELL>, comp> npq;

void input() {
	memset(map, 0, sizeof(map));
	priority_queue<CELL, vector<CELL>, comp> empty_pq;
	swap(pq, empty_pq); //clear pq
	cin >> N >> M >> K;
	for (int r = 149; r < N + 149; r++) {
		for (int c = 149; c < M + 149; c++) {
			cin >> map[r][c];
			if(map[r][c]) pq.push({ r, c, map[r][c], 0, false });
		}
	}
}

void printInput() {
	for (int r = 149; r < N + 149; r++) {
		for (int c = 149; c < M + 149; c++) {
			cout << map[r][c];
		}
		cout << endl;
	}
}

int sim() {
	for(int k = 1; k <= K; k++){
		priority_queue<CELL, vector<CELL>, comp> empty_pq;
		swap(npq, empty_pq); //clear npq
		while (!pq.empty()) {
			CELL cur = pq.top(); pq.pop();
			cur.t++;
			if (!cur.active) { //inactive state
				if (cur.t == cur.l) {
					cur.active = true;
					cur.t = 0;
				}
			}
			else { //active state
				if (cur.t == 1) { //spread
					for (int i = 0; i < 4; i++) {
						int nr = cur.r + dr[i], nc = cur.c + dc[i];
						if (map[nr][nc]) continue; //not empty cell
						npq.push({ nr, nc, cur.l, 0, false });
						map[nr][nc] = cur.l;
					} 
				}
				if (cur.t == cur.l) { //dead
					continue;
				}
			}
			npq.push(cur);
		}
		pq = npq;
	}
	return npq.size();
}

int main() {
	freopen("input5653.txt", "r", stdin);
	cin >> T;
	for (int t = 1; t <= T; t++) {
		input();
		cout << "#" << t << " " << sim() << endl;
	}
}