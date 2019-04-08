/*
	2019.04.04
	https://www.acmicpc.net/problem/16926
	k�� ������ ������ 1 ~ min(N, M) / 2 �̴�
	�׸��� �� ������ ���� ������
	(k, k)        ��    (k, M-(k-1))
	  ��                      ��
	(N-(k-1), k)  ��   (N-(k-1), M-(k-1))

	ó���� M�� N���� �ߴٰ� Ʋ�ȴ�.
	�׸��� ���� �� ��, �������� �� �� while ���ǿ��� k�� �ƴ϶� �ܼ��� 1�� �ߴٰ� Ʋ�ȴ�.
*/
#include <iostream>
#include <algorithm>

using namespace std;

int N, M, R, a;
int A[301][301];

void input() {
	cin >> N >> M >> R;
	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= M; c++) {
			cin >> A[r][c];
		}
	}
	a = min(N, M);
	a /= 2;
}

void rotate() {
	while (R--) {
		for (int k = 1; k <= a; k++) {
			int next = 0, prev = A[k][k];
			int r = k, c = k;
			while(r < N - (k - 1)) { //�Ʒ���
				next = A[r + 1][k];
				A[r + 1][k] = prev;
				prev = next;
				r++;
			}
			while (c < M - (k - 1)) { //������
				next = A[r][c + 1];
				A[r][c + 1] = prev;
				prev = next;
				c++;
			}	
			while (r > k) { //����
				next = A[r - 1][c];
				A[r - 1][c] = prev;
				prev = next;
				r--;
			}
			while (c > k) { //����
				next = A[r][c - 1];
				A[r][c - 1] = prev;
				prev = next;
				c--;
			}
		}
	}
}
void output() {
	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= M; c++) {
			cout << A[r][c] << " ";
		}
		cout << endl;
	}
}

int main() {
	freopen("input16926.txt", "r", stdin);
	input();
	rotate();
	output();
}