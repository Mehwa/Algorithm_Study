#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

typedef struct CELL {
	int life; //-1:dead
	int time;
	bool state; //0:disabled 1:enabled
	bool bNew;
};

int T, N, M, K;
CELL map[350][350];

struct compare
{
	bool operator()(const pair<int, int> & a, const pair<int, int> & b)
	{
		return map[a.first][a.second].life < map[b.first][b.second].life;
	}
};

//queue<pair<int, int>> q;
//queue<pair<int, int>> nq;
priority_queue <pair<int, int>, vector<pair<int, int>>, compare> pq;
priority_queue <pair<int, int>, vector<pair<int, int>>, compare> npq;

int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

void init() {
	//queue<pair<int, int>> emptyq;
	//swap(q, emptyq); //init queue
	priority_queue <pair<int, int>, vector<pair<int, int>>, compare> emptypq;
	swap(pq, emptypq); //init queue
	memset(map, 0, sizeof(map));
}

void input() {
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			int x;
			cin >> x;
			if (x > 0) {
				map[149 + i][149 + j].life = x;
				//q.push(make_pair(149 + i, 149 + j));
				pq.push(make_pair(149 + i, 149 + j));
			}
		}
	}
}

//void updateCells() {
//	queue<pair<int, int>> emptyq;
//	swap(nq, emptyq); //init queue
//	while (!q.empty()) {
//		pair<int, int> cur = q.front();
//		q.pop();
//		int i = cur.first;
//		int j = cur.second;
//		map[i][j].time++;
//		if (!map[i][j].state) { //disabled cell
//			if (map[i][j].time == map[i][j].life) {
//				map[i][j].state = true;
//				map[i][j].time = 0;
//			}
//		}
//		else { //enabled cell
//			if (map[i][j].time == 1) { //Spread()
//				for (int d = 0; d < 4; d++) {
//					int nx = i + dx[d];
//					int ny = j + dy[d];
//					if (map[nx][ny].life == 0) { //cel doesnt exists
//						map[nx][ny].bNew = true;
//						map[nx][ny].life = map[i][j].life;
//						nq.push(make_pair(nx, ny));
//					}
//					else if (map[nx][ny].life > 0) { //alive cell exists
//						if (map[nx][ny].bNew == true) {
//							map[nx][ny].life = max(map[nx][ny].life, map[i][j].life);
//						}
//					}
//				}
//			}
//			if (map[i][j].time == map[i][j].life) { //dead
//				map[i][j].life = -1;
//				continue;
//			}
//		}
//		nq.push(make_pair(i, j));
//	}
//	q = nq;
//	while (!q.empty()) {
//		map[q.front().first][q.front().second].bNew = false;
//		q.pop();
//	}
//}

void updateCellsPQ() {
	priority_queue <pair<int, int>, vector<pair<int, int>>, compare> emptypq;
	swap(npq, emptypq); //init queue
	while (!pq.empty()) {
		pair<int, int> cur = pq.top();
		pq.pop();
		int i = cur.first;
		int j = cur.second;
		map[i][j].time++;
		if (!map[i][j].state) { //disabled cell
			if (map[i][j].time == map[i][j].life) {
				map[i][j].state = true;
				map[i][j].time = 0;
			}
		}
		else { //enabled cell
			if (map[i][j].time == 1) { //Spread()
				for (int d = 0; d < 4; d++) {
					int nx = i + dx[d];
					int ny = j + dy[d];
					if (map[nx][ny].life == 0) { //cel doesnt exists
						map[nx][ny].life = map[i][j].life;
						npq.push(make_pair(nx, ny));
					}
				}
			}
			if (map[i][j].time == map[i][j].life) { //dead
				map[i][j].life = -1;
				continue;
			}
		}
		npq.push(make_pair(i, j));
	}
}

void simulatation() {
	for (int k = 1; k <= K; k++) {
		//updateCells();
		//q = nq;
		updateCellsPQ();
		pq = npq;
	}
}

int main()
{
	freopen("input.txt", "r", stdin);
	cin >> T;
	for (int t = 1; t <= T; t++) {
		init();
		input();
		simulatation();
		//cout << "#" << t << " " << nq.size() << endl;
		cout << "#" << t << " " << npq.size() << endl;
	}
}