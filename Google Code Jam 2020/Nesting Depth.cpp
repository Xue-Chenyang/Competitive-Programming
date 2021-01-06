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

int n, tc;
int main() {
	cin >> tc;
	for (int _ = 1; _ <= tc; _++) {
		string s; cin >> s;
		int cur = 0;
		printf("Case #%d: ", _);
		forn(i, s.length()) {
			char c = s[i];
			int l = c - '0';
			if (l < cur) {
				for (int j = l; j < cur; j++) {
					printf(")");
				}
			}
			else if (l > cur) {
				for (int j = cur; j < l; j++) {
					printf("(");
				}
			}
			printf("%c", c);
			cur = l;
		}
		for (; cur; cur--) {
			printf(")");
		}
		printf("\n");
	}
}