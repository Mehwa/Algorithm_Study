#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int N, M, K;
int a[10][10];
int nu[10][10];
int d_tree[10][10];
vector<int> tree[10][10];

int dr[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int dc[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

void input() {
	cin >> N >> M >> K;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			cin >> a[r][c];
			nu[r][c] = 5;
		}
	}
	for (int i = 0; i < M; i++) {
		int x, y, age;
		cin >> x >> y >> age;
		tree[x-1][y-1].push_back(age);
	}
}

void spring() {
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			if (!tree[r][c].size()) continue;
			sort(tree[r][c].begin(), tree[r][c].end());
			for (int k = 0; k < tree[r][c].size(); k++) {
				nu[r][c] -= tree[r][c][k];
				if (nu[r][c] < 0) {
					nu[r][c] += tree[r][c][k];
					d_tree[r][c] += tree[r][c][k] / 2;
					tree[r][c].erase(tree[r][c].begin() + k);
					k--;
				}
				else tree[r][c][k]++;
			}
		}
	}
}

void summer() {
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			nu[r][c] += d_tree[r][c];
			d_tree[r][c] = 0;
		}
	}
}

void fall() {
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			for (int k = 0; k < tree[r][c].size(); k++) {
				if (tree[r][c][k] % 5 == 0) {
					for (int i = 0; i < 8; i++) {
						int nr = r + dr[i], nc = c + dc[i];
						if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
						tree[nr][nc].push_back(1);
					}
				}
			}
		}
	}
}

void winter() {
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			nu[r][c] += a[r][c];
		}
	}
}

int countTree() {
	int count = 0;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			count += tree[r][c].size();
		}
	}
	return count;
}

int main() {
	freopen("input.txt", "r", stdin);
	input();
	while (K--) {
		spring();
		summer();
		fall();
		winter();
	}
	cout << countTree() << endl;
}