/*
	2019.04.03
	https://www.acmicpc.net/problem/13458
	모든 방에서 총 감독관의 감시 인원수 만큼 빼고 남은 인원을 일반 감독관 몇명이 필요한지 계산한다.
	처음에 총 감독관이 있어도 되고 없어도 되는 것으로 문제를 잘못 이해해서 시간이 좀 걸렸다.
*/
#include <iostream>
#include <cmath>

using namespace std;

int N, B, C;
int A[1000000];
long long result;

void input() {
	result = 0;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> A[i];
	}
	cin >> B >> C;
}

void solve() {
	for (int i = 0; i < N; i++) {
		A[i] -= B;
		result++;
		if (A[i] <= 0) continue;
		result += ceil(A[i] / (double)C);
	}
}

int main() {
	freopen("input13458.txt", "r", stdin);
	input();
	solve();
	cout << result << endl;
}