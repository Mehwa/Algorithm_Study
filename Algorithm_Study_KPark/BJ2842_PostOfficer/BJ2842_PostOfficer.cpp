#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int N, px, py;
int minH = 987654321, maxH = 0;
int housemap[52][52] = { false };
int hmap[52][52] = { 0 };
int cost[52][52] = { -1 };
bool visited[52][52] = { false };
int dx[8] = { 1, -1, 0, 0 , 1, 1, -1, -1}; //R, L, U, D, RU, RD, LD, LU
int dy[8] = { 0, 0, -1, 1, -1, 1, 1, -1};
vector<pair<int, int> > house;

void input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		char line[52];
		cin >> line;
		for (int j = 0; j < N; j++) {
			if (line[j] == 'P') {
				px = i + 1;
				py = j + 1;
			}
			else if (line[j] == 'K') {
				house.push_back(make_pair(i + 1, j + 1));
				housemap[i + 1][j + 1] = true;
			}
		}
	}
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			int h;
			cin >> h;
			hmap[i][j] = h;
		}
	}
}

void printInput() {
	cout << "px:" << px << " py:" << py << endl;
	for (int i = 0; i < house.size(); i++)
		cout << house[i].first << " " << house[i].second << endl;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << hmap[i][j];
		}
		cout << endl;
	}
}

void initMinMax() {
	for (int i = 0; i < house.size(); i++) {
		int h = hmap[house[i].first][house[i].second];
		if (h < minH)
			minH = h;
		if (h > maxH)
			maxH = h;
	}
}

void initCost() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (hmap[i][j] < minH)
				cost[i][j] = minH - hmap[i][j];
			else if (hmap[i][j] > maxH)
				cost[i][j] = hmap[i][j] - maxH;
			else
				cost[i][j] = 0;
		}
	}
}

bool comp(pair<int, int> a, pair<int, int> b) {
	return (cost[a.first][a.second] < cost[b.first][b.second]);
}

int visitHouse() {
	int visitedHouse = 0;
	int maxCost = 0;
	queue<pair<int, int> > q;
	q.push(make_pair(px, py));
	visited[px][py] = true;
	while (!q.empty()) {
		pair<int, int> cur = q.front();
		q.pop();
		if (housemap[cur.first][cur.second]) {
			visitedHouse++;
			if (cost[cur.first][cur.second] > maxCost)
				maxCost = cost[cur.first][cur.second];
			if (visitedHouse == house.size())
				break;
		}
		vector<pair<int, int> > d;
		for (int i = 0; i < 8; i++) {
			int nx = cur.first + dx[i];
			int ny = cur.second + dy[i];
			if (0 < nx && nx <= N && 0 < ny && ny <= N && !visited[nx][ny])
				d.push_back(make_pair(nx, ny));
		}
		sort(d.begin(), d.end(), comp);
		for (int i = 0; i < d.size(); i++) {
			q.push(make_pair(d[i].first, d[i].second));
			visited[d[i].first][d[i].second] = true;
			if (cost[cur.first][cur.second] > cost[d[i].first][d[i].second])
				cost[d[i].first][d[i].second] = cost[cur.first][cur.second];
		}
	}
	return maxCost;
}

int main()
{
	input();
	//printInput();
	initMinMax();
	initCost();
	int c = visitHouse();
	cout << maxH - minH + c;
}