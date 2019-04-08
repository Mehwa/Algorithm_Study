/*
	2019.04.04
	https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRFInKex8DFAUo&categoryId=AWXRFInKex8DFAUo&categoryType=CODE
	문제에 주어진 맵은 좌표 평면이기 때문에, 프로그램에서 사용하기 쉽게 하도록 이차원 배열로 적절히 변형해줘야 한다.
	=> 각 좌표를 최대 크기만큼 r 방향으로 빼주고 c 방향으로 더해줘서 평행 이동시키고, r의 부호를 뒤집에서 x축 대칭 이동시킨다.
	(-1, 1)   (1, 1)      ==>        (0, 0)   (2, 0)          ==>        (0, 0)   (2, 0)
	(-1, -1)  (1, -1)  (+1, -1)      (0, -2)  (2, -2)     x축 대칭이동   (0, 2)   (2, 2)
	*좌표가 x,y로 주어지므로 c,r로 바꿀 때 주의
	원자들을 배열에 저장해두고, 터지지 않고 남은 원자가 있는 동안 계속 시뮬 돌린다.
	맵에 현재 머무르고 있는 원자의 에너지를 저장해주고, 여러 원자가 겹칠 경우 해당 원자들의 에너지만큼 결과를 증가시키고 모두 터뜨린다.
	범위 벗어나면 그냥 터뜨린다.
	처음에 맵에 원소들의 좌표를 저장해서 해결하려고 했는데, 계속 백그라운드 테케가 틀려서 결국 잡지 못했다.
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
		atom[i].r *= 2 , atom[i].c *= 2; //0.5초 예외처리 해주기 위해 맵 사이즈를 2배 늘려준다.
		atom[i].r = -(atom[i].r);
		map[atom[i].r][atom[i].c] = atom[i].e;
	}
}

void solve() {
	while (remain > 0) {
		for (int i = 0; i < N; i++) {
			if (atom[i].e == -1) continue; //이미 터진거 제외
			if (map[atom[i].r][atom[i].c] != atom[i].e) { //현재 위치의 에너지 값과 원자의 에너지 값이 다르다 -> 이전에 터지는 그룹에서 첫번 째 도착 했던 애
				result += map[atom[i].r][atom[i].c];
				map[atom[i].r][atom[i].c] = 0;
				atom[i].e = -1;
				remain--;
				continue;
			}
			int nr = atom[i].r + dr[atom[i].d], nc = atom[i].c + dc[atom[i].d];
			if (nr < 0 || nr>4000 || nc < 0 || nc>4000) { //범위 벗어남
				atom[i].e = -1;
				remain--;
				continue;
			}
			//다른 원자 만남 
			if (map[nr][nc] > 0) {
				map[atom[i].r][atom[i].c] = 0;
				map[nr][nc] += atom[i].e;
				remain--;
				atom[i].e = -1;
			}
			else { //안만남
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