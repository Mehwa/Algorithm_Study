/*
	2019.04.07
	https://www.acmicpc.net/problem/17136
	블록을 채워야 할 위치를 찾고(next_pos(): 1인 첫 지점) 해당 지점에 i 블록을 넣을 수 있는지 판별해서 IsPossible() 가능하면 넣는다.
	이 과정을 반복하다가 다 채워지면 최소 블럭 개수 갱신
	
	처음에 i블록을 넣을 수 있는 최초 위치를 찾아서 넣는 방식으로 했는데, 어차피 1인 블록은 다 채워야하므로 이렇게 탐색할 경우 비효율적이다.
	즉, next_pos() 함수 안에 IsPossible()를 넣어서 가능 한 지점을 찾아 리턴한 후, 해당 지점에 블록을 넣었는데,
	그럴 경우 최대 4중 for문을 돌아서 찾게 되기 때문에 매우 비효율적이다.
	어차피 블록을 모두 채워야하므로 1인 칸이 있다면 가능한 아무 블록으로나 채우고 탐색하는 것이 낫다.

	그리고 효율적으로 바꾸는 과정에서 디버깅 시간이 좀 걸린 부분이 block[]과 setMap() 위치를 바꾸면서 if(다 채웠으면) 위로 올라가게 되었는데,
	그럴경우 롤백 하는 부분이 if(다채웠으면)이 true일 경우 리턴되기 때문에 실행되지 않아서 생긴 오류이다.
	if(조건 만족) return을 할 때, 항상 롤백이 실행 되는지를 주의하자.
*/

#include <iostream>
#include <algorithm>

using namespace std;

int map[10][10];
int block[6] = {0, 5, 5, 5, 5, 5 };
int result = 30;
int total = 0;
bool possible = false;

void input() {
	for (int r = 0; r < 10; r++) {
		for (int c = 0; c < 10; c++) {
			cin >> map[r][c];
			if (map[r][c]) total++;
		}
	}
}

bool IsPossible(int sr, int sc, int i) {
	for (int r = sr; r < sr + i; r++) {
		for (int c = sc; c < sc + i; c++) {
			if (r < 0 || r >= 10 || c < 0 || c >= 10) return false;
			if (!map[r][c]) return false;
		}
	}
	return true;
}

 pair<int, int> next_pos(int sr, int i) {
	for (int r = sr; r < 10; r++) {
		for (int c = 0; c < 10; c++) {
			if (map[r][c]) return{ r, c };
		}
	}
	return {-1, -1};
}

void setMap(int sr, int sc, int b, int val) {
	for (int r = sr; r < sr + b; r++) {
		for (int c = sc; c < sc + b; c++) {
			map[r][c] = val;
		}
	}
}

void dfs(int cr, int cc, int used, int remain) {
	if (remain == 0) { //면적 다 채우면 최소 값 갱신
		result = min(result, used);
		possible = true;
		return;
	}
	if (used >= result) return; //최소 값보다 많이 썼으면 그만
	for (int i = 1; i <= 5; i++) {
		if (!IsPossible(cr, cc, i)) continue;
		if (remain < i * i) continue;
		if (block[i] == 0) continue;
		setMap(cr, cc, i, 0);
		block[i]--;
		auto rt = next_pos(cr, i);
		dfs(rt.first, rt.second, used + 1, remain - i * i);
		block[i]++;
		setMap(cr, cc, i, 1);
	}
}

int main() {
	freopen("input17136.txt", "r", stdin);
	input();
	if (total == 0) cout << 0 << endl;
	else if (total == 100) cout << 4 << endl;
	else {
		auto rt = next_pos(0, 0);
		dfs(rt.first, rt.second, 0, total);
		if (possible == false) cout << -1 << endl;
		else cout << result << endl;
	}
}