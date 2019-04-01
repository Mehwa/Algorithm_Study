/*
 * Author: kpark
 * Date: 2019.03.21
 * Algorithm: DFS
 * Problem: https://www.acmicpc.net/problem/16943
*/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int A, B;
vector<int> alist;
int visit[10];
int result = 0;
bool possible = false;

void input() {
	cin >> A >> B;
	int n = A;
	while (n > 0) {
		int t = n % 10;
		n /= 10;
		alist.push_back(t);
	}
}

void dfs(int cur, int d) {
	if (d == alist.size()) {
		if (cur <= B) {
			result = max(result, cur); 
			possible = true;
		}
		return;
	}
	for (int i = 0; i < alist.size(); i++) {
		if (d == 0 && alist[i] == 0) continue; //0 can not be located at the first digit
		if (!visit[i]) {
			int tmp = cur;
			cur = cur * 10 + alist[i];
			visit[i] = true;
			dfs(cur, d + 1);
			visit[i] = false;
			cur = tmp;
		}
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	input();
	dfs(0, 0);
	if(possible) cout << result;
	else cout << -1 << endl;
}