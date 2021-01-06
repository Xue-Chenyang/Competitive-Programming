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
		cin >> n;
		vector<vi> m;
		m.assign(n, vi(n));
		int t = 0, r = 0, c = 0;
		forn(i, n) {
			bool rep = false;
			vi freq(n + 1, 0);
			forn(j, n) {
				cin >> m[i][j];
				if (j == i) t += m[i][j];
				if (freq[m[i][j]] > 0) rep = true;
				freq[m[i][j]] ++;
			}
			if (rep) r++;
		}
		forn(j, n) {
			bool rep = false;
			vi freq(n + 1, 0);
			forn(i, n) {
				if (freq[m[i][j]] > 0) rep = true;
				freq[m[i][j]] ++;
			}
			if (rep) c++;
		}
		cout << "Case #" << _ << ": " << t << " " << r << " " << c << endl;
	}
}