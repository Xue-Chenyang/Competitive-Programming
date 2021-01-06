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

vector<vector<int>> adj;
vi dist;
vector<int> dp[2];

int cal(int u, int l) {
	if (dist[u] == 0) {
		dp[l][u] = 0;
		return 0;
	}
	if (dp[l][u] >= 0) return dp[l][u];
	int ans = dist[u];
	for (int c : adj[u]) {
		if (dist[c] <= dist[u]) {
			if (l > 0) {
				ans = min(ans, cal(c, l - 1));
			}
		}
		else {
			ans = min(ans, cal(c, l));
		}
	}
	dp[l][u] = ans;
	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int tc; cin >> tc;
	while (tc--) {
		int n, m; cin >> n >> m;
		adj.assign(n, vi());
		forn(i, m) {
			int a, b; cin >> a >> b; a--; b--;
			adj[a].push_back(b);
		}
		queue<int> q;
		dist.assign(n, -1); dist[0] = 0;
		q.push(0);
		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (int v : adj[u]) {
				if (dist[v] < 0) {
					dist[v] = dist[u] + 1;
					q.push(v);
				}
			}
		}
		dp[0].assign(n, -1); dp[1].assign(n, - 1);
		for (int i = 0; i < n; i++) {
			cout << cal(i, 1) << " ";
		}
		cout << endl;
	}
}