/*
	2019.04.08
	

*/

#include <iostream>
#include <algorithm>

using namespace std;

int T, N, top, result_min, result_max;
int num[12], op[4], sel[11]; //숫자, 각 연산자 개수, 선택 연산자

void input() {
	cin >> N;
	result_max = -987654321, result_min = 987654321, top = 0;
	for (int i = 0; i < 4; i++) {
		cin >> op[i];
		top += op[i];
	}
	for (int i = 0; i < N; i++) {
		cin >> num[i];
	}
}

int cal() {
	int sum = num[0], op_id = 0;
	for (int i = 1; i < N; i++) {
		if (sel[op_id] == 0) sum += num[i];
		else if (sel[op_id] == 1) sum -= num[i];
		else if (sel[op_id] == 2) sum *= num[i];
		else sum /= num[i];  //if (sel[op_id] == 3)
		op_id++;
	}
	return sum;
}

void dfs(int d, int used) {
	if (used == top) { //연산자 다 정했으면
		int rt = cal();
		result_min = min(result_min, rt);
		result_max = max(result_max, rt);
		return;
	}
	for (int i = 0; i < 4; i++) {
		if (op[i] == 0) continue;
		sel[d] = i;
		op[i]--;
		dfs(d + 1, used + 1);
		op[i]++;
	}
}

int main() {
	freopen("input4008.txt", "r", stdin);
	cin >> T;
	for (int t = 1; t <= T; t++) {
		input();
		dfs(0, 0);
		cout << "#" << t << " " << result_max - result_min << "\n";;
	}
}