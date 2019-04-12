/*
	2019.04.12

*/
#include <iostream>
#include <cstring>
using namespace std;
int T, D, W, K;
int f[13][20], tmp[13][20];
void input() {
	cin >> D >> W >> K;
	for (int r = 0; r < D; r++) {
		for (int c = 0; c < W; c++) {
			cin >> f[r][c];
		}
	}
}
bool check() {
	for (int c = 0; c < W; c++) {
		bool rt = false;
		int same = 1;
		for (int r = 0; r < D - 1; r++) {
			if (f[r][c] == f[r + 1][c]) same++;
			else same = 1;
			if (same == K) {
				rt = true;
				break;
			}
		}
		if (!rt) return false;
	}
	return true;
}
void injection(int d, int val) {
	for (int c = 0; c < W; c++)
		f[d][c] = val;
}
bool dfs(int d, int inject) {
	if (d == D || inject == 0) return check();
	for (int i = -1; i < 2; i++) {
		if (i == -1) { if(dfs(d + 1, inject)) return true; continue; }
		memcpy(tmp[d], f[d], sizeof(f[d]));
		//memset(f[d], i, sizeof(f[d])); //i 약품 투여
		injection(d, i);
		if(dfs(d + 1, inject - 1)) return true;
		memcpy(f[d], tmp[d], sizeof(f[d]));
	}
	return false;
}
int solve() {
	if (check()) return 0;
	for (int k = 1; k < K; k++) {
		if (dfs(0, k)) return k;
	}
	return K;
}
int main() {
	freopen("input2112.txt", "r", stdin);
	cin >> T;
	for (int t = 1; t <= T; t++) {
		input();
		cout << "#" << t << " " << solve() << endl;
	}
}