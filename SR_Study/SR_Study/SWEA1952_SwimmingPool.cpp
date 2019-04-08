/*
	2019.04.02
	https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5PpFQaAQMDFAUq&categoryId=AV5PpFQaAQMDFAUq&categoryType=CODE
	1일, 1달, 3달 경우의 수에 따라 완전탐색하고, 
	3달일 경우 이후 2 칸을 -1로 채운 다음 12칸이 채워지면 비용을 계산한다.
*/

#include <iostream>
#include <algorithm>

using namespace std;

int T;
int cost[4]; //day, month, quater, year
int in_plan[12]; //input plan
int out_plan[12]; //cost choice
int result;

void input() {
	for (int i = 0; i < 4; i++)
		cin >> cost[i];
	for (int i = 0; i < 12; i++)
		cin >> in_plan[i];
}

int cal_cost() {
	int sum = 0;
	for (int i = 0; i < 12; i++) {
		if (out_plan[i] == -1) continue;
		if (out_plan[i] == 0) sum += in_plan[i] * cost[0];
		else sum += cost[out_plan[i]];
	}
	return sum;
}

void dfs(int d, int pc_end) { //pc: previous choice
	if (d == 12) {
		result = min(result, cal_cost());
		return;
	}
	for (int i = 0; i < 3; i++) {
		if (pc_end - d > 0) {
			out_plan[d] = -1; //지난달에 3달 선택했고, 아직 3달 안지났으면
			dfs(d + 1, pc_end);
			break;
		}
		else out_plan[d] = i;
		if (i == 2) dfs(d + 1, d + 3); //3달 선택
		else dfs(d + 1, d + 1);
	}
}

int main() {
	freopen("input1952.txt", "r", stdin);
	cin >> T;
	for (int t = 1; t <= T; t++) {
		input();
		result = cost[3];
		dfs(0, 0);
		cout << "#" << t << " " << result << endl;
	}
}