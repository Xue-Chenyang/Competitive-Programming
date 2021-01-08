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

int tc; ll A, B;

int main() {
	//ios::sync_with_stdio(false);
	//cin.tie(NULL);
	cin >> tc;
	while (tc--) {
		int n;
		cin >> n;
		if (n == 1) {
			cout << "9\n";
		}
		else {
			cout << "9";
			int c = 8;
			for (int i = 1; i < n; i++) {
				cout << c;
				c = (c + 1) % 10;
			}
			cout << endl;
		}
	}
}
