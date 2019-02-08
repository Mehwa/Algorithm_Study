#include <iostream>
#include <queue>

using namespace std;

int N, M, a1x, a1y, a2x, a2y, b1x, b1y, b2x, b2y;
bool map[101][101] = { true };
bool visited[101][101] = { false };
int dist[101][101] = { 0 };
int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

void input() {
	cin >> N >> M;
	cin >> a1x >> a1y;
	cin >> a2x >> a2y;
	cin >> b1x >> b1y;
	cin >> b2x >> b2y;
	for (int i = 0; i <= N; i++) {
		for (int j = 0; j <= M; j++) {
			map[i][j] = true;
		}
	}
	map[a1x][a1y] = false;
	map[a2x][a2y] = false;
	map[b1x][b1y] = false;
	map[b2x][b2y] = false;
}

void printInput() {
	/*cout << N << " " << M << endl;
	cout << a1x << " " << a1y << endl;
	cout << a2x << " " << a2y << endl;
	cout << b1x << " " << b1y << endl;
	cout << b2x << " " << b2y << endl;*/
	
	for (int j = 0; j <= M; j++) {
		for (int i = 0; i <= N; i++) {
			cout << map[i][j];
		}
		cout << endl;
	}
	for (int j = 0; j <= M; j++) {
		for (int i = 0; i <= N; i++) {
			cout << dist[i][j];
		}
		cout << endl;
	}
}

void init() {
	for (int i = 0; i <= N; i++) {
		for (int j = 0; j <= M; j++) {
			visited[i][j] = false;
			dist[i][j] = 0;
		}
	}
}

void initAll() {
	for (int i = 0; i <= N; i++) {
		for (int j = 0; j <= M; j++) {
			map[i][j] = true;
			visited[i][j] = false;
			dist[i][j] = 0;
		}
	}
	map[a1x][a1y] = false;
	map[a2x][a2y] = false;
	map[b1x][b1y] = false;
	map[b2x][b2y] = false;
}

int connectLineBFS(int startx, int starty, int endx, int endy) {
	queue<pair<int, int> > q;
	q.push(make_pair(startx, starty));
	visited[startx][starty] = true;
	while (!q.empty()) {
		pair<int, int> cur = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int nx = cur.first + dx[i];
			int ny = cur.second + dy[i];
			if (nx == endx && ny == endy) { //destination
				dist[nx][ny] = dist[cur.first][cur.second] + 1;
				return dist[nx][ny];
			}
			if (map[nx][ny] && !visited[nx][ny] && 0 <= nx && nx <= N && 0 <= ny && ny <= M) {
				q.push(make_pair(nx, ny));
				visited[nx][ny] = true;
				dist[nx][ny] = dist[cur.first][cur.second] + 1;
			}
		}
	}
	return -1; //impossible
}

//backtrack min dist line
void updateMap(int startx, int starty, int endx, int endy, int distance) {
	int curx = endx;
	int cury = endy;
	while (distance > 1) {
		for (int i = 0; i < 4; i++) {
			int nx = curx + dx[i];
			int ny = cury + dy[i];
			if (map[nx][ny] && dist[nx][ny] == distance - 1 && 0 <= nx && nx <= N && 0 <= ny && ny <= M) {
				map[nx][ny] = false; //mark the way
				distance--;
				curx = nx;
				cury = ny;
				break;
			}
		}
	}
}

int main()
{
	int dist1 = 0, dist2 = 0, dist3 = 0, dist4 = 0, sum1 = 0, sum2 = 0;
	input();
	
	//connect A, B
	dist1 = connectLineBFS(a1x, a1y, a2x, a2y);
	updateMap(a1x, a1y, a2x, a2y, dist1);
	init();
	dist2 = connectLineBFS(b1x, b1y, b2x, b2y);

	if(0 < dist1 && 0 < dist2) //sum1 possible
		sum1 = dist1 + dist2;

	initAll();

	//connect B, A
	dist3 = connectLineBFS(b1x, b1y, b2x, b2y);
	updateMap(b1x, b1y, b2x, b2y, dist3);
	init();
	dist4 = connectLineBFS(a1x, a1y, a2x, a2y);

	if(0 < dist3 && 0 < dist4) //sum2 possible
		sum2 = dist3 + dist4;

	if (sum1==0 && sum2==0) { //if both sum1 and sum2 impossible
		cout << "IMPOSSIBLE" << endl;
	}
	else {
		if (sum2 == 0) //if sum2 impossible
			cout << sum1 << endl;
		else if (sum1 == 0) //if sum1 impossible
			cout << sum2 << endl;
		else //if both sum1 and sum2 possible
			cout << min(sum1, sum2) << endl;
	}
}
