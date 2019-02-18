// 190215
// https://www.acmicpc.net/problem/10972

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int n;

int main()
{
	vector<int> v;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		int a;
		scanf("%d", &a);
		v.push_back(a);
	}

	int ret = next_permutation(v.begin(), v.end());

	if (ret == 0) {
		printf("-1\n");
	}
	else{
		for (int i = 0; i < n; i++) {
			printf("%d ", v[i]);
		}
		printf("\n");
	}
	return 0;
}