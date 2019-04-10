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
int dr[] = { 0, -1, 0, 1, 0 }; //����, ��, ��, ��, ��
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
		cin >> bcs[i].c >> bcs[i].r >> bcs[i].dist >> bcs[i].p; //* r, c �ݴ�
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
				insertBC(bid, nr, nc); //* bid�� �־���ϴµ� p�� �־���
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
	if (abc == bbc) { //���� �����Ϸ��� BC�� ���� ��
		if (map[ar][ac].size() == 1 && map[br][bc].size() == 1) { //�Ѵ� �ϳ���
			ta[time] = bcs[abc].p / 2;
			tb[time] = bcs[bbc].p / 2;
		}
		else {
			if (map[ar][ac].size() == 1 && map[br][bc].size() > 1) { //A�� 1�� B�� 2�� �̻�
				int bbc2 = map[br][bc][1];
				ta[time] = bcs[abc].p;
				tb[time] = bcs[bbc2].p;
			}
			else if (map[ar][ac].size() > 1 && map[br][bc].size() == 1) { // A�� 2�� �̻� B�� 1��
				int abc2 = map[ar][ac][1];
				ta[time] = bcs[abc2].p;
				tb[time] = bcs[bbc].p;
			}
			else { //�� �� 2�� �̻�
				int abc2 = map[ar][ac][1], bbc2 = map[br][bc][1];
				if (bcs[abc2].p > bcs[bbc2].p) { //A�� 2���� B�� 2������ �� ũ�� ==> A 2�� ���, B 1�� ���
					ta[time] = bcs[abc2].p;
					tb[time] = bcs[bbc].p;
				}
				else { //B�� 2���� A�� 2������ �� ũ�� ==> A 1�� ���, B 2�� ���
					ta[time] = bcs[abc].p;
					tb[time] = bcs[bbc2].p;
				}
			}
		}
	}
	else { // �Ȱ�ġ�� ���ڰ� ���
		ta[time] = bcs[abc].p;
		tb[time] = bcs[bbc].p;
	}
}

int solve() {
	int result = 0;
	createMap();
	int time = 0;
	charge(time);
	while (time++ < M) { //* move charge ���� �ݴ�
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