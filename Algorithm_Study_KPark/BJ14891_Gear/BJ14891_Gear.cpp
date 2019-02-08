#include <iostream>
#include <vector>

using namespace std;

int k;
int c[4][8];
bool cr[4] = { false };
vector<pair<int, int> > r;

void input() {
	for (int i = 0; i < 4; i++) {
		char line[9];
		cin >> line;
		for (int j = 0; j < 8; j++)
			c[i][j] = line[j] - '0';
	}
	cin >> k;
	for (int i = 0; i < k; i++) {
		int n = 0, d = 0;
		cin >> n >> d;
		r.push_back(make_pair(n-1, d));
	}
}

void printInput() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 8; j++) {
			cout << c[i][j];
		}
		cout << endl;
	}
	cout << endl;
	/*cout << k << endl;
	for (int i = 0; i < k; i++) {
		cout << r[i].first << " " << r[i].second << endl;
	}*/
}

void rotateCircle(int n, int d) {
	int prev = 0, cur = 0;
	if (d == 1) {
		prev = c[n][7];
		for (int i = 0; i < 8; i++) {
			cur = c[n][i];
			c[n][i] = prev;
			prev = cur;
		}
	}
	else {
		prev = c[n][0];
		for (int i = 7; i > -1; i--) {
			cur = c[n][i];
			c[n][i] = prev;
			prev = cur;
		}
	}
}

void rotateAll(int n, int d) {
	int lc = n - 1;
	int rc = n + 1;
	cr[n] = true;
	if (lc > -1 && c[lc][2] != c[n][6] && !cr[lc])
		rotateAll(lc, -d);
	if (rc < 4 && c[rc][6] != c[n][2] && !cr[rc])
		rotateAll(rc, -d);
	rotateCircle(n, d);
}

int score() {
	return (c[0][0] + c[1][0] * 2 + c[2][0] * 4 + c[3][0] * 8);
}

int main()
{
	input();
	//printInput();

	for (int i = 0; i < k; i++) {
		for (int j = 0; j < 4; j++)
			cr[j] = false;
		rotateAll(r[i].first, r[i].second);
		//printInput();
	}
	cout << score() << endl;
}