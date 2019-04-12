/*
	2019.04.12
	���� ������ �ε��� �ٸ��� �ߴٰ� �����ɸ�....
*/
#include <iostream>
#include <cstring>
using namespace std;
int N, M, sr, sc, K;
int cmd[1000], map[20][20];
int dice[6] = { 0, 0, 0, 0, 0, 0 };
int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };
int md[4][6] = { {1, 2, 3, 0, 4, 5}, //* �ε��� �򰥸�
{3, 0, 1, 2, 4, 5},
{0, 5, 2, 4, 1, 3},
{0, 4, 2, 5, 3, 1} };

void input() {
	cin >> N >> M >> sr >> sc >> K;
	for (int r = 0; r < N; r++)
		for (int c = 0; c < M; c++)
			cin >> map[r][c];
	for (int i = 0; i < K; i++) {
		cin >> cmd[i];
		if (cmd[i] == 1) cmd[i] = 3; //* �ε��� �򰥸�
		//if (cmd[i] == 2) cmd[i] = 2;
		else if (cmd[i] == 3) cmd[i] = 0;
		else if (cmd[i] == 4) cmd[i] = 1;
	}
}
void move(int sd) {
	int nr = sr + dr[sd], nc = sc + dc[sd];
	if (nr < 0 || nr >= N || nc < 0 || nc >= M) return;
	int tmp[6];
	for (int i = 0; i < 6; i++) //������
		tmp[i] = dice[md[sd][i]];
	memcpy(dice, tmp, sizeof(dice));
	if (map[nr][nc] == 0) { map[nr][nc] = dice[3]; } //ĭ�� ���� //* �ε��� �򰥸�
	else { dice[3] = map[nr][nc]; map[nr][nc] = 0; } //�ֻ��� �ٴڿ� ����, //* �ٴڿ� 0 ����
	sr = nr, sc = nc;
	cout << dice[1] << endl; //��� ���
}
void sim() {
	for (int i = 0; i < K; i++)
		move(cmd[i]);
}
int main() {
	freopen("input14499.txt", "r", stdin);
	input();
	sim();
}