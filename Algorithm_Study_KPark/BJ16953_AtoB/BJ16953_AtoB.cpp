/*
 * Author: kpark
 * Date: 2019.03.21
 * Algorithm: DFS
 * Problem: https://www.acmicpc.net/problem/16953
*/

#include <iostream>
#include <algorithm>

using namespace std;

long long A, B;
int result = 987654321;

bool dfs(long long cur, int d) {
	if (cur > B) return false;
	for (int i = 0; i < 2; i++) {
		long long tmp = A;
		if (i == 0) A *= 2;
		else A = A * 10 + 1;
		if (A == B) { result = min(result, d + 1); return true; }
		if(dfs(A, d + 1)) return true;
		A = tmp;
	}
	return false;
}

int main() {
	freopen("input.txt", "r", stdin);
	cin >> A >> B;
	if(dfs(A, 0)) cout << result + 1 << endl;
	else cout << -1 << endl;
}