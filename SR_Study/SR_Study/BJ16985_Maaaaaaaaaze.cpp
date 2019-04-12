/*
	2019.04.12

*/
#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;
struct POS { int z, r, c; };
int dist[5][5][5];
int map[5][5][5];
int umap[4][5][5][5];
int rot[5], layer[5];
int layer_init[5] = { 0, 1, 2, 3, 4 };
int dr[] = { -1, 1, 0, 0, 0, 0 };
int dc[] = { 0, 0, -1, 1, 0, 0 };
int dz[] = { 0, 0, 0, 0, -1, 1 };
int result = 987654321;
bool possible = false;
void input() {
	for (int z = 0; z < 5; z++) {
		for (int r = 0; r < 5; r++) {
			for (int c = 0; c < 5; c++) {
				cin >> map[z][r][c];
			}
		}
	}
}

void rotateArray(int z, int n) {
	int time = n;
	int src[5][5], dst[5][5];
	memcpy(src, map[z], sizeof(src));
	memcpy(dst, map[z], sizeof(src));
	while (time--) {
		int c = 4, idx = 0;
		for (int r = 0; r < 5; r++) {
			int tmp[5];
			memcpy(tmp, src[r], sizeof(tmp));
			for (int r2 = 0; r2 < 5; r2++) {
				dst[r2][c] = tmp[idx++];
			}
			c--, idx = 0;
		}
		memcpy(src, dst, sizeof(src));
	}
	memcpy(umap[n][z], dst, sizeof(dst));
}
void rotateMap() {
	for (int z = 0; z < 5; z++) {
		for (int n = 0; n < 4; n++) {
			rotateArray(z, n);
		}
	}
}
void createMap() {
	for (int i = 0; i < 5; i++) {
		memcpy(map[i], umap[rot[i]][layer[i]], sizeof(map[i]));
	}
}
int bfs() {
	if (!map[0][0][0] || !map[4][4][4]) return 987654321;  //*
	memset(dist, 0, sizeof(dist));
	queue<POS> q;
	q.push({ 0, 0, 0 });
	dist[0][0][0] = 1;
	while (q.size()) {
		for (int size = q.size(); size--;) {
			POS cur = q.front(); q.pop();
			for (int i = 0; i < 6; i++) {
				int nr = cur.r + dr[i], nc = cur.c + dc[i], nz = cur.z + dz[i];
				if (nr < 0 || nr >= 5 || nc < 0 || nc >= 5 || nz < 0 || nz >= 5 || dist[nz][nr][nc] || !map[nz][nr][nc]) continue;
				if (nr == 4 && nc == 4 && nz == 4) {
					possible = true; return dist[cur.z][cur.r][cur.c];
				}
				q.push({ nz, nr, nc });
				dist[nz][nr][nc] = dist[cur.z][cur.r][cur.c] + 1;
			}
		}
	}
	return 9876554321;
}
void layerDFS() {
	do{
		memcpy(layer, layer_init, sizeof(layer));
		createMap();
		result = min(result, bfs());
	} while (next_permutation(layer_init, layer_init + 5));
}
void rotateDFS(int d) {
	if (d == 5) {
		layerDFS();
		return;
	}
	for (int i = 0; i < 4; i++) {
		rot[d] = i;
		rotateDFS(d + 1);
	}
}
int main() {
	freopen("input16985.txt", "r", stdin);
	input(); 
	rotateMap();
	rotateDFS(0);
	if(possible) cout << result;
	else cout << -1;
}