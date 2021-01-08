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

int tc;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> tc;
	for (int _ = 1; _ <= tc; _++) {
		int x, y; cin >> x >> y;
		int A = abs(x), B = abs(y);
		vector<char> ans;
		bool ok = false;
		while (true) {
			if (A == 0 && B == 1) {
				ans.push_back('N');
				ok = true;
				break;
			}
			if (A == 1 && B == 0) {
				ans.push_back('E');
				ok = true;
				break;
			}
			if (((A ^ B) & 1) == 0) {
				break;
			}
			if (A & 1) {
				if ((A >> 1) & 1) {
					if ((B >> 1) & 1) {
						A = (A + 1) / 2;
						B = B / 2;
						ans.push_back('W');
					}
					else {
						A = (A - 1) / 2;
						B = B / 2;
						ans.push_back('E');
					}
				}
				else {
					if ((B >> 1) & 1) {
						A = (A - 1) / 2;
						B = B / 2;
						ans.push_back('E');
					}
					else {
						A = (A + 1) / 2;
						B = B / 2;
						ans.push_back('W');
					}
				}
			}
			else {
				if ((B >> 1) & 1) {
					if ((A >> 1) & 1) {
						B = (B + 1) / 2;
						A = A / 2;
						ans.push_back('S');
					}
					else {
						B = (B - 1) / 2;
						A = A / 2;
						ans.push_back('N');
					}
				}
				else {
					if ((A >> 1) & 1) {
						B = (B - 1) / 2;
						A = A / 2;
						ans.push_back('N');
					}
					else {
						B = (B + 1) / 2;
						A = A / 2;
						ans.push_back('S');
					}
				}
			}
		}
		cout << "Case #" << _ << ": ";
		if (ok) {
			for (char c : ans) {
				switch(c) {
				case 'S':
					if (y > 0) {
						cout << 'S';
					}
					else {
						cout << 'N';
					}
					break;

				case 'N':
					if (y > 0) {
						cout << 'N';
					}
					else {
						cout << 'S';
					}
					break;

				case 'E':
					if (x > 0) {
						cout << 'E';
					}
					else {
						cout << 'W';
					}
					break;

				case 'W':
					if (x > 0) {
						cout << 'W';
					}
					else {
						cout << 'E';
					}
					break;
				}
			}
			cout << endl;
		}
		else {
			cout << "IMPOSSIBLE" << endl;
		}
	}
}
