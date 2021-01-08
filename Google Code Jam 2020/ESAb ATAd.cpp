#pragma warning( disable : 4996 )
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <unordered_set>
#include <math.h>
using namespace std;

#define s(a) sort(a.begin(), a.end())
#define u(a) unique(a.begin(), a.end())
#define ms(a, b) memset(a, b, sizeof a)
#define all(a) a.begin(), a.end()

#define rep(i,x,y) for (i = (x); i < (y); i++)
#define rev(i,x,y) for (i = (y); i >= (x); i--)

#define forn(i, n) for (int i = 0; i < int(n); i++)

typedef long long ll;
typedef vector<int> vi;

int n, tc, b, x, y;

int query(int ind) {
	cout << ind + 1 << endl;
	int a; cin >> a;
	return a;
}

int main() {
	cin >> tc >> b;
	for (int _ = 1; _ <= tc; _++) {
		vector<bool> isSame(b);
		vi history, records(b, -1), rev_his(b, -1);
		int same = -1, diff = -1;
		int lp = 0, rp = b - 1;
		vi chanegs;
		for (int i = 0; i <= 150; i++) {

			if (lp > rp) {
				for (int j = 0; j < b; j++) {
					int value = records[j];
					
					int turn = rev_his[j];
					while (turn / 10 != (i-1) / 10) {
						int c = chanegs[turn / 10];
						switch (c){
						case 0:
							value = 1 - value;
							break;

						case 1:
							if (!isSame[j]) {
								value = 1 - value;
							}
							break;

						case 2:
							if (isSame[j]) {
								value = 1 - value;
							}
							break;

						case 3:
							break;
						}
						turn += 10;
					}
					cout << value;
				}
				cout << endl;
				string s;
				cin >> s;
				if (s != "Y") {
					return 0;
				}
				break;
			}
			if (i < 10) {
				if (i % 2 == 0) {
					records[lp] = query(lp);
					history.push_back(lp);
					rev_his[lp] = i;
					lp++;
				}
				else {
					records[rp] = query(rp);
					history.push_back(rp);
					rev_his[rp] = i;
					if (records[rp] == records[lp-1]) {
						isSame[lp - 1] = true; isSame[rp] = true;
						if (same < 0) same = lp-1;
					}
					else {
						isSame[lp - 1] = false;
						isSame[rp] = false;
						if (diff < 0) diff = lp-1;
					}
					rp--;
				}
				continue;
			}
			int c = 0;
			if (i % 10 == 0) {
				if (same < 0 || diff < 0) {
					int res = query(history[0]);
					history.push_back(history[0]);
					if (res != records[history[0]]) {
						c = 0;
					}
					else {
						c = 3;
					}
					records[history[0]] = res;
					rev_his[history[0]] = i;
					chanegs.push_back(c);
				}
				else {
					int res = query(same);
					history.push_back(same);
					if (res != records[same]) {
						x = 0;
					}
					else {
						x = 1;
					}
					records[same] = res;
					rev_his[same] = i;
				}
				continue;
			}
			if (i % 10 == 1) {
				if (same >= 0 && diff >= 0) {
					int res = query(diff);
					history.push_back(diff);
					if (res != records[diff]) {
						y = 0;
					}
					else {
						y = 1;
					}
					c = x + y * 2;
					chanegs.push_back(c);
					records[diff] = res;
					rev_his[diff] = i;
				}
				else {
					records[history.back()] = query(history.back());
					rev_his[history.back()] = i;
					history.push_back(history.back());
				}
				continue;
			}
			if (i % 2 == 0) {
				records[lp] = query(lp);
				history.push_back(lp);
				rev_his[lp] = i;
				lp++;
			}
			else {
				records[rp] = query(rp);
				history.push_back(rp);
				rev_his[rp] = i;
				if (records[rp] == records[lp - 1]) {
					isSame[rp] = true; isSame[lp - 1] = true;
					if (same < 0) same = lp - 1;
				}
				else {
					isSame[rp] = false; isSame[lp - 1] = false;
					if (diff < 0) diff = lp - 1;
				}
				rp--;
			}
		}
	}
}