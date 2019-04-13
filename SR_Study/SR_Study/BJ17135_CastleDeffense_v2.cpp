#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
int N, M, D;
int map[15][15];
struct EN{ int r, c, dead; };
struct AR { int r, c, target, t_dist; };
EN en[255];
AR ar[3];
int tenn = 0, enn = 0, result = 0, nkilled = 0;
void input() {
	cin >> N >> M >> D;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < M; c++) {
			cin >> map[r][c];
			if (map[r][c]) {
				en[enn].r = r, en[enn].c = c, en[enn].dead = 0;
				enn++;
			}
		}
	}
	tenn = enn;
}

void findTarget() {
	for (int i = 0; i < enn; i++) {
		EN cur = en[i];
		for (int a = 0; a < 3; a++) {
			int dist = abs(cur.r - ar[a].r) + abs(cur.c - ar[a].c);
			if (dist > D) continue;
			if (ar[a].target == -1 || dist < ar[a].t_dist || ((dist == ar[a].t_dist) && (cur.c < en[ar[a].target].c))) { //* 타겟 없을 때 처리(처음)
				ar[a].target = i;
				ar[a].t_dist = dist;
			}
		}
	}
}

void shoot() {
	for (int a = 0; a < 3; a++) {
		if (ar[a].target == -1) continue; //*
		en[ar[a].target].dead = 1;
	}
}

void dead() {
	int cur_row = ar[0].r - 1;
	int nenn = 0;
	for (int i = 0; i < enn; i++) {
		if (en[i].dead) { nkilled++; continue; }
		if (en[i].r == cur_row) { continue; }
		en[nenn++] = en[i];
	}
	enn = nenn;
}

void getDown() {	
	for (int a = 0; a < 3; a++) {
		ar[a].r--; ar[a].target = -1; //*타겟 초기화
	}
}


void sim() {
	EN ten[255];
	AR tar[3];
	memcpy(ten, en, sizeof(ten)); //* 적, 궁수 초기화
	memcpy(tar, ar, sizeof(tar));
	ar[0].t_dist = 1000, ar[1].t_dist = 1000, ar[2].t_dist = 1000;
	ar[0].target = -1, ar[1].target = -1, ar[2].target = -1;
	nkilled = 0, enn = tenn;
	while (enn) {
		findTarget();
		shoot();
		dead();
		getDown();
	}
	result = max(result, nkilled);
	memcpy(en, ten, sizeof(en));
	memcpy(ar, tar, sizeof(ar));
}

void archor_pos() {
	ar[0].r = N, ar[1].r = N, ar[2].r = N;
	for (int a1 = 0; a1 < M-2; a1++) {
		for (int a2 = a1 + 1; a2 < M-1; a2++) {
			for (int a3 = a2 + 1; a3 < M; a3++) {
				ar[0].c = a1, ar[1].c = a2, ar[2].c = a3;
				sim();
			}
		}
	}
}
int main() {
	freopen("input17135.txt", "r", stdin);
	input();
	archor_pos();
	cout << result;
}