/*
	2019.04.11

*/
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int T, result;
int c[4], dd[13], p[13];
void input() {
	memset(p, -1, sizeof(p));
	for (int i = 0; i < 4; i++)
		cin >> c[i];
	for (int i = 1; i < 13; i++)
		cin >> dd[i];
	result = c[3];
}
int cost() {
	int sum = 0;
	for (int i = 1; i < 13; i++) {
		int plan = p[i];
		if (plan == -1) continue;
		if(plan == 0) sum += c[plan] * dd[i];
		else sum += c[plan];
	}
	return sum;
}
void dfs(int d) {
	if (d == 13) {
		result = min(result, cost());
		return;
	}
	for (int i = 0; i < 3; i++) { //0:1일권, 1:1달권, 2:3달권
		if (d > 10 && i == 2) continue; //11월 이후 3달권 안함
		p[d] = i;
		if (i == 2) dfs(d + 3);
		else dfs(d + 1);
		p[d] = -1;
	}
}
int main() {
	freopen("input1952.txt", "r", stdin);
	cin >> T;
	for (int t = 1; t <= T; t++) {
		input();
		dfs(1);
		cout << "#" << t << " " << result << endl;
	}
}