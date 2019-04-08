/*
	2019.04.08
	

*/

#include <iostream>
#include <algorithm>

using namespace std;

struct P {
	int r, c, dist, s;
};
struct S {
	int r, c, ppn, k;
	P pp[10];
};
bool comp(P p1, P p2) {
	return p1.dist < p2.dist;
}
int T, N;
int map[10][10];
P pp[10];
S ss[2];
int ppn, ssn, result;

void input() {
	result = 987654321;
	ppn = 0, ssn = 0;
	cin >> N;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			cin >> map[r][c];
			if (map[r][c] == 1) { //���
				pp[ppn].r = r, pp[ppn].c = c;
				ppn++; //�����
			}
			else if (map[r][c] > 0) { // ���
				ss[ssn].r = r, ss[ssn].c = c, ss[ssn].k = map[r][c];
				ssn++;
			}
		}
	}
}

int sim(S s) {
	//�Ÿ� ª�� ������ sort
	sort(s.pp, s.pp + s.ppn, comp);
	for (int i = 0; i < s.ppn; i++) {
		if (i == 0 || i == 1 || i == 2) s.pp[i].dist += s.k;
		else {
			int prev_time = s.pp[i - 3].dist;
			if (prev_time < s.pp[i].dist) { //�տ� ģ�� ������ ����������
				s.pp[i].dist += s.k;
			}
			else { //�� ģ�� ������ ���� �����ؼ� ����ϸ�
				s.pp[i].dist = prev_time + s.k;
			}
		}
	}
	return s.pp[s.ppn - 1].dist; //�������� ���� ģ��
}

void dfs(int d) {
	if (d == ppn) {
		int s0 = sim(ss[0]);
		int s1 = sim(ss[1]);
		result = min(result, max(s0, s1));
		return;
	}
	for (int i = 0; i < 2; i++) {
		pp[d].dist = abs(pp[d].r - ss[i].r) + abs(pp[d].c - ss[i].c) + 1;
		pp[d].s = i;
		ss[i].pp[ss[i].ppn++] = pp[d];
		dfs(d + 1);
		ss[i].ppn--;
	}
}

int main() {
	freopen("input2383.txt", "r", stdin);
	cin >> T;
	for (int t = 1; t <= T; t++) {
		input();
		dfs(0);
		cout << "#" << t << " " << result << "\n";
	}
}