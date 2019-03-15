# Algorithm_Study
알고리즘 공부하자

VS에서 GitHub 사용법
https://mewha.tistory.com/5?category=692810

# Coding Cheet Sheet

* 파일로 표준 입출력 받기
```C++
freopen("input.txt", "r", stdin);
```

* array 초기화 (2차원도 가능)
```C++
#include <cstring>
memset(a, 0, sizeof(a));
```

* vector 중복제거
```C++
#include <algorithm>
vector<int> v;
v.sort(v.begin(), v.end());
v.erase(unique(v.begin(), v.end()), v.end());
```

* vector 복사
```C++
vector<int> src, dst;
copy(src.begin(), src.end(), dst.end());
```

* queue 초기화
```C++
queue <pair<int, int>> q;
swap(q, emptyq);
```

* priority queue compare overloading
```C++
#include <queue>
struct compare
{
    bool operator()(const int & a, int & b)
    {
        return a < b;
    }
};
priority_queue <int, vector<int>, compare> pq;
```

* string split
```C++
#include <string>
vector<string> split(const string& s, char delimiter)
{
	vector<string> tokens;
	string token;
	istringstream tokenStream(s);
	while (getline(tokenStream, token, delimiter))
	{
		tokens.push_back(token);
	}
	return tokens;
}
```
