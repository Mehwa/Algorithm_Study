/*
	2019.04.08
	https://www.acmicpc.net/problem/16235

*/

#include <iostream>
#include <queue>

using namespace std;

int N, M, K;
int A[11][11], remain[11][11], dead[11][11];
priority_queue<int, vector<int>, greater<int>> tree[11][11];
int dr[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int dc[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

void input() {
	cin >> N >> M >> K;
	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			cin >> A[r][c];
			remain[r][c] = 5;
		}
	}
	for (int i = 0; i < M; i++) {
		int r, c, a;
		cin >> r >> c >> a;
		tree[r][c].push(a);
	}
}

void spring() {
	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			priority_queue<int, vector<int>, greater<int>> ntree;
			while (!tree[r][c].empty()) {
				int cur = tree[r][c].top(); tree[r][c].pop();
				if (remain[r][c] - cur >= 0) { //양분 충분하면, 먹고 자란다
					remain[r][c] -= cur;
					cur++;
					ntree.push(cur);
				}
				else {
					dead[r][c] += cur / 2;
				}
			}
			swap(tree[r][c], ntree);
		}
	}
}
void summer() {
	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			remain[r][c] += dead[r][c];
			dead[r][c] = 0;
		}
	}
}
void fall() {
	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			priority_queue<int, vector<int>, greater<int>> ntree;
			while (!tree[r][c].empty()) {
				int cur = tree[r][c].top(); tree[r][c].pop();
				if (cur < 5 || cur % 5 != 0) { ntree.push(cur); continue; }
				for (int i = 0; i < 8; i++) {
					int nr = r + dr[i], nc = c + dc[i];
					if (nr<1 || nr>N || nc<1 || nc>N) continue;
					tree[nr][nc].push(1);
				}
				ntree.push(cur);
			}
			swap(tree[r][c], ntree);
		}
	}
}
void winter() {
	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			remain[r][c] += A[r][c];
		}
	}
}
int output() {
	int sum = 0;
	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			sum += tree[r][c].size();
		}
	}
	return sum;
}

void sim() {
	while(K--) {
		spring();
		summer();
		fall();
		winter();
	}
}

int main() {
	freopen("input16235.txt", "r", stdin);
	input();
	sim();
	cout << output() << "\n";
}