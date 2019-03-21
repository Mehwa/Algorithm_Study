/*
 * Author: kpark
 * Data: 2019.03.20
 * Algorithm: DFS
 * Problem: https://www.acmicpc.net/problem/16987
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;
struct egg { int s, w; };
vector<egg> list;
int result = 0;
int tmp_result = 0;

void input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		int s, w;
		cin >> s >> w;
		list.push_back({ s, w });
	}
}

void dfs (int d) {
	if (d == N) return;
	for (int i = 0; i < list.size( ); i++) {
		if (d == i) continue;
		if (list[i].s <= 0) continue; //next egg broken
		if (list[d].s <= 0) { //cur egg broken
			dfs(d + 1);
		}
		else {
			list[d].s -= list[i].w;
			list[i].s -= list[d].w;
			if (list[d].s <= 0) tmp_result++;
			if (list[i].s <= 0) tmp_result++;
			result = max(result, tmp_result);
			dfs(d + 1);
			if (list[d].s <= 0) tmp_result--;
			if (list[i].s <= 0) tmp_result--;
			list[d].s += list[i].w;
			list[i].s += list[d].w;
		}
	}
}


int main() {
	freopen("input.txt", "r", stdin);
	input();
	dfs(0);
	cout << result << endl;
}