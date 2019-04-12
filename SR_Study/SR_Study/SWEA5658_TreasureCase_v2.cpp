/*
	2019.04.12

*/
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
int T, N, K;
string tc;
int ans[30];
bool comp(int a, int b) { return a > b; }
void input() {
	scanf("%d %d\n", &N, &K);
	getline(cin, tc);
	tc += tc;
}
bool exist(int num, int nn) {
	for (int i = 0; i < nn; i++) {
		if (ans[i] == num) return true;
	}
	return false;
}
int get16(char c) {
	if (c == 'A') return 10;
	if (c == 'B') return 11;
	if (c == 'C') return 12;
	if (c == 'D') return 13;
	if (c == 'E') return 14;
	if (c == 'F') return 15;
	else return c - '0';
}
int digit(int d) {
	int num = 1;
	for (int i = 0; i < d; i++)
		num *= 16;
	return num;
}
int getNumber(string str) {
	int num = 0, size = str.size() - 1;
	for (int i = 0; i < str.size(); i++) {
		num += get16(str[i]) * digit(size--);
	}
	return num;
}
int sim() {
	int size = N / 4, nn = 0;
	for (int i = 0; i < N; i++) {
		string cur = tc.substr(i, size);
		int num = getNumber(cur);
		if (!exist(num, nn)) ans[nn++] = num;
	}
	sort(ans, ans + nn, comp);
	return ans[K-1];
}
int main() {
	freopen("input5658.txt", "r", stdin);
	cin >> T;
	for (int t = 1; t <= T; t++) {
		input();
		cout << "#" << t << " " << sim() << endl;
	}
}