#include <iostream>
#include <vector>

using namespace std;

struct curve {
	int r, c, d, g;
};

int N;
vector<int> dir;
vector<curve> curves;
int map[102][102];

int dr[] = { 0, -1, 0, 1 };
int dc[] = { 1, 0, -1, 0 };

void input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		curve cv;
		cin >> cv.c >> cv.r >> cv.d >> cv.g;
		curves.push_back(cv);
	}
}

void dragonCurve() {
	for (int i = 0; i < curves.size(); i++) {
		dir.clear();
		curve cv = curves[i];
		map[cv.r][cv.c] = 1;
		dir.push_back(cv.d);
		int cr = cv.r + dr[cv.d], cc = cv.c + dc[cv.d];
		map[cr][cc] = 1;
		for (int j = 1; j <= cv.g; j++) {
			for (int k = dir.size() - 1; k >= 0; k--) {
				int nd = (dir[k] + 1) % 4;
 				int nr = cr + dr[nd], nc = cc + dc[nd];
				if (nr < 0 || nr > 100 || nc < 0 || nc > 100) break;
				map[nr][nc] = 1;
				cr = nr, cc = nc;
				dir.push_back(nd);
			}
		}
	}
}

int countCurve() {
	int ct = 0;
	for (int i = 0; i <= 100; i++) {
		for (int j = 0; j <= 100; j++) {
			if (map[i][j] && map[i + 1][j] && map[i][j + 1] && map[i + 1][j + 1]) ct++;
		}
	}
	return ct;
}

int main() {
	freopen("input.txt", "r", stdin);
	input();
	dragonCurve();
	cout << countCurve() << endl;
}