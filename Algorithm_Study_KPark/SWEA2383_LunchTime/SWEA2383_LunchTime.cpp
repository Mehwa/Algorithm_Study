#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

typedef struct Person {
	int id, x, y, time, s, dist; //s:stair id
}Person;

struct compare
{
	bool operator()(const Person & a, const Person & b)
	{
		return a.dist > b.dist;
	}
};

typedef struct Stair {
	int x, y, k;
	priority_queue<Person, vector<Person>, compare> q;
}Stair;

int T, N, result;
int dx[4] = { 1, -1, 0 , 0 };
int dy[4] = { 0, 0, -1, 1 };
vector<Person> people;
vector<Stair> stairs;
bool visited[10][10][10];
int map[10][10];

void input() {
	result = 987654321;
	memset(visited, false, sizeof(visited));
	people.clear();
	stairs.clear();
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			if (map[i][j] == 1) {
				people.push_back({ (int)people.size(), i, j, 0, 0, 0 });
			}
			else if (map[i][j] > 1) {
				stairs.push_back({ i, j, map[i][j] });
			}
		}
	}
}

int countTime() {
	int rt = 0;
	for (int i = 0; i < people.size(); i++) {
		people[i].dist = abs(people[i].x - stairs[people[i].s].x) + abs(people[i].y - stairs[people[i].s].y);
		people[i].time = abs(people[i].x - stairs[people[i].s].x) + abs(people[i].y - stairs[people[i].s].y);
		stairs[people[i].s].q.push(people[i]);
	}
	for (int i = 0; i < stairs.size(); i++) {
		int k_time = stairs[i].k;
		int count = 0;
		int prev[3] = { 0 };
		while (!stairs[i].q.empty()) {
			Person cur_p = stairs[i].q.top();
			stairs[i].q.pop();
			if(cur_p.time < prev[count % 3])
				cur_p.time = prev[count % 3] + k_time;
			else
				cur_p.time += k_time + 1;
			prev[count % 3] = cur_p.time;
			rt = max(rt, prev[count % 3]);
			count++;
		}
	}
	return rt;
}

void dfs(int d) {
	if (d == people.size()) {
		result = min(countTime(), result);
		return;
	}
	for (int i = 0; i < stairs.size(); i++) {
		people[d].s = i;
		dfs(d + 1);
	}
}

int main()
{
	freopen("input.txt", "r", stdin);
	cin >> T;
	for (int t = 1; t <= T; t++) {
		input();
		dfs(0);
		cout << "#" << t << " " << result << endl;
	}
}