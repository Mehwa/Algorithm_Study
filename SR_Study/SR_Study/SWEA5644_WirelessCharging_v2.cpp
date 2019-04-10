/*
	2019.04.10

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;

struct BC {
	int r, c, dist, p;
};
int T, M, C;
int A[101], B[101], ta[101], tb[101];
int ar, ac, br, bc;
BC bcs[8];
vector<int> map[11][11];
int dr[] = { 0, -1, 0, 1, 0 }; //정지, 상, 우, 하, 좌
int dc[] = { 0, 0, 1, 0, -1 };
bool comp(int aid, int bid) { return bcs[aid].p > bcs[bid].p; }

void input() {
	ar = 1, ac = 1, br = 10, bc = 10;
	memset(ta, 0, sizeof(ta));
	memset(tb, 0, sizeof(tb));
	memset(map, 0, sizeof(map));
	cin >> M >> C;
	for (int i = 1; i <= M; i++)
		cin >> A[i];
	for (int i = 1; i <= M; i++)
		cin >> B[i];
	for (int i = 0; i < C; i++)
		cin >> bcs[i].c >> bcs[i].r >> bcs[i].dist >> bcs[i].p; //* r, c 반대
}

void insertBC(int bid, int r, int c) {
	map[r][c].push_back(bid);
	if (map[r][c].size() > 1)
		sort(map[r][c].begin(), map[r][c].end(), comp);
}

void bfs(int bid, BC bc) {
	bool visit[11][11];
	memset(visit, false, sizeof(visit));
	int dist = bc.dist, p = bc.p;
	queue<pair<int, int>> q;
	q.push({ bc.r, bc.c });
	visit[bc.r][bc.c] = true;
	insertBC(bid, bc.r, bc.c);
	while (q.size() && dist--) {
		for (int size = q.size(); size--;) {
			pair<int, int> cur = q.front(); q.pop();
			for (int i = 1; i < 5; i++) {
				int nr = cur.first + dr[i], nc = cur.second + dc[i];
				if (nr < 1 || nr > 10 || nc < 1 || nc > 10 || visit[nr][nc]) continue;
				visit[nr][nc] = true;
				q.push({ nr, nc });
				insertBC(bid, nr, nc); //* bid를 넣어야하는데 p를 넣었음
			}
		}
	}
}

void createMap() {
	for (int i = 0; i < C; i++) {
		bfs(i, bcs[i]);
	}
}

void move(int time) {
	ar += dr[A[time]], ac += dc[A[time]];
	br += dr[B[time]], bc += dc[B[time]];
	//cout << "A:" << ar << "," << ac;
	//cout << "B:" << br << "," << bc<<endl;
}

void charge(int time) {
	if (map[ar][ac].size() == 0 && map[br][bc].size() == 0) return;
	if (map[ar][ac].size() == 0) { ta[time] = 0;  tb[time] = bcs[map[br][bc][0]].p; return; }
	if (map[br][bc].size() == 0) { ta[time] = bcs[map[ar][ac][0]].p; tb[time] = 0; return; }
	int abc = map[ar][ac][0], bbc = map[br][bc][0];
	if (abc == bbc) { //둘이 접속하려는 BC가 같을 때
		if (map[ar][ac].size() == 1 && map[br][bc].size() == 1) { //둘다 하나뿐
			ta[time] = bcs[abc].p / 2;
			tb[time] = bcs[bbc].p / 2;
		}
		else {
			if (map[ar][ac].size() == 1 && map[br][bc].size() > 1) { //A는 1개 B는 2개 이상
				int bbc2 = map[br][bc][1];
				ta[time] = bcs[abc].p;
				tb[time] = bcs[bbc2].p;
			}
			else if (map[ar][ac].size() > 1 && map[br][bc].size() == 1) { // A는 2개 이상 B는 1개
				int abc2 = map[ar][ac][1];
				ta[time] = bcs[abc2].p;
				tb[time] = bcs[bbc].p;
			}
			else { //둘 다 2개 이상
				int abc2 = map[ar][ac][1], bbc2 = map[br][bc][1];
				if (bcs[abc2].p > bcs[bbc2].p) { //A의 2번이 B의 2번보다 더 크다 ==> A 2번 사용, B 1번 사용
					ta[time] = bcs[abc2].p;
					tb[time] = bcs[bbc].p;
				}
				else { //B의 2번이 A의 2번보다 더 크다 ==> A 1번 사용, B 2번 사용
					ta[time] = bcs[abc].p;
					tb[time] = bcs[bbc2].p;
				}
			}
		}
	}
	else { // 안겹치면 각자거 사용
		ta[time] = bcs[abc].p;
		tb[time] = bcs[bbc].p;
	}
}

int solve() {
	int result = 0;
	createMap();
	int time = 0;
	charge(time);
	while (time++ < M) { //* move charge 순서 반대
		move(time);
		charge(time);
	}
	for (int i = 0; i <= M; i++)
		result += ta[i] + tb[i];

	//for (int i = 0; i <= M; i++)
	//	cout << ta[i] << " ";
	//cout << endl;
	//for (int i = 0; i <= M; i++)
	//	cout << tb[i] << " ";
	//cout << endl;
	return result;
}

int main() {
	freopen("input5644.txt", "r", stdin);
	cin >> T;
	for (int t = 1; t <= T; t++) {
		input();
		cout << "#" << t << " " << solve() << endl;
	}
}