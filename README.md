# Algorithm_Study
알고리즘 공부하자

VS에서 GitHub 사용법
https://mewha.tistory.com/5?category=692810

# Coding Cheet Sheet

* 파일로 표준 입출력 받기
<pre><code>freopen("input.txt", "r", stdin);</code></pre>

* array 초기화 (2차원도 가능)
<pre><code>
#include cstring
memset(a, 0, sizeof(a));
</code></pre>

* vector 중복제거
<pre><code>
#include algorithm
vector<int> v;
v.sort(v.begin(), v.end());
v.erase(unique(v.begin(), v.end()), v.end());
</code></pre>

* vector 복사
<pre><code>
vector<int> src, dst;
copy(src.begin(), src.end(), dst.end());
</code></pre>
