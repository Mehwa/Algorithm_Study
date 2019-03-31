/*
 * Author: kpark
 * Date: 2019.03.28
 * Algorithm: DFS
 * Problem: https://www.acmicpc.net/problem/15686
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int N, M;
int map[50][50];
vector<pair<int, int>> c;
vector<pair<int, int>> h;
int result;

void input() {
	result = 987654321;
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			if (map[i][j] == 1) h.push_back({ i, j });
			if (map[i][j] == 2) c.push_back({ i, j });
		}
	}
}

int dist() {
	int d = 0;
	for (int i = 0; i < h.size(); i++) {
		int hd = 987654321;
		for (int j = 0; j < c.size(); j++) {
			if(map[c[j].first][c[j].second] == 2)
				hd = min(hd, abs(h[i].first - c[j].first) + abs(h[i].second - c[j].second));
		}
		d += hd;
	}
	return d;
}

void chooseDFS(int d, int cc) {
	if (d == (c.size() - M)) { //# of closing stores
		result = min(result, dist());
		return;
	}
	for (int i = cc; i < c.size(); i++) {
		map[c[i].first][c[i].second] = 0; //close
		chooseDFS(d + 1, i + 1);
		map[c[i].first][c[i].second] = 2;
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	input();
	chooseDFS(0, 0);
	dist();
	cout << result << endl;
}