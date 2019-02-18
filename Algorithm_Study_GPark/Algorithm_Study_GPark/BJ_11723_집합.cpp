// 10215
// https://www.acmicpc.net/problem/11723

#include <cstdio>
#include <cstring>
using namespace std;

int t;
int n=0;

void add(int num)
{
	n |= (1 << num);
}

void remove(int num)
{
	n &= ~(1 << num);
}

int check(int num)
{
	int ret = (n & (1 << num));
	if (ret) return 1;
	else return 0;
}

void toggle(int num)
{
	n ^= (1 << num);
}

void all()
{
	n = (1 << 20) - 1;
}

void empty()
{
	n = 0;
}
int main()
{
	char cmd[10];
	int num;
	scanf("%d", &t);
	while (t--) {
		scanf("%s", cmd);
		if (!strcmp(cmd, "all")) {
			all();
		}
		else if (!strcmp(cmd, "empty")) {
			empty();
		}
		else {
			scanf("%d", &num);
			if (!strcmp(cmd, "add")) {
				add(num - 1);
			}
			else if (!strcmp(cmd, "remove")) {
				remove(num - 1);
			}
			else if (!strcmp(cmd, "toggle")) {
				toggle(num - 1);
			}
			else if (!strcmp(cmd, "check")) {
				printf("%d\n", check(num - 1));
			}
		}
	}

	return 0;
}