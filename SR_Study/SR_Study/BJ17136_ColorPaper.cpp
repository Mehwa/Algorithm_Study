/*
	2019.04.07
	https://www.acmicpc.net/problem/17136
	����� ä���� �� ��ġ�� ã��(next_pos(): 1�� ù ����) �ش� ������ i ����� ���� �� �ִ��� �Ǻ��ؼ� IsPossible() �����ϸ� �ִ´�.
	�� ������ �ݺ��ϴٰ� �� ä������ �ּ� �� ���� ����
	
	ó���� i����� ���� �� �ִ� ���� ��ġ�� ã�Ƽ� �ִ� ������� �ߴµ�, ������ 1�� ����� �� ä�����ϹǷ� �̷��� Ž���� ��� ��ȿ�����̴�.
	��, next_pos() �Լ� �ȿ� IsPossible()�� �־ ���� �� ������ ã�� ������ ��, �ش� ������ ����� �־��µ�,
	�׷� ��� �ִ� 4�� for���� ���Ƽ� ã�� �Ǳ� ������ �ſ� ��ȿ�����̴�.
	������ ����� ��� ä�����ϹǷ� 1�� ĭ�� �ִٸ� ������ �ƹ� ������γ� ä��� Ž���ϴ� ���� ����.

	�׸��� ȿ�������� �ٲٴ� �������� ����� �ð��� �� �ɸ� �κ��� block[]�� setMap() ��ġ�� �ٲٸ鼭 if(�� ä������) ���� �ö󰡰� �Ǿ��µ�,
	�׷���� �ѹ� �ϴ� �κ��� if(��ä������)�� true�� ��� ���ϵǱ� ������ ������� �ʾƼ� ���� �����̴�.
	if(���� ����) return�� �� ��, �׻� �ѹ��� ���� �Ǵ����� ��������.
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
	if (remain == 0) { //���� �� ä��� �ּ� �� ����
		result = min(result, used);
		possible = true;
		return;
	}
	if (used >= result) return; //�ּ� ������ ���� ������ �׸�
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