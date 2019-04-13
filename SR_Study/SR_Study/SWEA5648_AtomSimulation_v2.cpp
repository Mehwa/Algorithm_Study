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
bool move(int i) { //죽은 원자 있을 경우 true, 없으면 false
	int cr = a[i].r, cc = a[i].c;
	int nr = cr + dr[a[i].d], nc = cc + dc[a[i].d];
	map[cr][cc] = 0;
	if (nr < 0 || nr >= 4000 || nc < 0 || nc >= 4000) { //범위 벗어나 죽음
		a[i].alive = false;
		return true;
	}
	if (map[nr][nc]) { //원자 충돌 : 맵 2배했기 때문에 같은 방향 이동, 0.5초 고려 안해도 됨
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
	while (nalive > 1) { //살아있는 원자 존재하는 동안
		//memset(map, 0, sizeof(map));  /* 이거 하나 때문에 시간초과
		bool rt = false;
		for (int i = 1; i < nalive; i++) { //모든 원자 1칸 전진
			rt = move(i);
		}
		//if (!rt) continue;
		int aa = 1; ATOM tmp[1001];
		for (int i = 1; i < nalive; i++) { //죽은 원자 처리
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