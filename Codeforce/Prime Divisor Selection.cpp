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

const int CAP = 1e6 + 10;
const ll MAXN = 1e18;
int n, k; bool isp[CAP];
vector<int> primes;
vector<ll> A, B;
unordered_map<ll, int> rev_pows;

void seive() {
	for (int i = 2; i < CAP; i++) {
		if (isp[i]) {
			primes.push_back(i);
			for (ll j = 1LL * i * i; j < CAP; j+= i) {
				isp[j] = false;
			}
			for (ll j = 1LL * i; j < MAXN; j *= i) {
				rev_pows[j] = i;
				if (MAXN / j < i) break;
			}
		}
	}
}

bool isPrime(int m) {
	if (m < CAP) return isp[m];
	for (int i = 0; i < primes.size(); i++) {
		if (1LL * primes[i] * primes[i] > m) break;
		if (m % primes[i] == 0) return false;
	}
	return true;
}


int main() {
	ms(isp, true);
	scanf("%d%d", &n, &k);
	if (k == 1) {
		printf("0\n");
		return 0;
	}
	seive();
	A.resize(n); B.resize(n, -1);
	int tot = 0;
	unordered_map<int, vector<ll>> ps;
	forn(i, n) {
		scanf("%lld", &A[i]);
		if (A[i] < 1e9) {
			if (isPrime(A[i])) {
				ps[A[i]].push_back(A[i]);
				B[i] = A[i];
				continue;
			}
		}
		int rt = sqrt(A[i]);
		if (isPrime(rt) && 1LL * rt * rt == A[i]) {
			ps[rt].push_back(A[i]); B[i] = rt;
			continue;
		}
		if (rev_pows.count(A[i])) {
			ps[rev_pows[A[i]]].push_back(A[i]); B[i] = rev_pows[A[i]];
		}
	}
	priority_queue<pair<int, int>> pq;
	for (auto pair : ps) {
		if (pair.second.size() > 1) {
			tot += pair.second.size();
			pq.push({ pair.second.size(), pair.first });
		}
	}
	if (k > tot) {
		vector<ll> ans;
		for (int i = 0; i < n; i++) {
			if (ans.size() + tot == k) break;
			if (B[i] == -1) {
				bool b = true; ll cp = A[i];
				for (auto [p, arr] : ps) {
					if (arr.size() == 1) continue;
					while (cp % p == 0) {
						cp /= p;
					}
					if (cp == 1) break;
				}
				if (cp == 1) {
					ans.push_back(A[i]);
				}
			}
		}
		if (ans.size() + tot == k) {
			for (int i = 0; i < n; i++) {
				if (ps[B[i]].size() > 1) {
					printf("%lld ", A[i]);
				}
			}
			for (ll v : ans) {
				printf("%lld ", v);
			}
		}
		else {
			printf("0\n");
		}
		return 0;
	}
	if (pq.top().first == 2 && (k & 1)) {
		bool ok = false;
		for (int i = 0; i < n; i++) {
			if (B[i] == -1) {
				unordered_set<int> pick;
				bool b = true; ll cp = A[i];
				for (auto [p,arr] : ps) {
					if (arr.size() <= 1) continue;
					if (cp % p == 0) pick.insert(p);
					while (cp % p == 0) cp /= p;
				}
				if (cp != 1LL || pick.size() > (k - 1) / 2) {
					b = false;
				}
				if (b) {
					int cnt = (k - 1 - 2 * pick.size()) / 2;
					for (auto [p, arr] : ps) {
						if (arr.size() <= 1) continue;
						if (pick.count(p)) {
							printf("%lld %lld ", arr[0], arr[1]);
						}
						else if (cnt > 0) {
							cnt--;
							printf("%lld %lld ", arr[0], arr[1]);
						}
					}
					printf("%lld\n", A[i]);
					ok = true; break;
				}
			}
		}
		if (!ok) {
			printf("0\n");
		}
	}
	else {
		vector<ll> ans; bool sf = false;
		int rem = k;
		while (rem > 0) {
			if (rem == 1) {
				sf = true;
				auto [f, p] = pq.top(); pq.pop();
				ans.push_back(ps[p][0]);
				ans.push_back(ps[p][1]);
				break;
			}
			auto [f, p] = pq.top(); pq.pop();
			for (int i = 0; i < rem && i < ps[p].size(); i++) {
				ans.push_back(ps[p][i]);
			}
			rem -= ps[p].size();
		}
		
		for (int i = ans.size() - 1; (i + k) >= ans.size(); --i) {
			printf("%lld ", ans[i]);
		}
	}
}