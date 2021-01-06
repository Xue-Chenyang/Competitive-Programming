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

/**
void getAns(int u, vector<vector<int>>& adj, vi & A, vi & B, bool isA = true) {
	if (isA) {
		if (A[u] >= 0) {
			return;
		}
		for (int c : adj[u]) {

		}
	}
}


int main() {
	int tc; scanf("%d", &tc);
	while (tc--) {
		int n, m;
		scanf("%d%d", &n, &m);
		vector<vector<int>> adj(n, vi());
		for (int i = 0; i < n; i++) {
			int a, b; scanf("%d%d", &a, &b);
			a--; b--;
			adj[a].push_back(b);
		}
		vi d(n,-1);
		queue<int> q; q.push(0); d[0] = 0;
		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (int c : adj[u]) {
				if (d[c] == -1) {
					d[c] = d[u] + 1;
					q.push(c);
				}
			}
		}
		vector<int> A(n,-1), B(n,-1);
		for (int i = 0; i < n; i++) {
			getAns(i, adj, A, B);
		}
	}
}
*/

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int tc;
	cin >> tc;
	while (tc--) {
		int n, m; cin >> n >> m;
		vi freq(m+1, 0);
		for (int i = 0; i < n; i++) {
			int a; cin >> a;
			freq[a]++;
		}
		vi prices(m + 1, 0);
		for (int i = 1; i <= m; i ++) {
			cin >> prices[i];
		}
		ll ans = 0;
		int ptr = m;
		for (int i = 1; i <= m; i++) {
			while (ptr > i && freq[ptr] == 0) ptr--;
			if (ptr <= i) break;
			ans += 1LL * prices[i];
			freq[ptr] --;
		}
		for (int i = 0; i <= m; i++) {
			ans += 1LL * freq[i] * prices[i];
		}
		cout << ans << endl;
	}
}