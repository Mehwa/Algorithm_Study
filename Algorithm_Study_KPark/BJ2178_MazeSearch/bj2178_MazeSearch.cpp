#include <iostream>
#include <queue>

#define START_X 1
#define START_Y 1
#define NUM_OF_DIRECTION 4

using namespace std;

int N, M;
bool map[102][102] = { false };
bool visited[102][102] = { false };

//Right, Left, Up, Down
int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

void input() {
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		char line[101];
		cin >> line;
		for (int j = 1; j <= M; j++) {
			if (line[j - 1] - '0')
				map[i][j] = true;
		}
	}
}

void printInput() {
	for (int i = 0; i <= N + 1; i++) {
		for (int j = 0; j <= M + 1; j++) {
			cout << map[i][j];
		}
		cout << endl;
	}
}

int searchMazeBFS() {
	int nStep = 0;
	int nPrev_token = 0, nNext_token = 0;
	queue< pair<int, int> > q;
	q.push(make_pair(START_X, START_Y)); //start node
	visited[START_X][START_Y] = true;
	nPrev_token++;
	while (!q.empty()) {
		pair<int, int> cur = q.front();
		q.pop();
		nPrev_token--;
		//cout<<"Prev:"<<nPrev_token<< " Next:" << nNext_token<<" ("<<cur.first<<","<<cur.second<<")"<<endl;

		if ((cur.first == N) && (cur.second == M)) {
			nStep++;
			break;
		}
		for (int i = 0; i < NUM_OF_DIRECTION; i++) {
			int next_x = cur.first + dx[i];
			int next_y = cur.second + dy[i];
			if (map[next_x][next_y] && !visited[next_x][next_y]) {
				q.push(make_pair(next_x, next_y));
				visited[next_x][next_y] = true;
				nNext_token++;
			}
		}
		if (nPrev_token == 0) {
			nPrev_token = nNext_token;
			nNext_token = 0;
			nStep++;
			//cout<<"Step:"<<nStep<<" ("<<cur.first<<","<<cur.second<<")"<<endl;
		}
	}
	return nStep;
}

int main() {
	input();
	//printInput();
	cout << searchMazeBFS();
	system("pause");
}