#include <iostream>
using namespace std;

int N, K;
int A[10][10];
int in[3][20], w[3], id[3]; //id: 몇 번째를 낼지

//0:지우, 1:경희, 2:민호
void input() {
	cin >> N >> K;
	id[0] = 0, id[1] = 0, id[2] = 0;
	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			cin >> A[r][c];
		}
	}
	for (int i = 0; i < 20; i++)
		cin >> in[1][i];
	for (int i = 0; i < 20; i++)
		cin >> in[2][i];
}
bool exist(int n) {
	for (int i = 0; i < id[0]; i++) {
		if (in[0][i] == n) return true;
	}
	return false;
}
bool dfs(int d, int win, int ch) {
	if (w[1] == K || w[2] == K) return false;
	if (w[0] == K) return true;
	if (win == 0 || ch == 0) { //지우 참가
		int p = (win == 0 ? ch : win);
		for (int i = 1; i <= N; i++) {
			if (exist(i)) continue;
			if (A[i][in[p][id[p]]] == 2) { win = 0; ch = (p == 1 ? 2 : 1); } //지우 승
			else { win = p, ch = (p == 1 ? 2 : 1); } //지우 패
			in[0][id[0]] = i, id[0]++, id[p]++, w[win]++;
			if (dfs(d + 1, win, ch)) return true;
			w[win]--, id[0]--, id[p]--, in[0][id[0]] = 0;
		}
	}
	else { // 지우 참가 안함
		if (A[in[1][id[1]]][in[2][id[2]]] == 2) win = 1;
		else win = 2;
		id[1]++, id[2]++, w[win]++;
		if(dfs(d + 1, win, 0)) return true;
		w[win]--, id[1]--, id[2]--;
	}
	return false;
 }

int main() {
	freopen("input16986.txt", "r", stdin);
	input();
	if (dfs(0, 0, 1)) cout << 1;
	else cout << 0;
}