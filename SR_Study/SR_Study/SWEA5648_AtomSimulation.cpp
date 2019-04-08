/*
	2019.04.04
	https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRFInKex8DFAUo&categoryId=AWXRFInKex8DFAUo&categoryType=CODE
	������ �־��� ���� ��ǥ ����̱� ������, ���α׷����� ����ϱ� ���� �ϵ��� ������ �迭�� ������ ��������� �Ѵ�.
	=> �� ��ǥ�� �ִ� ũ�⸸ŭ r �������� ���ְ� c �������� �����༭ ���� �̵���Ű��, r�� ��ȣ�� �������� x�� ��Ī �̵���Ų��.
	(-1, 1)   (1, 1)      ==>        (0, 0)   (2, 0)          ==>        (0, 0)   (2, 0)
	(-1, -1)  (1, -1)  (+1, -1)      (0, -2)  (2, -2)     x�� ��Ī�̵�   (0, 2)   (2, 2)
	*��ǥ�� x,y�� �־����Ƿ� c,r�� �ٲ� �� ����
	���ڵ��� �迭�� �����صΰ�, ������ �ʰ� ���� ���ڰ� �ִ� ���� ��� �ù� ������.
	�ʿ� ���� �ӹ����� �ִ� ������ �������� �������ְ�, ���� ���ڰ� ��ĥ ��� �ش� ���ڵ��� ��������ŭ ����� ������Ű�� ��� �Ͷ߸���.
	���� ����� �׳� �Ͷ߸���.
	ó���� �ʿ� ���ҵ��� ��ǥ�� �����ؼ� �ذ��Ϸ��� �ߴµ�, ��� ��׶��� ���ɰ� Ʋ���� �ᱹ ���� ���ߴ�.
*/
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

struct ATOM {
	int r, c, d, e;
};
	
int T, N, remain, result;
int map[4001][4001];
ATOM atom[1001];

int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };

void input() {
	memset(map, 0, sizeof(map));
	memset(atom, 0, sizeof(atom));
	cin >> N;
	remain = N, result = 0;
	for (int i = 0; i < N; i++) {
		cin >> atom[i].c >> atom[i].r >> atom[i].d >> atom[i].e;
		atom[i].r -= 1000, atom[i].c += 1000;
		atom[i].r *= 2 , atom[i].c *= 2; //0.5�� ����ó�� ���ֱ� ���� �� ����� 2�� �÷��ش�.
		atom[i].r = -(atom[i].r);
		map[atom[i].r][atom[i].c] = atom[i].e;
	}
}

void solve() {
	while (remain > 0) {
		for (int i = 0; i < N; i++) {
			if (atom[i].e == -1) continue; //�̹� ������ ����
			if (map[atom[i].r][atom[i].c] != atom[i].e) { //���� ��ġ�� ������ ���� ������ ������ ���� �ٸ��� -> ������ ������ �׷쿡�� ù�� ° ���� �ߴ� ��
				result += map[atom[i].r][atom[i].c];
				map[atom[i].r][atom[i].c] = 0;
				atom[i].e = -1;
				remain--;
				continue;
			}
			int nr = atom[i].r + dr[atom[i].d], nc = atom[i].c + dc[atom[i].d];
			if (nr < 0 || nr>4000 || nc < 0 || nc>4000) { //���� ���
				atom[i].e = -1;
				remain--;
				continue;
			}
			//�ٸ� ���� ���� 
			if (map[nr][nc] > 0) {
				map[atom[i].r][atom[i].c] = 0;
				map[nr][nc] += atom[i].e;
				remain--;
				atom[i].e = -1;
			}
			else { //�ȸ���
				map[atom[i].r][atom[i].c] -= atom[i].e;
				map[nr][nc] += atom[i].e;
				atom[i].r = nr, atom[i].c = nc;
			}
		}
	}
}

int main() {
	freopen("input5648.txt", "r", stdin);
	cin >> T;
	for (int t = 1; t <= T; t++) {
		input();
		solve();
		cout << "#" << t << " " << result << endl;
	}
}