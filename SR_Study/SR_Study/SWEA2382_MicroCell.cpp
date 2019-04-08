/*
	2019.04.05
	https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV597vbqAH0DFAVl&categoryId=AV597vbqAH0DFAVl&categoryType=CODE
	저번 구현과 다르게 셀 안에 n 개수 저장하고 맵에 해당 셀에 머무르고 있는 군집의 n 저장
	나보다 먼저 움직인 셀이 머무르고 있는 칸의 정보를 초기화해주는 것을 방지하기 위해 이동할 때 초기화하지 않고 맵 한번에 0으로 초기화
	(경계에서 큰 애가 경계로 들어왔는데 해당 위치에 있던 애가 밖으로 나가면서 0 만드는 오류 있음)
*/
#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

struct CELL {
	int r, c, n, d;
};
struct comp {
	bool operator()(CELL &a, CELL &b) {
		return a.n < b.n;
	}
};

int T, N, M, K;
int map[100][100];
priority_queue<CELL, vector<CELL>, comp> pq;
int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };
int nd[] = { 1, 0, 3, 2 };

void input() {
	memset(map, 0, sizeof(map));
	cin >> N >> M >> K;
	for (int k = 0; k < K; k++) {
		CELL tmp;
		cin >> tmp.r >> tmp.c >> tmp.n >> tmp.d;
		map[tmp.r][tmp.c] = tmp.n;
		tmp.d--;
		pq.push(tmp);
	}
}

void sim() {
	while (M--) {
		memset(map, 0, sizeof(map));
		priority_queue<CELL, vector<CELL>, comp> npq;
		while (!pq.empty()){
			CELL cur = pq.top(); pq.pop();
			int nr = cur.r + dr[cur.d], nc = cur.c + dc[cur.d];
			if (nr == 0 || nr == N - 1 || nc == 0 || nc == N - 1) { //경계 만나면
				cur.n /= 2;
				cur.d = nd[cur.d];
				if (cur.n == 0) continue;
			}
			else if (cur.n < map[nr][nc]) { //다음칸에 나보다 큰 군집이 이미 있으면
				//map[cur.r][cur.c] = 0;
				map[nr][nc] += cur.n;
				continue;
			}
			//이동
			//map[cur.r][cur.c] = 0;
			map[nr][nc] = cur.n;
			cur.r = nr, cur.c = nc;
			npq.push(cur);
		}
		while (!npq.empty()) {
			CELL cur = npq.top(); npq.pop();
			if (map[cur.r][cur.c] != cur.n) { //이동 후 현재 칸에 미생물 수가 증가했다는 건 다른 군집이 합쳐졌다는 것
				cur.n = map[cur.r][cur.c];
			}
			pq.push(cur);
		}
	}
}
int output() {
	int sum = 0;
	while (!pq.empty()) {
		sum += pq.top().n; pq.pop();
	}
	return sum;
}

int main() {
	freopen("input2382.txt", "r", stdin);
	cin >> T;
	for (int t = 1; t <= T; t++) {
		input();
		sim();
		cout << "#" << t << " " << output() << endl;
	}
}