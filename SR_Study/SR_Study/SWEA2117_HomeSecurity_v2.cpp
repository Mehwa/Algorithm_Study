/*
	2019.04.11

*/
#include <iostream>
#include <algorithm>
using namespace std;

struct HOUSE {
	int r, c;
};
int T, N, M, max_k, nh;
HOUSE h[400];
int K[30];

void input() {
	max_k = 0, nh = 0;
	cin >> N >> M;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			int x;
			cin >> x;
			if (x == 1) { 
				h[nh].r = r, h[nh].c = c; 
				nh++;
			}
		}
	}
	int k = 1;
	while (1) {
		K[k] = k * k + (k - 1)*(k - 1);
		if (nh * M < K[k]) break; //최대 가능 이익보다 비용이 커지면 할 필요 없음
		max_k = k++;
	}
}
int cost(int r, int c, int k) {
	int cnt = 0;
	for (int i = 0; i < nh; i++) {
		if (abs(r - h[i].r) + abs(c - h[i].c) <= k - 1) { //서비스 가능 지역
			cnt++;
		}
	}
	if (cnt * M >= K[k]) return cnt;
	else return -1; //손해
}
int solve() {
	int ck = max_k, rt = 0;
	while (ck > 1) {
		for (int r = 0; r < N; r++) {
			for (int c = 0; c < N; c++) {
				rt = max(rt, cost(r, c, ck));
			}
		}
		if (rt > 0) return rt;
		ck--;
	}
	return 1; //k가 1일때만 가능하다면 답은 1
}
int main() {
	freopen("input2117.txt", "r", stdin);
	cin >> T;
	for (int t = 1; t <= T; t++) {
		input();
		cout << "#" << t << " " << solve() << endl;
	}
}