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

int tc,n,k,q;

const ll MOD = 1e9 + 7;
const int MAXN = 5005;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n >> k >> q;
	vector<ll> A(n);
	forn(i, n) cin >> A[i];
	ll dp[MAXN][MAXN]; ms(dp, 0);
	for (int i = 0; i < n; i++) {
		dp[i][0] = 1;
	}
	for (int i = 1; i <= k; i++) {
		for (int j = 0; j < n; j++) {
			if (j - 1 >= 0) {
				dp[j][i] = dp[j - 1][i - 1];
			}
			if (j + 1 < n) {
				dp[j][i] = (dp[j][i] + dp[j + 1][i - 1]) % MOD;
			}
		}
	}
	ll mul[MAXN]; ms(mul, 0);
	ll ans = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= k / 2; j++) {
			if (j * 2 == k) {
				mul[i] = (mul[i] + dp[i][j] * dp[i][k - j]) % MOD;
			}
			else {
				mul[i] = (mul[i] + dp[i][j] * dp[i][k - j] * 2) % MOD;
			}
		}
		ans = (ans + mul[i] * A[i]) % MOD;
	}
	forn(i, q) {
		int a; ll d;
		cin >> a >> d;
		a--;
		ans = (ans - mul[a] * A[a] + mul[a] * d) % MOD;
		if (ans < 0) ans += MOD;
		A[a] = d;
		cout << ans << endl;
	}

}
