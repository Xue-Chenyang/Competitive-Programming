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

int tc,n;

int main() {
	//ios::sync_with_stdio(false);
	//cin.tie(NULL);
	int x, y, z;
	cin >> x >> y >> z;
	vector<ll> a(x), b(y), c(z);
	vector<ll> S(3), M(3, 1e10);
	forn(i, x) {
		cin >> a[i];
			S[0] += a[i];
			M[0] = min(M[0], a[i]);
	}
	forn(i, y) {
		cin >> b[i];
		S[1] += b[i];
		M[1] = min(M[1], b[i]);
	}
	forn(i, z) {
		cin >> c[i];
		S[2] += c[i];
		M[2] = min(M[2], c[i]);
	}
	sort(all(S)); sort(all(M));
	ll off = min(S[0], M[0] + M[1]);
	cout << S[0] + S[1] + S[2] - off * 2 << endl;
}
