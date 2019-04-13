#include <iostream>
#include <cstring>
using namespace std;
struct ATOM { int r, c, d, k; bool alive, crash; };
int T, N, na, nalive, result;
int map[4001][4001];
ATOM a[1001];
int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };
void input() {
	memset(map, 0, sizeof(map));
	na = 1, result = 0;
	cin >> N;
	for(int i = 0; i < N; i++){
		cin >> a[na].c >> a[na].r >> a[na].d >> a[na].k;
		a[na].alive = true, a[na].crash = false;
		a[na].c = 2 * (a[na].c + 1000);
		a[na].r = 2 * -(a[na].r - 1000);
		na++;
	}
	nalive = na;
}
bool move(int i) { //���� ���� ���� ��� true, ������ false
	int cr = a[i].r, cc = a[i].c;
	int nr = cr + dr[a[i].d], nc = cc + dc[a[i].d];
	map[cr][cc] = 0;
	if (nr < 0 || nr >= 4000 || nc < 0 || nc >= 4000) { //���� ��� ����
		a[i].alive = false;
		return true;
	}
	if (map[nr][nc]) { //���� �浹 : �� 2���߱� ������ ���� ���� �̵�, 0.5�� ��� ���ص� ��
		a[i].crash = true, a[map[nr][nc]].crash = true;
		a[i].alive = false;
		a[map[nr][nc]].alive = false;
		return true;
	}
	map[nr][nc] = i;
	a[i].r = nr, a[i].c = nc;
	return false;
}

void sim() {
	while (nalive > 1) { //����ִ� ���� �����ϴ� ����
		//memset(map, 0, sizeof(map));  /* �̰� �ϳ� ������ �ð��ʰ�
		bool rt = false;
		for (int i = 1; i < nalive; i++) { //��� ���� 1ĭ ����
			rt = move(i);
		}
		//if (!rt) continue;
		int aa = 1; ATOM tmp[1001];
		for (int i = 1; i < nalive; i++) { //���� ���� ó��
			map[a[i].r][a[i].c] = 0;
			if (a[i].crash) result += a[i].k;
			if (!a[i].alive) continue;
			tmp[aa++] = a[i];
		}
		nalive = aa;
		memcpy(a, tmp, sizeof(a));
	}	
}
int main() {
	freopen("input5648.txt", "r", stdin);
	cin >> T;
	for (int t = 1; t <= T; t++) {
		input();
		sim();
		cout << "#" << t << " " << result << endl;
	}
}