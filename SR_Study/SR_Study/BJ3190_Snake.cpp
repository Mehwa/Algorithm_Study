/*
	2019.04.11

*/
#include <iostream>
using namespace std;

struct POS {
	int r, c;
};
struct CMD {
	int t, d; //time, direction
};
POS snake[200];
CMD m[101];
int N, K, L, h, t, cd, prev_t;
int map[102][102];
int dr[] = { -1, 0, 1, 0 }; //�� �� �� ��
int dc[] = { 0, 1, 0, -1 };
int	ld[] = { 3, 0, 1, 2 }; //���� ȸ��
int rd[] = { 1, 2, 3, 0 }; //������ ȸ��

void input() {
	h = 0, t = 0, cd = 1, prev_t = 0;
	snake[0].r = 1, snake[0].c = 1, map[1][1] = 1;
	cin >> N >> K;
	for (int i = 0; i < K; i++) { //���
		int r, c;
		cin >> r >> c;
		map[r][c] = 2;
	}
	cin >> L;
	for (int i = 0; i < L; i++) { //���
		int t; char d;
		cin >> t >> d;
		m[i].t = t - prev_t, m[i].d = (d == 'L' ? -1 : 1); //���� L�̸� -1 D�� 1
		prev_t = t;
	}
	for (int r = 0; r <= N + 1; r++) {
		for (int c = 0; c <= N + 1; c++) {
			if (r == 0 || c == 0 || r == N + 1 || c == N + 1) map[r][c] = 1;
		}
	}
}

int sim() {
	int time = 0;
	m[L].t = -1; //�������� ��� ���ƶ�
	for (int i = 0; i <= L; i++) {
		CMD cmd = m[i];
		while (cmd.t--) {
			int nr = snake[h].r + dr[cd], nc = snake[h].c + dc[cd];
			if (map[nr][nc] == 1) return time + 1; //���� ����
			//�Ӹ� ������
			//h++;
			h = (h + 1) % 200;
			snake[h].r = nr, snake[h].c = nc;
			if (map[nr][nc] != 2) { //����ƴϸ� ���� ������
				map[snake[t].r][snake[t].c] = 0;
				//t++;
				t = (t + 1) % 200;
			}
			map[nr][nc] = 1;			
			time++;
		}
		//cmd.d �������� ȸ��
		if (cmd.d == -1) cd = ld[cd];
		else cd = rd[cd];
	}
}

int main() {
	freopen("input3190.txt", "r", stdin);
	input();
	cout << sim();
}