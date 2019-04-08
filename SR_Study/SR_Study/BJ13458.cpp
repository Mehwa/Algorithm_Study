/*
	2019.04.03
	https://www.acmicpc.net/problem/13458
	��� �濡�� �� �������� ���� �ο��� ��ŭ ���� ���� �ο��� �Ϲ� ������ ����� �ʿ����� ����Ѵ�.
	ó���� �� �������� �־ �ǰ� ��� �Ǵ� ������ ������ �߸� �����ؼ� �ð��� �� �ɷȴ�.
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