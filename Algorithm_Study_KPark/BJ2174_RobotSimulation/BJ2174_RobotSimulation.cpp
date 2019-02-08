#include <iostream>
#include <vector>

using namespace std;

#define OK 0
#define WALLCRASH 1
#define ROBOTCRASH 2

int A, B, N, M;
int map[102][102] = { 0 }; //robot location map
vector <pair<int, int> > r; //robot location
int dir[102] = { 0 }; //robot direction
int dx[4] = { 0, 1, 0, -1 }; //N, E, S, W
int dy[4] = { 1, 0, -1, 0 };
typedef struct COMMAND {
	int rid;
	int n;
	char cmd;
};
COMMAND cmdList[102];

void input() {
	cin >> A >> B;
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		int x = 0, y = 0;
		char d;
		cin >> x >> y >> d;
		map[x][y] = i;
		r.push_back(make_pair(x, y));
		if (d == 'N')
			dir[i] = 0;
		else if (d == 'E')
			dir[i] = 1;
		else if (d == 'S')
			dir[i] = 2;
		else //'W'
			dir[i] = 3;
	}
	for (int i = 0; i < M; i++) {
		cin >> cmdList[i].rid >> cmdList[i].cmd >> cmdList[i].n;
	}
}

void rotateLeft(int rid) {
	dir[rid] = dir[rid] - 1;
	if (dir[rid] < 0)
		dir[rid] = 3;
}
void rotateRight(int rid) {
	dir[rid] = (dir[rid] + 1) % 4;
}

int moveForward(int rid) {
	int cx = r[rid - 1].first;
	int cy = r[rid - 1].second;
	int nx = cx + dx[dir[rid]];
	int ny = cy + dy[dir[rid]];
	if (nx < 1 || nx > A || ny < 1 || ny > B) {
		cout << "Robot " << rid << " crashes into the wall" << endl;
		return WALLCRASH;
	}
	else if (map[nx][ny] > 0 ) {
		cout << "Robot " << rid << " crashes into robot " << map[nx][ny] << endl;
		return ROBOTCRASH;
	}
	map[nx][ny] = rid;
	map[cx][cy] = 0;
	r[rid - 1].first = nx;
	r[rid - 1].second = ny;
	return OK;
}

int move(int rid, char cmd) {
	int rt = OK;
	if (cmd == 'L')
		rotateLeft(rid);
	else if (cmd == 'R')
		rotateRight(rid);
	else  // 'F'
		rt = moveForward(rid);
	return rt;
}

int main()
{
	input();
	int rt = OK;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < cmdList[i].n; j++) {
			rt = move(cmdList[i].rid, cmdList[i].cmd);
			if (rt != OK)
				break;
		}
		if (rt != OK)
			break;
	}
	if (rt == OK)
		cout << "OK" << endl;
}