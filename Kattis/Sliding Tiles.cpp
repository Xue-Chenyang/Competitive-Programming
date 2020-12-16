#include <bits/stdc++.h>
using namespace std;

char grid[120][120];
unordered_map<char , pair<int,int>> pos;

void reset() {
	for (int i = 0; i < 120; i++) {
		for (int j = 0; j < 120; j++) {
			grid[i][j] = ' ';
		}
		
	}
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			char c = 'A' + 5*i + j;
			grid[i + 60][j + 60] = c;
			pos[c] = {i + 60, j + 60};
		}
	}
			
}

void move(int r, int c, int dr, int dc) {
	
	char prev = ' ';
	
	do {
		pos[prev] = {r , c};
		//printf("pos %c = %d %d\n", prev, r , c);
		swap(prev , grid[r][c]);
		
		
		r += dr;
		c += dc;
	} while (prev != ' ');
}



void print() {
	
	
	
	int r1, r2, c1, c2;
	r1 = c1 = 1000;
	r2 = c2 = 0;
	
	for (int i = 0; i < 120; i++) {
		for (int j = 0; j < 120; j++) {
			if (isalpha(grid[i][j])) {
				r1 = min(r1 , i);
				r2 = max(r2, i);
				c1 = min (c1, j);
				c2 = max(c2, j);
			}
		}
	}
	
	for (int i = r1; i <= r2; i++) {
		deque<char> buf;
		for (int j = c1; j <= c2; j++) {
			buf.push_back(grid[i][j]);
		}
		while (buf.size() && !isalpha(buf.back())) {
			buf.pop_back();
		}
		
		for (auto c: buf) cout<<c;
		cout<<'\n';
	}
}


int main() {
	int n;
	while (cin>>n, n != -1) {
		
		reset();
		
		while (n--) {
			char ch; string dir; cin>>ch>>dir;
			int dr = 0, dc = 0;
			int r , c; tie(r , c ) = pos[ch];
			
			
			if (dir == "up") dr--;
			if (dir == "down") dr++;
			if (dir == "left") dc--;
			if (dir == "right") dc++;
			
			move( r , c , dr, dc);
			//print();
		}
		print();
		
		
		cout<<endl;
	}
}
