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
int dd[] = { 3, 0, 1, 2 }; //�������� ȸ��

void input() {
	result = 1;
	cin >> N >> M >> R >> C >> D;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < M; c++) {
			cin >> map[r][c];
		}
	}
}
 
////�̷��� �ϸ� �׳� dfs Ž���� �Ǿ����.
////��, �ڷ� �ѹ��� �� direction�� ���� ������ ���ư�������.
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
	if (nr < 0 || nr >= N || nc < 0 || nc >= M || map[nr][nc] || visit[nr][nc]) { //���� ĭ�� �� �� ���� ���
		if (t == 4) { //�̹� �� ���� ��� Ȯ��
			int br = cr - dr[d], bc = cc - dc[d];
			if (br < 0 || br >= N || bc < 0 || bc >= M || map[br][bc]) 
				return true; //�ڰ� ���̰ų� ���� ����� ���̻� �� �� ����
			if(clean(br, bc, d, 0)) return true; //�ڷ� ����
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