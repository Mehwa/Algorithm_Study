/*
	2019.04.05
	https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRUN9KfZ8DFAUo&categoryId=AWXRUN9KfZ8DFAUo&categoryType=CODE
	처음 시작점을 i ~ N까지 배열을 N /4 길이만큼 쪼개서 숫자를 만들어 set에 넣고, K번째 원소를 찾는다.
	문제 접근은 쉬웠는데, charToNum() 함수에서 ABCDEF 숫자를 1씩 잘못 넣는 바람에 틀린거를 인덱스에서 틀린 줄 알고 찾다가 시간만 많이 버렸다.
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
	int a = N / 4; //한 변의 길이
	for (int i = 0; i < N; i++) {
		for (int k = 0; k < 4; k++) { //네 방향에 있는 숫자들을 만든다
			int digit = a - 1;
			int num = 0;
			for (int j = i + a * k; j < i + a + a * k; j++) {
				int idx = j % N; //인덱스 벗어날 경우 처음으로 돌아와서 인덱스 찾는다
				num += (int)charToNum(pass[idx]) * getDigit(digit--);
			}
			s.insert(num);
		}
	}
	int t = 1;
	int result;
	for (auto key : s) { //K번째 원소 찾기
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
