/*
	2019.04.05
	https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRUN9KfZ8DFAUo&categoryId=AWXRUN9KfZ8DFAUo&categoryType=CODE
	ó�� �������� i ~ N���� �迭�� N /4 ���̸�ŭ �ɰ��� ���ڸ� ����� set�� �ְ�, K��° ���Ҹ� ã�´�.
	���� ������ �����µ�, charToNum() �Լ����� ABCDEF ���ڸ� 1�� �߸� �ִ� �ٶ��� Ʋ���Ÿ� �ε������� Ʋ�� �� �˰� ã�ٰ� �ð��� ���� ���ȴ�.
*/
#include <iostream>
#include <vector>
#include <string>
#include <set>

using namespace std;

int T, N, K;
string pass;

void input() {
	scanf("%d %d\n", &N, &K);
	getline(cin, pass);
}

int charToNum(char c) {
	if (c == 'A') return 10;
	if (c == 'B') return 11;
	if (c == 'C') return 12;
	if (c == 'D') return 13;
	if (c == 'E') return 14;
	if (c == 'F') return 15;
	else return c - '0';
}

int getDigit(int digit) {
	int rt = 1;
	for (int i = 0; i < digit; i++)
		rt *= 16;
	return rt;
}

int solve() {
	set<int, greater<int> > s;
	int a = N / 4; //�� ���� ����
	for (int i = 0; i < N; i++) {
		for (int k = 0; k < 4; k++) { //�� ���⿡ �ִ� ���ڵ��� �����
			int digit = a - 1;
			int num = 0;
			for (int j = i + a * k; j < i + a + a * k; j++) {
				int idx = j % N; //�ε��� ��� ��� ó������ ���ƿͼ� �ε��� ã�´�
				num += (int)charToNum(pass[idx]) * getDigit(digit--);
			}
			s.insert(num);
		}
	}
	int t = 1;
	int result;
	for (auto key : s) { //K��° ���� ã��
		if (t++ == K) {
			result = key;
			break;
		}
	}
	return result;
}

int main() {
	freopen("input5658.txt", "r", stdin);
	cin >> T;
	for (int t = 1; t <= T; t ++ ) {
		input();
		cout << "#" << t << " " << solve() << endl;
	}
}
