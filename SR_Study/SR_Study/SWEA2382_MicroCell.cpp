/*
	2019.04.05
	https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV597vbqAH0DFAVl&categoryId=AV597vbqAH0DFAVl&categoryType=CODE
	���� ������ �ٸ��� �� �ȿ� n ���� �����ϰ� �ʿ� �ش� ���� �ӹ����� �ִ� ������ n ����
	������ ���� ������ ���� �ӹ����� �ִ� ĭ�� ������ �ʱ�ȭ���ִ� ���� �����ϱ� ���� �̵��� �� �ʱ�ȭ���� �ʰ� �� �ѹ��� 0���� �ʱ�ȭ
	(��迡�� ū �ְ� ���� ���Դµ� �ش� ��ġ�� �ִ� �ְ� ������ �����鼭 0 ����� ���� ����)
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
			if (nr == 0 || nr == N - 1 || nc == 0 || nc == N - 1) { //��� ������
				cur.n /= 2;
				cur.d = nd[cur.d];
				if (cur.n == 0) continue;
			}
			else if (cur.n < map[nr][nc]) { //����ĭ�� ������ ū ������ �̹� ������
				//map[cur.r][cur.c] = 0;
				map[nr][nc] += cur.n;
				continue;
			}
			//�̵�
			//map[cur.r][cur.c] = 0;
			map[nr][nc] = cur.n;
			cur.r = nr, cur.c = nc;
			npq.push(cur);
		}
		while (!npq.empty()) {
			CELL cur = npq.top(); npq.pop();
			if (map[cur.r][cur.c] != cur.n) { //�̵� �� ���� ĭ�� �̻��� ���� �����ߴٴ� �� �ٸ� ������ �������ٴ� ��
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