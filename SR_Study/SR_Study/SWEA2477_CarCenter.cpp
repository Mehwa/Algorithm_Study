/*
	2019.04.03
	https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV6c6bgaIuoDFAXy&categoryId=AV6c6bgaIuoDFAXy&categoryType=CODE
	1) ������ ���� ������� �����뿡�� ����. => ���� ��� ť�� �ִ´�.
	2) �� �����뿡 ��� �ο��� ���Խ�Ų��.
	3) ���� ���� ������� ����뿡�� ����.
	4) �� ����뿡 ��� �ο��� ���Խ�Ų��.
	����ü�� �����ϰ� �����ؼ� ������ �������.
	ó���� ������ �߸������ؼ� �ο����� �ô�.
	B�� ���� �� ť�� ��� �ִ� ��� ���Ҹ� �־�� �ϴµ�, �ϳ��� �־ Ʋ�Ⱦ���.
	�ùķ��̼� ������ �Ǽ��� �����ؾ� �ϰ�, �����ؼ� ���ܰ� ������ �� �����ؾ� ��.
*/
#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

struct DESK {
	int lat, f, pid; //latency, finish_time, person id
};
struct P {
	int id, t, rec, rep;
};

int T, N, M, K, A, B;
int people;
DESK aa[10];
DESK bb[10];
P pp[1001];
queue<int> bq;

void input() {
	people = 0;
	memset(aa, 0, sizeof(aa));
	memset(bb, 0, sizeof(bb));
	memset(pp, 0, sizeof(pp));
	queue<int>().swap(bq);
	cin >> N >> M >> K >> A >> B;
	for (int i = 1; i <= N; i++) {
		cin >> aa[i].lat;
	}
	for (int i = 1; i <= M; i++) {
		cin >> bb[i].lat;
	}
	for (int i = 1; i <= K; i++) {
		cin >> pp[i].t;
		pp[i].id = i;
		pp[i].rec = 0;
		pp[i].rep = 0;
	}
}

void insertA(int time) {
	for (int i = 1; i <= K; i++) {
		if (pp[i].rec > 0) continue;
		if (pp[i].t <= time) { // ���� �ð� ������
			P cp = pp[i];
			for (int i = 1; i <= N; i++) {
				if (aa[i].pid == 0) {
					aa[i].pid = cp.id;
					aa[i].f = time + aa[i].lat;
					pp[cp.id].rec = i;
					break;
				}
			}
		}
	}
}
void insertB(int time) {
	for (int size = bq.size(); size--;) {
		int pid = bq.front();
		for (int i = 1; i <= M; i++) {
			if (bb[i].pid == 0) {
				bb[i].pid = pid;
				bb[i].f = time + bb[i].lat;
				pp[pid].rep = i;
				bq.pop();
				break;
			}
		}
	}
}
void doA(int time) {
	for (int i = 1; i <= N; i++) {
		if (aa[i].pid == 0) continue;
		if (aa[i].f <= time) { //���� �ð� ������
			bq.push(aa[i].pid);
			aa[i].pid = 0;
		}
	}
}
void doB(int time) {
	for (int i = 1; i <= M; i++) {
		if (bb[i].pid == 0) continue;
		if (bb[i].f <= time) {
			people++;
			bb[i].pid = 0;
		}
	}
}

void solve() {
	int time = 0;
	while (people < K) {
		doA(time);
		insertA(time);
		doB(time);
		insertB(time);
		time++;
	}
}
int cnt() {
	int sum = 0;
	for (int i = 1; i <= K; i++) {
		if (pp[i].rec == A && pp[i].rep == B) sum+= pp[i].id;
	}
	return sum;
}

int main() {
	freopen("input2477.txt", "r", stdin);
	cin >> T;
	for (int t = 1; t <= T; t++) {
		input();
		solve();
		int result = cnt();
		if(result == 0) cout << "#" << t << " " << -1 << endl;
		else cout << "#" << t << " " << result << endl;
	}
}