#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int T, D, W, K;
bool f[13][20]; //[D][W]
int ch[3] = { -1, 0, 1 };//no, A, B
int result = 30;

void init() {
	result = 30;
	memset(f, 0, sizeof(f));
}

void input() {
	cin >> D >> W >> K;
	for (int i = 0; i < D; i++) {
		for (int j = 0; j < W; j++) {
			cin >> f[i][j];
		}
	}
}

bool test() {
	for (int j = 0; j < W; j++) {
		int count = 1;
		bool prev = f[0][j];
		for (int i = 1; i < D; i++) {
			if (f[i][j] == prev) {
				count++;
				if (count == K)
					break;
			}
			else
				count = 1;
			prev = f[i][j];
		}
		if (count < K)
			return false;
	}
	return true;
}

void inject(int d, int c) {
	if (c > -1)
		memset(f[d], c, sizeof(f[d]));
}

void printFilm() {
	for (int i = 0; i < D; i++) {
		for (int j = 0; j < W; j++) {
			cout << f[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

void dfs(int d, int nInject) {
	if (d == D)
		return;
	if (nInject == result) return;
	for (int i = 0; i < 3; i++) {
		bool tmp[20];
		memcpy(tmp, f[d], sizeof(f[d]));

		int cx = ch[i];

		inject(d, cx); //inject row d with cx (-1 or 0 or 1)
		if (test()) {
			if (cx > -1)
				result = min(nInject + 1, result);
			else
				result = min(nInject, result);
			memcpy(f[d], tmp, sizeof(f[d])); //rollback injected row
			return;
		}

		if (cx > -1) //inject case
			dfs(d + 1, nInject + 1);
		else
			dfs(d + 1, nInject);

		memcpy(f[d], tmp, sizeof(f[d])); //rollback injected row
	}
}

int main()
{
	cin >> T;
	for (int t = 1; t <= T; t++) {
		init();
		input();
		dfs(0, 0);
		cout << "#" << t << " " << result << endl;
	}
}
