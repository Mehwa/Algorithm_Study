/*
	2019.04.05
	https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5V1SYKAaUDFAWu
	각 층에 A, B 투입 혹은 안넣는 경우의 수를 완전 탐색한다.
	투입 횟수 k를 증가시키며 해당 k에서 검사에 성공하면 k가 답이 된다.

	***if 관련 치명적인 실수
	아래 코드가 정답인데,
	if (i == 2) {
		if (dfs(injected, d + 1)) return true; //투입 안함
	}
	else if (injected > 0) {

	}
	이걸 라인 수 줄여보겠다고 아래와 같이 썼다가 많이 틀렸다. 문제는 else if 가 앞에 있는 if에 걸리길 의도한건데, 뒤에 있는 if에 걸린다.
	게다가 밑에 else if를 if로 썼다가 엄청 고생했다. 이상하게 문제에서 49개 맞고 자꾸 시간 초과가 났는데, 예외에서 걸린것 같다.
	if (i == 2) if (dfs(injected, d + 1)) return true; //투입 안함
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
			if (dfs(inject, d + 1)) return true; //투입 안함
		}
		else if (inject > 0) {
			bool tmp[20];
			memcpy(tmp, film[d], sizeof(film[d]));
			memset(film[d], i, sizeof(film[d])); //약품 투입
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