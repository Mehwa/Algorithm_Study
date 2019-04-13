#include <iostream>
#include <algorithm>
using namespace std;
int N, M;
int map[50][50];
int cdist[100][13]; //각집으로부터 각치킨집까지 거리
int cd[13]; //어떤 치킨집 살릴건지
struct POS { int r, c; };
POS h[100], ch[13];
int nh, nc, result;
void input() {
	nh = 0, nc = 0, result = 987654321;
	cin >> N >> M;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			cin >> map[r][c];
			if (map[r][c] == 1) {
				h[nh].r = r, h[nh].c = c;
				nh++;
			}
			else if (map[r][c] == 2) {
				ch[nc].r = r, ch[nc].c = c;
				nc++;
			}
		}
	}
}
void calDist() {
	for (int i = 0; i < nh; i++) {
		for (int j = 0; j < nc; j++) {
			//i집으로부터 j치킨집까지 거리
			cdist[i][j] = abs(h[i].r - ch[j].r) + abs(h[i].c - ch[j].c);
		}
	}
}
int sumDist() {
	int sum = 0;
	for (int i = 0; i < nh; i++) {
		int min_d = 987654321;
		for (int j = 0; j < nc; j++) {
			if (cd[j] == 0) continue;
			min_d = min(min_d, cdist[i][j]);
		}
		sum += min_d;
	}
	return sum;
}

void choose() {
	for (int i = 0; i < M; i++) {
		cd[i] = 1;
	}
	sort(cd, cd + nc);
	do {
		result = min(result, sumDist());
	} while (next_permutation(cd, cd + nc));
}
int main() {
	freopen("input15686.txt", "r", stdin);
	input();
	calDist();
	choose();
	cout << result;
}