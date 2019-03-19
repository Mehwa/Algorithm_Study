#include <iostream>
#include <deque>

using namespace std;

int N, K;
int map[10][10];
deque<int> a[3]; //0:jw, 1:kh, 2:mh
int win[3]; //0:jw, 1:kh, 2:mh
int visit[10];

void input() {
	cin >> N >> K;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			cin >> map[i][j];
	int x;
	for (int i = 0; i < 20; i++) {
		cin >> x;
		a[1].push_back(x);
	}
		
	for (int i = 0; i < 20; i++) {
		cin >> x;
		a[2].push_back(x);
	}
		
}

pair<int, int> next_xy(int l) {
	if (l == 1) return { 0, 2 };
	if (l == 2) return { 0, 1 };
	if (l == 0) return { 1, 2 };
}

int dfs(int d, int l) { //start from 0, 0, 2
	if (win[0] == K) return 1;
	if (win[1] == K || win[2] == K) return 0;
	if (l != 0) {
		for (int i = 1; i <= N; i++) {
			if (!visit[i]) {
				pair<int, int> nxy = next_xy(l);
				int nx = i, ny = a[nxy.second].front();
				a[nxy.second].pop_front();
				if (map[nx][ny] == 2) { //nx(0:jw) win
					win[nxy.first]++;
					visit[i] = true;
					if (dfs(d + 1, nxy.second)) return 1;
					visit[i] = false;
					win[nxy.first]--;
				}
				else { //nx(0:jw) lose
					win[nxy.second]++;
					visit[i] = true;
					if (dfs(d + 1, nxy.first)) return 1;
					visit[i] = false;
					win[nxy.second]--;
				}
				a[nxy.second].push_front(ny);
			}
		}
	}
	else {
		int nx = a[1].front(), ny = a[2].front();
		a[1].pop_front(), a[2].pop_front();
		if (map[nx][ny] == 2) { //1 win
			win[1]++;
			if (dfs(d + 1, 2)) return 1;
			win[1]--;
		}
		else { //2 win
			win[2]++;
			if (dfs(d + 1, 1)) return 1;
			win[2]--;
		}
		a[1].push_front(nx), a[2].push_front(ny);
	}
	return 0;
}

int main() {
	freopen("input.txt", "r", stdin);
	input();
	cout << dfs(0, 2) << endl;
}
