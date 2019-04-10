/*
	2019.04.10

*/

#include <iostream>
#include <cstring>
using namespace std;
int T, N, X;
int map[20][20];
int load[20];

void input() {
	cin >> N >> X;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			cin >> map[r][c];
		}
	}
}

bool check() {
	int same = 1;
	for (int i = 0; i < N - 1; i++) {
		int diff = abs(load[i] - load[i + 1]);
		if (diff > 1) return false; //2이상이면 못감
		else if (diff == 0) { //평지
			same++;
		}
		else {
			if (load[i] > load[i + 1]) { //내리막
				int start = i + 1, end = start + X;
				for (int j = start; j < end; j++) {
					if (load[start] != load[j] || j >= N) 
						return false;
				}
				i = end - 2; 
				same = 0; //* 1로 했었음
			}
			else { //오르막
				if (same < X) return false;
				same = 1;
			}
		}
	}
	return true;
}

int solve() {
	int cnt = 0;
	for (int r = 0; r < N; r++) {
		memcpy(load, map[r], sizeof(load));
		if (check()) cnt++;
	}
	for (int c = 0; c < N; c++) {
		for (int r = 0; r < N; r++) {
			load[r] = map[r][c];
		}
		if (check()) cnt++;
	}
	return cnt;
}

int main() {
	freopen("input4014.txt", "r", stdin);
	cin >> T;
	for (int t = 1; t <= T; t++) {
		input();
		cout << "#" << t << " " << solve() << endl;
	}
}