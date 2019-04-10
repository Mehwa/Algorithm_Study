/*
	2019.04.10

*/
#include <iostream>
#include <algorithm>

using namespace std;

int T, N, M, C;
int map[10][10];
int A[5], B[5];
int dfs_result, result;
void input() {
	dfs_result = 0, result = 0;
	cin >> N >> M >> C;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			cin >> map[r][c];
		}
	}
}

void dfs(int arr[], int d, int sum, int square) {
	if (d == M) {
		dfs_result = max(square, dfs_result);
		return;
	}
	for (int i = 0; i < 2; i++) {
		if (sum + arr[d] * i > C) continue;
		dfs(arr, d + 1, sum + arr[d] * i, square + arr[d] * arr[d] * i); //* *i
	}
}

int cal(int r1, int c1, int r2, int c2) {
	int sum = 0;
	int idx = 0;
	for (int c = c1; c < c1 + M; c++)
		A[idx++] = map[r1][c];
	idx = 0;
	for (int c = c2; c < c2 + M; c++)
		B[idx++] = map[r2][c];
	dfs(A, 0, 0, 0);
	sum += dfs_result; dfs_result = 0;
	dfs(B, 0, 0, 0);
	sum += dfs_result; dfs_result = 0;
	return sum;
}

void solve() {
	for (int r1 = 0; r1 < N; r1++) {
		for (int c1 = 0; c1 < N; c1++) {
			if (c1 + M > N) continue; //¹üÀ§ ¹þ¾î³²
			for (int r2 = r1; r2 < N; r2++) {
				for (int c2 = 0; c2 < N; c2++) {
					if (c2 + M > N) continue; //¹üÀ§ ¹þ¾î³²
					if (r1 == r2 && c1 + M > c2) continue; //°ãÄ¡´Â ¿µ¿ª  //*r1==r2
					result = max(result, cal(r1, c1, r2, c2));
				}
			}
		}
	}
}

int main() {
	freopen("input2115.txt", "r", stdin);
	cin >> T;
	for (int t = 1; t <= T; t++) {
		input();
		solve();
		cout << "#" << t << " " << result << endl;
	}
}