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

vector<int> primes;
int isp[1000000];

void seive() {
	ms(isp, 0);
	for (int i = 2; i < 1000000; i++) {
		if (isp[i] == 0) {
			primes.push_back(i);
			for (ll j = 1LL * i * i; j < 1000000; j += i) {
				isp[j] = 1;
			}
		}
	}
}

// const ll MOD = 990001037;

int faha(int k) {
	int ptr = 0;
	int ans = 1;
	while (1LL * primes[ptr] * primes[ptr] <= k) {
		int freq = 0;
		while (k % primes[ptr] == 0) {
			freq++; k /= primes[ptr];
		}
		if (freq & 1) {
			ans = (ans * primes[ptr]);
		}
		ptr++;
	}
	if (k != 1) {
		ans *= k;
	}
	return ans;
}

int main() {
	//ios::sync_with_stdio(false);
	//cin.tie(NULL);
	int tc; scanf("%d", &tc);
	seive();
	vi ref(1000001);
	for (int i = 1; i < 1000001; i ++) {
		ref[i] = faha(i);
	}
	vector<int> hm(1000001);
	forn(t, tc) {
		int n; scanf("%d", &n);
		vi A(n);
		forn(i, n) {
			scanf("%d", &A[i]);
			hm[ref[A[i]]] ++;
		}
		int zc = 0; int ans0 = 0, ans1 = 0;
		for (int i = 0; i < n; i++) {
			ans0 = max(ans0, hm[ref[A[i]]]);
			if (ref[A[i]] == 1 || hm[ref[A[i]]] % 2 == 0) {
				zc += hm[ref[A[i]]];
			}
			hm[ref[A[i]]] = 0;
		}
		ans1 = max(ans0, zc);
		int q; scanf("%d", &q);
		forn(i, q) {
			ll p; scanf("%lld", &p);
			if (p == 0) {
				printf("%d\n", ans0);
			}
			else {
				printf("%d\n", ans1);
			}
		}
	}
}