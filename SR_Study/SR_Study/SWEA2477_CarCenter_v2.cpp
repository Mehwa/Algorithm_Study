/*
	2019.04.11

*/
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

struct C { int id, t; };
int T, N, M, K, AA, BB, result, finish;
int A[10], B[10], at[10], atid[10], bt[10], tk[1001], cid[1001];
queue<C> aq, bq;
void input() {
	queue<C>().swap(aq); queue<C>().swap(bq);
	result = 0, finish = 0;
	memset(at, -1, sizeof(at));
	memset(atid, -1, sizeof(atid));
	memset(bt, -1, sizeof(bt));
	memset(cid, -1, sizeof(cid));
	cin >> N >> M >> K >> AA >> BB;
	for (int i = 1; i <= N; i++)
		cin >> A[i];
	for (int i = 1; i <= M; i++)
		cin >> B[i];
	for (int i = 1; i <= K; i++) {
		cin >> tk[i];
		aq.push({ i, tk[i] });
	}
}

void recep_ready(int time) {
	for (int i = 1; i <= N; i++) {
		if (at[i] == -1) { //ºó Ä­ ÀÖÀ¸¸é
			if (aq.empty()) return;
			C cur = aq.front();
			if (cur.t > time) return;
			at[i] = time + A[i];
			atid[i] = cur.id;
			if (i == AA) //n_recep += cur.id;
				cid[cur.id] = 1;
			aq.pop();
		}
	}
}
void recep(int time) {
	for (int i = 1; i <= N; i++) {
		if (at[i] == -1) continue;
		if (at[i] <= time) {
			bq.push({ atid[i], time });
			at[i] = -1;
			atid[i] = -1;
		}
	}
}
void repair_ready(int time) {
	for (int i = 1; i <= M; i++) {
		if (bt[i] == -1) { //ºó Ä­ ÀÖÀ¸¸é
			if (bq.empty()) return;
			C cur = bq.front();
			if (cur.t > time) return;
			bt[i] = time + B[i];
			if (i == BB) { //n_repair += cur.id;
				if (cid[cur.id] == 1)
					cid[cur.id] = 2;
			}
			bq.pop();
		}
	}
}
void repair(int time) {
	for (int i = 1; i <= M; i++) {
		if (bt[i] == -1) continue;
		if (bt[i] <= time) {
			bt[i] = -1;
			finish++;
		}
	}
}
void solve() {
	int time = 0;
	while (finish != K) {
		recep(time);
		recep_ready(time);
		repair(time);
		repair_ready(time);
		time++;
	}
}
int output() {
	int sum = 0;
	for (int i = 1; i < 1001; i++) {
		if (cid[i] == 2) sum += i;
	}
	return sum;
}

int main() {
	freopen("input2477.txt", "r", stdin);
	cin >> T;
	for (int t = 1; t <= T; t++) {
		input();
		solve();
		result = output();
		if (result == 0) cout << "#" << t << " " << -1 << endl;
		else cout << "#" << t << " " << result << endl;
	}
}