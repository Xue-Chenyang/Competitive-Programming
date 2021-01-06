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

vi visited, forbid, ans;
vector<vector<int>> adj;

void dfs(int u) {
	visited[u] = 1;
	if (!forbid[u]) {
		ans.push_back(u);
		for (int c : adj[u]) {
			forbid[c] = 1;
		}
	}
	for (int c : adj[u]) {
		if (!visited[c]) dfs(c);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int tc; cin >> tc;
	while (tc--) {
		int n, m; cin >> n >> m;
		adj.assign(n, vi());
		forn(i, m) {
			int a, b; cin >> a >> b;
			a--; b--;
			adj[a].push_back(b);
			adj[b].push_back(a);
		}
		visited.assign(n, 0);
		forbid.assign(n, 0);
		ans.clear();
		dfs(0);
		bool ok = true;
		forn(i, n) {
			if (!visited[i]) {
				cout << "NO" << endl;
				ok = false;
				break;
			}
		}
		if (ok) {
			cout << "YES" << endl;
			cout << ans.size() << endl;
			for (int v : ans) {
				cout << v + 1 << " ";
			}
			cout << endl;
		}
	}
}