/*
	풀다 포기
*/

#include <iostream>
#include <cstring>
using namespace std;

#define U 0
#define D 1
#define F 2
#define B 3
#define L 4
#define R 5

#define WH 0
#define YE 1
#define RE 2
#define OR 3
#define GR 4
#define BL 5

struct CMD {
	char p, d;
};
CMD cmd[1000];
int T, N;
int init_cube[6][3][3] = { { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} },
					  { {1, 1, 1}, {1, 1, 1}, {1, 1, 1} },
					  { {2, 2, 2}, {2, 2, 2}, {2, 2, 2} },
					  { {3, 3, 3}, {3, 3, 3}, {3, 3, 3} },
					  { {4, 4, 4}, {4, 4, 4}, {4, 4, 4} },
					  { {5, 5, 5}, {5, 5, 5}, {5, 5, 5} },
};
int cube[6][3][3];

void input() {
	memcpy(cube, init_cube, sizeof(cube));
	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> cmd[i].p >> cmd[i].d;
}
void output() {
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			if (cube[U][r][c] == WH) cout << "w";
			else if (cube[U][r][c] == YE) cout << "y";
			else if (cube[U][r][c] == RE) cout << "r";
			else if (cube[U][r][c] == OR) cout << "o";
			else if (cube[U][r][c] == GR) cout << "g";
			else if (cube[U][r][c] == BL) cout << "b";
		}
		cout << endl;
	}
}

void rr(int p) {
	int tmp[9]; int idx = 0;
	for (int r = 0; r < 3; r++)
		for (int c = 0; c < 3; c++)
			tmp[idx++] = cube[p][r][c];
	idx = 0;
	for (int c = 2; c--;)
		for (int r = 0; r < 3; r++)
			cube[p][r][c] = tmp[idx++];
}
void rl(int p) {
	int tmp[9]; int idx = 0;
	for (int r = 0; r < 3; r++)
		for (int c = 0; c < 3; c++)
			tmp[idx++] = cube[p][r][c];
	idx = 0;
	for (int c = 0; c < 3; c++)
		for (int r = 2; r--;)
			cube[p][r][c] = tmp[idx++];
}
void rrr(int p1, int p2, int p3, int p4) {
	//int tmp[12]; int idx = 0;
	////뽑기
	//for (int c = 0; c < 3; c++)
	//	tmp[idx++] = cube[p1][2][c];
	//for (int r = 0; r < 3; r++)
	//	tmp[idx++] = cube[p2][r][0];
	//for (int c = 2; c >= 0; c--)
	//	tmp[idx++] = cube[p3][0][c];
	//for (int r = 2; r >= 0; r--)
	//	tmp[idx++] = cube[p4][r][2];
	////넣기
	//idx = 0;
	//for (int r = 0; r < 3; r++)
	//	cube[p2][r][0] = tmp[idx++];
	//for (int c = 2; c >= 0; c--)
	//	cube[p3][0][c] = tmp[idx++];
	//for (int r = 2; r >= 0; r--)
	//	cube[p4][r][2] = tmp[idx++];
	//for (int c = 0; c < 3; c++)
	//	cube[p1][2][c] = tmp[idx++];
}
void rrl(int p1, int p2, int p3, int p4) {
	//int tmp[12]; int idx = 0;
	////뽑기
	//for (int c = 2; c >= 0; c--)
	//	tmp[idx++] = cube[p1][2][c];
	//for (int r = 0; r < 3; r++)
	//	tmp[idx++] = cube[p4][r][2];
	//for (int c = 0; c < 3; c++)
	//	tmp[idx++] = cube[p3][0][c];
	//for (int r = 2; r >= 0; r--)
	//	tmp[idx++] = cube[p2][r][0];
	////넣기
	//idx = 0;
	//for (int r = 0; r < 3; r++)
	//	cube[p4][r][2] = tmp[idx++];
	//for (int c = 0; c < 3; c++)
	//	cube[p3][0][c] = tmp[idx++];
	//for (int r = 2; r >= 0; r--)
	//	cube[p2][r][0] = tmp[idx++];
	//for (int c = 2; c >= 0; c--)
	//	cube[p1][2][c] = tmp[idx++];
}

void action(CMD cmd) {
	if (cmd.p == 'U') {
		if (cmd.d == '+') { rr(U); rrr(B, R, F, L); }
		else if (cmd.d == '-') { rl(U); rrl(B, R, F, L); }
	}
	else if (cmd.p == 'D') {
		if (cmd.d == '+') { rr(D); rrr(B, L, F, R); }
		else if (cmd.d == '-') { rl(D); rrl(B, L, F, R); }
	}
	else if (cmd.p == 'F') {
		if (cmd.d == '+') { rr(F); rrr(U, R, D, L); }
		else if (cmd.d == '-') { rl(F); rrl(U, R, D, L); }
	}
	else if (cmd.p == 'B') {
		if (cmd.d == '+') { rr(B); rrr(U, L, D, R); }
		else if (cmd.d == '-') { rl(B); rrl(U, L, D, R); }
	}
	else if (cmd.p == 'L') {
		if (cmd.d == '+') { rr(L); rrr(B, U, F, D); }
		else if (cmd.d == '-') { rl(L); rrl(B, U, F, D); }
	}
	else { //if (cmd.p == 'R') {
		if (cmd.d == '+') { rr(R); rrr(B, D, F, U); }
		else if (cmd.d == '-') { rl(R); rrl(B, D, F, U); }
	}
}

void sim() {
	for (int i = 0; i < N; i++) {
		action(cmd[i]);
	}
}

int main() {
	freopen("input5373.txt", "r", stdin);
	cin >> T;
	for (int t = 1; t <= T; t++) {
		input();
		sim();
		output();
	}
}