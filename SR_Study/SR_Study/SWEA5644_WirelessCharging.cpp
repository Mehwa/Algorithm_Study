/*
	2019.04.02
	https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRDL1aeugDFAUo&categoryId=AWXRDL1aeugDFAUo&categoryType=CODE
	���� �� ĭ�� vector�� �ؼ�, �ش� ĭ���� �����ϴ� BC�� �Ŀ��� ū ������ �ְ� 
	A, B�� �̵���Ű�� �ش� ĭ���� ���� ������ �� �� ���� ū ��, �� 0��°�� ���� ���ϰ�, 
	���� ���� ��ġ�� �κ��� ���� ó�� ���ش�.
	
	ó���� if/else �� ������ ���ǿ� ���� ������ ó�� �ߴµ�, ���� �ȳ��ͼ� ���� Ž������ �ٲ�µ��� ���� �ȳ��Դ�.
	��������� ���� ����� �κп��� BC�� ���� ���� ���� ���� �� sort�� ���� ���� ��������.
*/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

int T, M, A;
vector<int> map[10][10];
bool visit[10][10];
int a_trace[100];
int b_trace[100];
int result;

struct BC {
	int r, c, cc, p;
};
vector<BC> bcs;
struct POS {
	int r, c, bc;
};

int dr[] = { 0, -1, 0, 1, 0 };
int dc[] = { 0, 0, 1, 0, -1 };

bool comp(int a, int b) {
	return bcs[a].p > bcs[b].p;
}

void input() {
	bcs.clear();
	memset(map, 0, sizeof(map));
	result = 0;
	cin >> M >> A;
	for (int i = 0; i < M; i++)
		cin >> a_trace[i];
	for (int i = 0; i < M; i++)
		cin >> b_trace[i];
	for (int i = 0; i < A; i++) {
		BC tmp;
		cin >> tmp.c >> tmp.r >> tmp.cc >> tmp.p;
		bcs.push_back({ tmp.r - 1, tmp.c - 1, tmp.cc, tmp.p });
	}
}
void bfs(int bc_id) {
	memset(visit, 0, sizeof(visit));
	queue<pair<int, int>> q;
	q.push({ bcs[bc_id].r, bcs[bc_id].c });
	visit[bcs[bc_id].r][bcs[bc_id].c] = true;
	map[bcs[bc_id].r][bcs[bc_id].c].push_back(bc_id);
	if (map[bcs[bc_id].r][bcs[bc_id].c].size() > 1)
		sort(map[bcs[bc_id].r][bcs[bc_id].c].begin(), map[bcs[bc_id].r][bcs[bc_id].c].end(), comp);
	int count = 0;
	while (q.size()) {
		for (int size = q.size(); size--;) {
			pair<int, int> cur = q.front(); q.pop();
			for (int i = 1; i < 5; i++) {
				int nr = cur.first + dr[i], nc = cur.second + dc[i];
				if (nr < 0 || nr >= 10 || nc < 0 || nc >= 10 || visit[nr][nc]) continue;
				q.push({ nr, nc });
				visit[nr][nc] = true;
				map[nr][nc].push_back(bc_id);
				if (map[nr][nc].size() > 1)
					sort(map[nr][nc].begin(), map[nr][nc].end(), comp);
			}
		}
		if (++count == bcs[bc_id].cc) break;
	}
}
void createMap() {
	for (int i = 0; i < bcs.size(); i++)
		bfs(i);
}

int chargeAB(POS a, POS b) {
	vector<int> a_bcs = map[a.r][a.c];
	vector<int> b_bcs = map[b.r][b.c];
	if (a_bcs.size() == 0 && b_bcs.size() == 0) return 0;
	else if (a_bcs.size() == 0 && b_bcs.size() >= 1) return bcs[b_bcs[0]].p;
	else if (a_bcs.size() >= 1 && b_bcs.size() == 0) return bcs[a_bcs[0]].p;
	else {
		int charge = 0;
		for (int i = 0; i < a_bcs.size(); i++) {
			if (i > 2) break;
			a.bc = a_bcs[i];
			for (int j = 0; j < b_bcs.size(); j++) {
				if (j > 2) break;
				b.bc = b_bcs[j];
				if (a.bc == b.bc) charge = max(charge, bcs[a.bc].p / 2 + bcs[b.bc].p / 2);
				else charge = max(charge, bcs[a.bc].p + bcs[b.bc].p);
			}
		}
		return charge;
	}
}

void move() {
	POS a, b;
	a = { 0, 0, -1}, b = { 9, 9, -1};
	result += chargeAB(a, b);
	for(int m = 0; m < M; m++) {
		a.r = a.r + dr[a_trace[m]], a.c = a.c + dc[a_trace[m]];
		b.r = b.r + dr[b_trace[m]], b.c = b.c + dc[b_trace[m]];
		result += chargeAB(a, b);
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	cin >> T;
	for (int t = 1; t <= T; t++) {
		input();
		createMap();
		move();
		cout << "#" << t << " " << result << endl;
	}
}