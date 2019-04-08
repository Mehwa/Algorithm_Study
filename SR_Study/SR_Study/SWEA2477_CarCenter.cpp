/*
	2019.04.03
	https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV6c6bgaIuoDFAXy&categoryId=AV6c6bgaIuoDFAXy&categoryType=CODE
	1) 접수가 끝난 사람들을 접수대에서 뺀다. => 정비 대기 큐에 넣는다.
	2) 빈 접수대에 대기 인원을 투입시킨다.
	3) 정비가 끝난 사람들을 정비대에서 뺀다.
	4) 빈 정비대에 대기 인원을 투입시킨다.
	구조체를 복잡하게 정의해서 구현이 힘들었다.
	처음에 문제를 잘못이해해서 인원수를 셌다.
	B에 넣을 때 큐에 들어 있는 모든 원소를 넣어야 하는데, 하나만 넣어서 틀렸었다.
	시뮬레이션 문제는 실수에 주의해야 하고, 집중해서 예외가 없는지 잘 생각해야 함.
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
		if (pp[i].t <= time) { // 도착 시간 넘으면
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
		if (aa[i].f <= time) { //종료 시간 지나면
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