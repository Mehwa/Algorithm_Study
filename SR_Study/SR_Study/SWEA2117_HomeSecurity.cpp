/*
	2019.04.03
	https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5V61LqAf8DFAWu&categoryId=AV5V61LqAf8DFAWu&categoryType=CODE
	�� ��ǥ r, c���� k�� ������Ű�� �ش� ��ǥ�� �߽����� ���� �ȿ� �ִ� �� ���� ���ϰ�, 
	�� �� ������ cost�� ���� ������ �ִ� ���� ������Ų��.
	����ȭ
	1) ���� ��� ���� ���� ���� ���� ������ cost���� ���� k�� �ִ� ���� �̸� ���� �ش� k��ŭ�� ������.
	2) �� ���������κ����� �Ÿ��� ���� �Ÿ� �̻��� �������� ������ (k - 3)
	ó���� if (cost(k) <= nh * M)���� =�� ���� �ٶ��� Ʋ�Ⱦ���.
*/

#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

int T, N, M;
int map[20][20];
int max_area, max_k;
vector<pair<int, int>> home;

int cost(int k) {
	return k * k + (k - 1)*(k - 1);
}

void input() {
	home.clear();
	memset(map, 0, sizeof(map));
	cin >> N >> M;
	max_area = N * N;
	int k = 1;
	while (1) {
		if (cost(k++) > max_area * M) break;
	}
	max_k = k;	
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			cin >> map[r][c];
			if (map[r][c]) home.push_back({ r, c });
		}
	}
}

int dist(int ar, int ac, int br, int bc) {
	return abs(ar - br) + abs(ac - bc);
}

bool valid(int r, int c, int k) {
	if (dist(0, 0, r, c) < k - 3) return false;
	if (dist(N - 1, 0, r, c) < k - 3) return false;
	if (dist(0, N - 1, r, c) < k - 3) return false;
	if (dist(N - 1, N - 1, r, c) < k - 3) return false;
	return true;
}

int countHome(int r, int c, int k) {
	int cnt = 0;
	for (int i = 0; i < home.size(); i++) {
		if (dist(home[i].first, home[i].second, r, c) <= k - 1) cnt++;
	}
	return cnt;
}

int solve() {
	int result = 0;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			for (int k = 1; k <= max_k; k++) {
 				if (!valid(r, c, k)) continue; 
				int nh = countHome(r, c, k);
				if (cost(k) <= nh * M) {
					result = max(result, nh);
				}
			} 
		}
	}
	return result;
}

int main() {
	freopen("input2117.txt", "r", stdin);
	cin >> T;
	for (int t = 1; t <= T; t++) {
		input();
		cout << "#" << t << " " << solve() << endl;
	}
}