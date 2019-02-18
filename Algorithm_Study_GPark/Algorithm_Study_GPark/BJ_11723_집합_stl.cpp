// 10215
// https://www.acmicpc.net/problem/11723

#include <cstdio>
#include <cstring>
#include <bitset>
using namespace std;

int t;
bitset<20> b;

void add(int num)
{
	b.set(num, true);
}

void remove(int num)
{
	b.set(num, false);
}

int check(int num)
{
	if (b.test(num) == 1) return 1;
	else return 0;
}

void toggle(int num)
{
	b.flip(num);
}

void all()
{
	b.set();
}

void empty()
{
	b.reset();
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