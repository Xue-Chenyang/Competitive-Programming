#include <bits/stdc++.h>

using namespace std;

int r,c;

int moves[4][2]{{1,0},{0,1},{-1,0},{0,-1}};


int movesb[8][2]{{1,0},{0,1},{-1,0},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}};

bool inbound(int x, int y) {
	return x>=0 && y>=0 && x < r && y < c;
}

int nbits(int n) {
	int cnt = 0;
	while (n > 0) {
		if ((n & 1)) {
			cnt ++;
		}
		n >>= 1;
	}
	//cout << cnt << endl;
	return cnt;
} 

bool valid(int mask) {
	//cout << "checking " << mask << endl;
	int cnt1 = nbits(mask);
	vector<int> vis(100,0);
	int dfsc = 0;
	for (int i = 0; i < r*c; i ++) {
		//cout << "i is " << i << endl;
		if (((mask >> i) & 1) && !vis[i]) {
			dfsc++;
			
			//cout << "begin dfs at " << i/c << ", " << i%c << endl;
			
			if (dfsc > 1) {
				return false;
			}
			queue<int> q;
			q.push(i);
			vis[i] =1;
			while (!q.empty()) {
				int u = q.front(); q.pop();
				int x = u/c, y = u%c;
				for (auto [dx, dy] : moves) {
					int nx = x + dx, ny = y + dy;
					if (inbound(nx,ny) && !vis[nx*c+ny] && ((mask >> (nx*c+ny)) & 1)) {
						vis[nx*c+ny] = 1;
						q.push(nx*c+ny);
					}
				}
			}
		}
	}
	vector<int> vis2(100,0);
	int bcnt = 0;
	for (int i = 0; i < r*c; i ++) {
		if (((mask >> i) & 1)) continue;
		int x = i / c, y = i%c;
		if (x == 0 || x == r-1 || y == 0 || y == c-1) {
			if (vis2[i]) continue;
			queue<int> q;
			q.push(i);
			vis2[i] =1;
			while (!q.empty()) {
				bcnt ++;
				int u = q.front(); q.pop();
				int x = u/c, y = u%c;
				for (auto [dx, dy] : movesb) {
					int nx = x + dx, ny = y + dy;
					if (inbound(nx,ny) && !vis2[nx*c+ny] && !((mask >> (nx*c+ny)) & 1)) {
						vis2[nx*c+ny] = 1;
						q.push(nx*c+ny);
					}
				}
			}
		}
	}
	//cout << "bcnt is " << bcnt << endl;
	
	//cout << "cnt1 is " << cnt1 << endl;
	return bcnt + cnt1 == r*c;
}

int main() {
	cin >> r >> c;
	int cnt = 0;
	for (int i = 1; i < (1<<(r*c)); i ++) {
		if (valid(i)) cnt ++;
	}
	cout << cnt << endl;
}
