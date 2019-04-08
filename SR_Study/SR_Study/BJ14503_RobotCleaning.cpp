/*
	2019.04.08
	https://www.acmicpc.net/problem/14503

*/

#include <iostream>

using namespace std;

int N, M, R, C, D, result;
int map[50][50];
int visit[50][50];
int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };
int dd[] = { 3, 0, 1, 2 }; //왼쪽으로 회전

void input() {
	result = 1;
	cin >> N >> M >> R >> C >> D;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < M; c++) {
			cin >> map[r][c];
		}
	}
}
 
////이렇게 하면 그냥 dfs 탐색이 되어버림.
////즉, 뒤로 롤백할 때 direction이 이전 값으로 돌아가버린다.
//bool clean(int cr, int cc, int d) {
//	//for (int i = 0; i < 4; i++) {
//	int num = 4, i = d;
//	while(num--){
//		int nd = dd[i++];
//		int nr = cr + dr[nd], nc = cc + dc[nd];
//		if (nr < 0 || nr >= N || nc < 0 || nc >= M || map[nr][nc] || visit[nr][nc]) continue;
//		visit[nr][nc] = true;
//		result++;
//		if(clean(nr, nc, nd)) return true;
//		visit[nr][nc] = false;
//		result--;
//		if (i == 4) i = 0;
//	}
//	int br = cr - dr[d], bc = cc - dc[d];
//	if (br < 0 || br >= N || bc < 0 || bc >= M || map[br][bc]) { return true; }
//	else if(clean(br, bc, d)) return true;
//} 

bool clean(int cr, int cc, int d, int t) {
	int nd = dd[d];
	int nr = cr + dr[nd], nc = cc + dc[nd];
	if (nr < 0 || nr >= N || nc < 0 || nc >= M || map[nr][nc] || visit[nr][nc]) { //왼쪽 칸에 갈 수 없는 경우
		if (t == 4) { //이미 네 방향 모두 확인
			int br = cr - dr[d], bc = cc - dc[d];
			if (br < 0 || br >= N || bc < 0 || bc >= M || map[br][bc]) 
				return true; //뒤가 벽이거나 범위 벗어나면 더이상 갈 수 없음
			if(clean(br, bc, d, 0)) return true; //뒤로 후진
		}
		if (clean(cr, cc, nd, t + 1)) return true;
	}
	visit[nr][nc] = true;
	result++;
	if(clean(nr, nc, nd, 0)) return true;
	visit[nr][nc] = false;
	result--;
	return false;
}

int main() {
	freopen("input14503.txt", "r", stdin);
	input();
	visit[R][C] = true;
	//clean(R, C, D);
	
	clean(R, C, D, 0);
	cout << result;
}