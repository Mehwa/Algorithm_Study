/*
	2019.04.05
	https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5V1SYKAaUDFAWu
	�� ���� A, B ���� Ȥ�� �ȳִ� ����� ���� ���� Ž���Ѵ�.
	���� Ƚ�� k�� ������Ű�� �ش� k���� �˻翡 �����ϸ� k�� ���� �ȴ�.

	***if ���� ġ������ �Ǽ�
	�Ʒ� �ڵ尡 �����ε�,
	if (i == 2) {
		if (dfs(injected, d + 1)) return true; //���� ����
	}
	else if (injected > 0) {

	}
	�̰� ���� �� �ٿ����ڴٰ� �Ʒ��� ���� ��ٰ� ���� Ʋ�ȴ�. ������ else if �� �տ� �ִ� if�� �ɸ��� �ǵ��Ѱǵ�, �ڿ� �ִ� if�� �ɸ���.
	�Դٰ� �ؿ� else if�� if�� ��ٰ� ��û ����ߴ�. �̻��ϰ� �������� 49�� �°� �ڲ� �ð� �ʰ��� ���µ�, ���ܿ��� �ɸ��� ����.
	if (i == 2) if (dfs(injected, d + 1)) return true; //���� ����
	else if(injected > 0) {}
*/


#include <iostream>
#include <cstring>

using namespace std;

int T, W, D, K;
bool film[13][20];

void input() {
	memset(film, 0, sizeof(film));
	cin >> D >> W >> K;
	for (int r = 0; r < D; r++) {
		for (int c = 0; c < W; c++) {
			cin >> film[r][c];
		}
	}
}

bool check() {
	for (int j = 0; j < W; j++) {
		int count = 1;
		bool prev = film[0][j];
		for (int i = 1; i < D; i++) {
			if (film[i][j] == prev) {
				count++;
				if (count == K)
					break;
			}
			else
				count = 1;
			prev = film[i][j];
		}
		if (count < K)
			return false;
	}
	return true;
}

bool dfs(int inject, int d) {
	if (d == D) return check();
	for (int i = 0; i < 3; i++) {
		if (i == 2) {
			if (dfs(inject, d + 1)) return true; //���� ����
		}
		else if (inject > 0) {
			bool tmp[20];
			memcpy(tmp, film[d], sizeof(film[d]));
			memset(film[d], i, sizeof(film[d])); //��ǰ ����
			if (dfs(inject - 1, d + 1)) return true;
			memcpy(film[d], tmp, sizeof(film[d]));
		}
	}
	return false;
}

int solve() {
	if (K == 1 || check()) return 0;
	for (int k = 1; k < K; k++) {
		if (dfs(k, 0)) return k;
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