#pragma warning( disable : 4996 )
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <unordered_set>
#include <math.h>
using namespace std;

void fast() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}

int lsone(int l) {
    return l & (-1 * l);
}

#define s(a) sort(a.begin(), a.end())
#define u(a) unique(a.begin(), a.end())
#define ms(a, b) memset(a, b, sizeof a)
#define all(a) a.begin(), a.end()

#define rep(i,x,y) for (i = (x); i < (y); i++)
#define rev(i,x,y) for (i = (y); i >= (x); i--)

#define forn(i, n) for (int i = 0; i < int(n); i++)

typedef long long ll;
typedef vector<int> vi;

const ll MOD = 1e9 + 7;
vector<ll> twos(62);
vector<vector<int>> adj(62, vi());

ll modpow(ll m, int p) {
	if (p == 0) return 1;
	ll ans = modpow(m, p / 2);
	ans = (ans * ans) % MOD;
	if (p & 1) {
		ans = (ans * m) % MOD;
	}
	return ans;
}

void ini() {
	ll cur = 1;
	for (int i = 0; i < 62; i++) {
		twos[i] = cur;
		cur = (cur * 2) % MOD;
	}
}
int main() {
	ini();
	int tc; cin >> tc;
	while (tc--) {
		int n; cin >> n;
		vector<ll> freq(63, 0);
		vector<ll> A(n);
		forn(i, n) {
			scanf("%lld", &A[i]);
			forn(j, 60) {
				if (A[i] & (1LL << j)) freq[j]++;
			}
		}

		ll ans = 0;
		for (int i = 0; i < n; i++) {
			ll orA = 0, andA = 0;
			for (int j = 0; j < 60; j++) {
				if ((A[i] >> j) & 1) {
					orA = (orA + (n * twos[j])) % MOD;
					andA = (andA + (freq[j] * twos[j])) % MOD;
				}
				else {
					orA = (orA + (freq[j] * twos[j])) % MOD;
				}
			}
			ans = (ans + (orA * andA)) % MOD;
		}
		printf("%lld\n", ans);
	}
}