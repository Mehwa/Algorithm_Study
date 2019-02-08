#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int N;
int s[16][16] = { 0 };
vector<int> v(16), id(16);

void printAB(vector<int> &a, vector<int> &b) {
	cout << "A:";
	for (int i = 0; i < N / 2; i++)
		cout << a[i] << " ";

	cout << "	B:";
	for (int i = 0; i < N / 2; i++)
		cout << b[i] << " ";
	cout << endl;
}

void input() {
	cin >> N;
	for (int i = 0; i < N; i++)
		v[i] = i;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> s[i][j];
	for (int i = 0; i < N / 2; i++)
		id[i] = 1;
	for (int i = N / 2; i < N; i++)
		id[i] = 0;
}

int cal(vector<int> &vl) {
	int sum = 0;
	for (int i = 0; i < N / 2 - 1; i++)
		for (int j = i + 1; j < N / 2; j++)
			sum = sum + s[vl[i]][vl[j]] + s[vl[j]][vl[i]];
	return sum;
}

int numComb() {
	int num = 1;
	for (int i = N; 0 < i; i--) {
		if (i > N / 2)
			num *= i;
		else
			num /= i;
	}
	return num / 2;
}

int main() {
	int test_case, T;
	freopen("input.txt", "r", stdin);
	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case) {
		int ans = 987654321, count = 0;

		input();

		int maxCount = numComb();

		sort(id.begin(), id.begin() + N);

		do {
			vector<int> a, b;
			int a_val = 0, b_val = 0, diff = 0;

			//get combination with id[]
			for (int i = 0; i < N; i++) {
				if (id[i])
					a.push_back(v[i]);
				else
					b.push_back(v[i]);
			}

			printAB(a, b);

			a_val = cal(a);
			b_val = cal(b);

			diff = abs(a_val - b_val);
			ans = min(diff, ans);

			if (++count == maxCount)
				break;
		} while (next_permutation(id.begin(), id.begin() + N));

		cout << "#" << test_case << " " << ans << endl;
	}
	return 0;
}
