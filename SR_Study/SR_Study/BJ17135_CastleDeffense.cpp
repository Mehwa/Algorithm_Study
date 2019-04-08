/*
	2019.04.07
	https://www.acmicpc.net/problem/17135
	ó���� �ü� ���� ��ġ�� for������ ����Ž���ϰ�, 
	���� ���縦 ��� �迭�� �����ϰ�, �̸� ��ȸ�ϸ鼭 �ü����� Ȱ�� ��� ������ �ݺ��Ѵ�.
	�� ������ �κ��� ���� �ϱ� ���ؼ� Ž�� row�� ��ĭ ���ҽ�Ű���� �ߴ�.
	�ùķ��̼� �������� �̷��� �迭�� ������ ��� �ð� ���⵵�� �ظ��ϸ� ������ �� ������,
	������, ���� ���縦 �Ź� Ȯ��������ϱ� ������ for���� �׻� �� ����� n��ŭ ���� �ȴ�.
	ȿ�������� �Ϸ���, ���� ����� �� �ڷ� ������ n�� �ٿ����鼭 Ž���ϸ� �� ������ ���� �� ���� �� ����.
*/
#include <iostream>
#include <algorithm>

using namespace std;

struct ENEMY {
	int r, c;
	bool alive;
};
int N, M, D;
int result;
ENEMY en[225];
int en_size;

void input() {
	result = 0;
	en_size = 0;
	cin >> N >> M >> D;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < M; c++) {
			int x;
			cin >> x;
			if (x) {
				en[en_size].r = r, en[en_size].c = c, en[en_size].alive = true;
				en_size++;
			}
		}
	}
}

void init() {
	for (int i = 0; i < en_size; i++) {
		en[i].alive = true;
	}
}

void sim(int a1, int a2, int a3) {
	int kiled = 0;
	int cur_row = N, remain = en_size;
	while (remain) {
		int a1_shoot = -1, a2_shoot = -1, a3_shoot = -1;
		int a1_min_d = 300, a2_min_d = 300, a3_min_d = 300;
		for (int i = 0; i < en_size; i++) { //�ü��� �� ���� ���ϱ�
			ENEMY cur = en[i];
			if (!en[i].alive) continue;
			int a1_dist = abs(cur.r - cur_row) + abs(cur.c - a1);
			int a2_dist = abs(cur.r - cur_row) + abs(cur.c - a2);
			int a3_dist = abs(cur.r - cur_row) + abs(cur.c - a3);
			if (a1_dist <= D) {
				if (a1_dist < a1_min_d) { //1�� �ü�
					a1_min_d = a1_dist;
					a1_shoot = i;
				}
				else if (a1_dist == a1_min_d && cur.c < en[a1_shoot].c) {
					a1_min_d = a1_dist;
					a1_shoot = i;
				}
			}
			if (a2_dist <= D) {
				if (a2_dist < a2_min_d) { //2�� �ü�
					a2_min_d = a2_dist;
					a2_shoot = i;
				}
				else if (a2_dist == a2_min_d && cur.c < en[a2_shoot].c) {
					a2_min_d = a2_dist;
					a2_shoot = i;
				}
			}
			if (a3_dist <= D) {
				if (a3_dist < a3_min_d) { //3�� �ü�
					a3_min_d = a3_dist;
					a3_shoot = i;
				}
				else if (a3_dist == a3_min_d && cur.c < en[a3_shoot].c) {
					a3_min_d = a3_dist;
					a3_shoot = i;
				}
			}
		}

		//���� ���δ�
		if (a1_shoot >= 0) {
			if (en[a1_shoot].alive) {
				en[a1_shoot].alive = false;
				remain--;
				kiled++;
			}
		}
		if (a2_shoot >= 0) {
			if (en[a2_shoot].alive) {
				en[a2_shoot].alive = false;
				remain--;
				kiled++;
			}
		}
		if (a3_shoot >= 0) {
			if (en[a3_shoot].alive) {
				en[a3_shoot].alive = false;
				remain--;
				kiled++;
			}
		}

		//�� ������
		cur_row--;
		for (int i = 0; i < en_size; i++) {
			if (!en[i].alive) continue;
			if (en[i].r == cur_row) {
				remain--;
				en[i].alive = false;
			}
		}
	}
	result = max(result, kiled);
}

void archor() {
	for (int a1 = 0; a1 < M - 2; a1++) {
		for (int a2 = a1 + 1; a2 < M - 1; a2++) {
			for (int a3 = a2 + 1; a3 < M; a3++) {
				init();
				sim(a1, a2, a3);
			}
		}
	}
}

int main() {
	freopen("input17135.txt", "r", stdin);
	input();
	archor();
	cout << result << endl;
}