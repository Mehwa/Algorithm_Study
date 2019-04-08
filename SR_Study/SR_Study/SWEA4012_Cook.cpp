/*
	2019.04.08
	

*/

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int T, N, N2;
int A[8], B[8];
int S[17][17];
int result;

void input() {
	result = 987654321;
	memset(S, 0, sizeof(S));
	cin >> N;
	N2 = N / 2;
	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			cin >> S[r][c];
		}
	}
}

void findB() {
	int a_idx = 0, b_idx = 0;
	for (int i = 1; i <= N; i++) {
		if (A[a_idx] == i) {
			a_idx++;  continue;
		}
		B[b_idx++] = i;
	}
}

int score(int arr[]) {
	int sum = 0;
	for (int r = 0; r < N2; r++) {
		for (int c = 0; c < N2; c++) {
			sum += S[arr[r]][arr[c]];
		}
	}
	return sum;
}

void dfs(int d, int pi) {
	if (d == N2) {
		findB();
		int a = score(A);
		int b = score(B);
		result = min(result, abs(a - b));
		return;
	}
	for (int i = pi + 1; i <= N; i++) {
		A[d] = i;
		dfs(d + 1, i);
	}
}

int main() {
	freopen("input4012.txt", "r", stdin);
	cin >> T;
	for (int t = 1; t <= T; t++) {
		input();
		dfs(0, 0);
		cout << "#" << t << " " << result << "\n";
	}
}