#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int N;
bool map[27][27] = { false };
bool visited[27][27] = { false };

int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

void input() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		char line[25];
		cin >> line;
		for (int j = 1; j <= N; j++) {
			if (line[j - 1] - '0')
				map[i][j] = true;
		}
	}
}

void printInput() {
	cout << "N:" << N << endl;
	for (int i = 0; i <= N + 1; i++) {
		for (int j = 0; j <= N + 1; j++) {
			cout << map[i][j];
		}
		cout << endl;
	}
}

int houseGroupingBFS(int start_x, int start_y){
	int nHouse = 0;
	queue <pair <int, int> > q;
	q.push(make_pair(start_x, start_y));
	visited[start_x][start_y] = true;
	while (!q.empty()) {
		pair<int, int> cur = q.front();
		q.pop();
		nHouse++;
		for (int i = 0; i < 4; i++) {
			int next_x = cur.first + dx[i];
			int next_y = cur.second + dy[i];
			if (map[next_x][next_y] && !visited[next_x][next_y]) {
				q.push(make_pair(next_x, next_y));
				visited[next_x][next_y] = true;
			}
		}
	}
	return nHouse;
}

void houseGrouping() {
	int nGroup = 0;
	vector<int> vHouseList;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (map[i][j] && !visited[i][j]) {
				int nHouse = houseGroupingBFS(i, j);
				nGroup++;
				vHouseList.push_back(nHouse);
			}
		}
	}
	sort(vHouseList.begin(), vHouseList.end());
	cout << nGroup << endl;
	for (int i = 0; i < vHouseList.size(); i++) {
		cout << vHouseList[i] << endl;
	}
}

int main() {
	input();
	//printInput();
	houseGrouping();
	system("pause");
}