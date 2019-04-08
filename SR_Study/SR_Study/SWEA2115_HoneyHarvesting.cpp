/*
	2019.04.05
	https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV597vbqAH0DFAVl&categoryId=AV597vbqAH0DFAVl&categoryType=CODE
	저번 풀이랑 다른게, 배열의 각 원소를 쓸 지 말지만 (0 or 1) 탐색하도록 했다. 속도 훨씬 빠름
	그리고 A, B 위치 완전 탐색할 때, 범위 넘어가는 것 체크 안해줘서 틀렸었다. 실수 주의
*/

#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int T, N, M, C, result, rt;
int map[10][10];
int A[5];
int B[5];

void input() {
	memset(map, 0, sizeof(map));
	result = 0;
	cin >> N >> M >> C;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			cin >> map[r][c];
		}
	}
}

void dfs(int d, int sum, int square, int arr[]) {
	if (sum > C) return; //합이 C가 넘으면
	if (d == M) {
		rt = max(rt, square);
		return;
	}
	for (int i = 0; i < 2; i++) {
		sum += i * arr[d];
		square += i * arr[d] * arr[d];
		dfs(d + 1, sum, square, arr);
		sum -= i * arr[d];
		square -= i * arr[d] * arr[d];
	}
}

void setArr(int r1, int c1, int r2, int c2) {
	int i = 0;
	for (int c = c1; c < c1 + M; c++) {
		A[i++] = map[r1][c];
	}
	i = 0;
	for (int c = c2; c < c2 + M; c++) {
		B[i++] = map[r2][c];
	}
}

void solve() {
	for (int r1 = 0; r1 < N; r1++) {
		for (int c1 = 0; c1 < N; c1++) {
			if (c1 + M - 1 >= N) continue; //범위 벗어남
			for (int r2 = r1; r2 < N; r2++) {
				for (int c2 = 0; c2 < N; c2++) {
					if (c2 + M - 1 >= N) continue; //범위 벗어남
					if (r1 == r2 && c1 + M - 1 >= c2) continue; //겹치는 영역
					int sum = 0;
					setArr(r1, c1, r2, c2);
					rt = 0;
					dfs(0, 0, 0, A);
					sum += rt;
					rt = 0;
					dfs(0, 0, 0, B);
					sum += rt;
					result = max(result, sum);
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