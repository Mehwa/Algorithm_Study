/*
	2019.04.10

*/

#include <iostream>
#include <algorithm>
using namespace std;

int N, result;
int T[16], P[16];

void input() {
	result = 0;
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> T[i] >> P[i];
	}
}

void dfs(int d, int remain, int profit) {
	if (d == N + 1) {
		result = max(result, profit);
		return;
	}
	for (int i = 0; i < 2; i++) {
		if (i == 0) { //���Ѵ�
			if(remain == 0) dfs(d + 1, remain, profit);
			else dfs(d + 1, remain - 1, profit);
		}
		else { //�Ѵ�
			if (remain > 0) continue; //���� �� �� �ϴ� ��
			if (T[d] > N - d + 1) continue; //���� �Ⱓ �Ѿ
			dfs(d + 1, T[d] - 1, profit + P[d]);
		}
	}
}

int main() {
	freopen("input14501.txt", "r", stdin);
	input();
	dfs(1, 0, 0);
	cout << result;
}