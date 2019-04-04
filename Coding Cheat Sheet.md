# Coding Cheat Sheet

* 입출력 속도 줄이기
```C++
ios_base::sync_with_stdio(0);
cin.tie(0);
```

* 파일로 표준 입출력 받기
```C++
freopen("input.txt", "r", stdin);
```

* 한 줄씩 입력 받기
```C++
string line;
getline(cin, line);
```

* array 초기화 (2차원도 가능)
```C++
#include <cstring>
memset(a, 0, sizeof(a)); //btye 단위로 set, 0, -1 사용 가능, 1 불가
```

* 정렬
```C++
#include <algorithm>
vector<int> src, dst;
sort(src.begin(), src.end()); //오름차순
sort(src.rbegin(), src.rend()); //내림차순
sort(src.rbegin(), src.rend(), compare); //비교 함수 정의
```

* vector 중복제거
```C++
#include <algorithm>
vector<int> v;
sort(v.begin(), v.end());
v.erase(unique(v.begin(), v.end()), v.end());
```

* vector 복사
```C++
vector<int> src, dst;
copy(src.begin(), src.end(), dst.end());
```

* vector 원소 찾기
```C++
#include <algorithm>
vector<int> v;
auto it = find (v.begin(), v.end(), 30);
if (it != myvector.end())
	cout << "Element found in myvector: " << *it << '\n';
else
	cout << "Element not found in myvector\n";
```

* queue 초기화
```C++
queue <pair<int, int>> q;
swap(q, emptyq);
```

* 순열
```C++
vector<int> arr;
sort(arr.begin(), arr.end());
do{
	//permutation in arr
}while(next_permutation(arr.begin(), arr.end()));
//perv_permutation() for reverse permutation search
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
* queue에서 distance에 따라 다르게 처리하고 싶을 때
```C++
while (q.size()) {
	for (int size = q.size(); size--;) { //for each distance

	}
}
```
