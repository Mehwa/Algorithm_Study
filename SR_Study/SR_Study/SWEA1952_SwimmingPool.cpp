/*
	2019.04.02
	https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5PpFQaAQMDFAUq&categoryId=AV5PpFQaAQMDFAUq&categoryType=CODE
	1��, 1��, 3�� ����� ���� ���� ����Ž���ϰ�, 
	3���� ��� ���� 2 ĭ�� -1�� ä�� ���� 12ĭ�� ä������ ����� ����Ѵ�.
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
			out_plan[d] = -1; //�����޿� 3�� �����߰�, ���� 3�� ����������
			dfs(d + 1, pc_end);
			break;
		}
		else out_plan[d] = i;
		if (i == 2) dfs(d + 1, d + 3); //3�� ����
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