#include <iostream>
#include <cstring>

using namespace std;

int N;
double p[4]; //pe, pw, ps, pn
bool visited[30][30];
int dx[4] = { 1, -1, 0, 0 }; //E, W, S, N
int dy[4] = { 0, 0, -1, 1 };

void input() {
	cin >> N;
	for (int i = 0; i < 4; i++) {
		int x;
		cin >> x;
		p[i] = x / (double)100;
	}
}

double dfs(int cx, int cy, int depth) {
	if (depth == N) return 1.0;
	visited[cx][cy] = true;
	double result = 0.0;
	for (int i = 0; i < 4; i++) {
		int nx = cx + dx[i];
		int ny = cy + dy[i];
		if (visited[nx][ny]) continue;
		result += p[i] * dfs(nx, ny, depth+1);
	}
	visited[cx][cy] = false;
	return result;
}

int main()
{
	input();
	printf("%.10lf\n", dfs(14, 14, 0));
}